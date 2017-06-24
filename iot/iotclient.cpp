/*
 *  Copyright (C) 2014-2017 Savoir-faire Linux Inc.
 *
 *  Author: Philippe Proulx <philippe.proulx@savoirfairelinux.com>
 *  Author: Guillaume Roguez <Guillaume.Roguez@savoirfairelinux.com>
 *  Author: Houmin Wei <houmin.wei@pku.edu.cn>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <stdexcept>

#include "iotclient.h"
#include "dring/account_const.h"

IotClient::IotClient(int flags, bool persistent)
{
    callManager_.reset(new IotCallManager());
    configurationManager_.reset(new IotConfigurationManager());
    presenceManager_.reset(new IotPresenceManager());

#ifdef RING_VIDEO
    videoManager_.reset(new IotVideoManager());
#endif

    if (initLibrary(flags) < 0)
        throw std::runtime_error {"cannot initialize libring"};

}

IotClient::~IotClient()
{
    // instances destruction order is important
    // so we enforce it here

#ifdef RING_VIDEO
    videoManager_.reset();
#endif
    presenceManager_.reset();
    configurationManager_.reset();
    callManager_.reset();
}

int
IotClient::initLibrary(int flags)
{
    using namespace std::placeholders;

    using std::bind;
    using DRing::exportable_callback;
    using DRing::CallSignal;
    using DRing::ConfigurationSignal;
    using DRing::PresenceSignal;
    using DRing::AudioSignal;

    using SharedCallback = std::shared_ptr<DRing::CallbackWrapperBase>;

    auto callM = callManager_.get();
    auto confM = configurationManager_.get();
    auto presM = presenceManager_.get();

#ifdef RING_VIDEO
    using DRing::VideoSignal;
    auto videoM = videoManager_.get();
#endif

    // Configuration event handlers
    
    // This is a short example of callback using a lambda. In this case, this displays the incoming messages
    const std::map<std::string, SharedCallback> configEvHandlers = {
        exportable_callback<ConfigurationSignal::IncomingAccountMessage>([]
            (const std::string& accountID, const std::string& from, const std::map<std::string, std::string>& payloads){
                RING_INFO("accountID : %s", accountID.c_str());
                RING_INFO("from : %s", from.c_str());
                for(auto& it : payloads)
                    RING_INFO("%s : %s", it.first.c_str(), it.second.c_str());
            }),
    };

    if (!DRing::init(static_cast<DRing::InitFlag>(flags)))
        return -1;

    registerConfHandlers(configEvHandlers);

    if (!DRing::start())
        return -1;

    return 0;
}

void
IotClient::finiLibrary() noexcept
{
    DRing::fini();
}

int
IotClient::event_loop() noexcept
{
    // While the iot client is running, the events are polled every 10 milliseconds
    RING_INFO("IotClient starting to poll events");
    auto confM = configurationManager_.get();
    const std::vector<std::string> accountList(confM->getAccountList());

    if (accountList.empty())
    {
        RING_INFO("No Account Yet");

       auto details = confM->getAccountTemplate(DRing::Account::ProtocolNames::RING);
        details["Account.alias"] = "loveST";
        details["Account.archivePassword"] = "loveST1MARING";
        details["Account.deviceID"] = "6bf905c7894c620894e0b40d0ef9f468f2c358d1";
        details["Account.deviceName"] = "cosmos";
        details["Account.displayName"] = "loveST";
        details["Account.hostname"] = "bootstrap.ring.cx";
        details["Account.username"] = "ring:3e4ae4861d1e888522b7c1530c202f8c43e99d71";
        details["RingNS.account"] = "ccd0eeaf90ca0d75a6fa277fee8b822a32ef93fa";
        confM->addAccount(details);
    }

    while(!pollNoMore_)
    {
        DRing::pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::map<std::string, std::string> payloads;
        std::string payload("payload");
        std::string msg("houmin");
        payloads.insert(std::make_pair(payload, msg));
        auto accLst = confM->getAccountList();
        if (!accLst.empty())
        {
            for (auto &item: accLst)
                RING_INFO("%s",item.c_str());
            std::string toAccountID(accLst.front());
            std::string toUri("ring:fd9d8b64610500a8f7b87579fbfc75562ff97f3c");
            confM->sendTextMessage(toAccountID, toUri, payloads);
        }
        RING_INFO("POLLING...");
    }
    return 0;
}

int
IotClient::exit() noexcept
{
    try {
        // On exit, the client stop polling events
        pollNoMore_ = true;
        finiLibrary();
    } catch (const std::exception& err) {
        std::cerr << "quitting: " << err.what() << std::endl;
        return 1;
    }

    return 0;
}
