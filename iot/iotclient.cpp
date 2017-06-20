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

    // Call event handlers
    const std::map<std::string, SharedCallback> callEvHandlers = {
        exportable_callback<CallSignal::StateChange>(bind(&IotCallManager::callStateChanged, callM, _1, _2, _3)),
        exportable_callback<CallSignal::TransferFailed>(bind(&IotCallManager::transferFailed, callM)),
        exportable_callback<CallSignal::TransferSucceeded>(bind(&IotCallManager::transferSucceeded, callM)),
        exportable_callback<CallSignal::RecordPlaybackStopped>(bind(&IotCallManager::recordPlaybackStopped, callM, _1)),
        exportable_callback<CallSignal::VoiceMailNotify>(bind(&IotCallManager::voiceMailNotify, callM, _1, _2)),
        exportable_callback<CallSignal::IncomingMessage>(bind(&IotCallManager::incomingMessage, callM, _1, _2, _3)),
        exportable_callback<CallSignal::IncomingCall>(bind(&IotCallManager::incomingCall, callM, _1, _2, _3)),
        exportable_callback<CallSignal::RecordPlaybackFilepath>(bind(&IotCallManager::recordPlaybackFilepath, callM, _1, _2)),
        exportable_callback<CallSignal::ConferenceCreated>(bind(&IotCallManager::conferenceCreated, callM, _1)),
        exportable_callback<CallSignal::ConferenceChanged>(bind(&IotCallManager::conferenceChanged, callM, _1, _2)),
        exportable_callback<CallSignal::UpdatePlaybackScale>(bind(&IotCallManager::updatePlaybackScale, callM, _1, _2, _3)),
        exportable_callback<CallSignal::ConferenceRemoved>(bind(&IotCallManager::conferenceRemoved, callM, _1)),
        exportable_callback<CallSignal::NewCallCreated>(bind(&IotCallManager::newCallCreated, callM, _1, _2, _3)),
        exportable_callback<CallSignal::RecordingStateChanged>(bind(&IotCallManager::recordingStateChanged, callM, _1, _2)),
        exportable_callback<CallSignal::SecureSdesOn>(bind(&IotCallManager::secureSdesOn, callM, _1)),
        exportable_callback<CallSignal::SecureSdesOff>(bind(&IotCallManager::secureSdesOff, callM, _1)),
        exportable_callback<CallSignal::RtcpReportReceived>(bind(&IotCallManager::onRtcpReportReceived, callM, _1, _2)),
        exportable_callback<CallSignal::PeerHold>(bind(&IotCallManager::peerHold, callM, _1, _2)),
        exportable_callback<CallSignal::AudioMuted>(bind(&IotCallManager::audioMuted, callM, _1, _2)),
        exportable_callback<CallSignal::VideoMuted>(bind(&IotCallManager::videoMuted, callM, _1, _2)),
        exportable_callback<CallSignal::SmartInfo>(bind(&IotCallManager::SmartInfo, callM, _1))
    };

    // Configuration event handlers
    const std::map<std::string, SharedCallback> configEvHandlers = {
        exportable_callback<ConfigurationSignal::VolumeChanged>(bind(&IotConfigurationManager::volumeChanged, confM, _1, _2)),
        exportable_callback<ConfigurationSignal::AccountsChanged>(bind(&IotConfigurationManager::accountsChanged, confM)),
        exportable_callback<ConfigurationSignal::StunStatusFailed>(bind(&IotConfigurationManager::stunStatusFailure, confM, _1)),
        exportable_callback<ConfigurationSignal::RegistrationStateChanged>(bind(&IotConfigurationManager::registrationStateChanged, confM, _1, _2, _3, _4)),
        exportable_callback<ConfigurationSignal::VolatileDetailsChanged>(bind(&IotConfigurationManager::volatileAccountDetailsChanged, confM, _1, _2)),
        exportable_callback<ConfigurationSignal::Error>(bind(&IotConfigurationManager::errorAlert, confM, _1)),
        exportable_callback<ConfigurationSignal::IncomingAccountMessage>(bind(&IotConfigurationManager::incomingAccountMessage, confM, _1, _2, _3 )),
        exportable_callback<ConfigurationSignal::AccountMessageStatusChanged>(bind(&IotConfigurationManager::accountMessageStatusChanged, confM, _1, _2, _3, _4 )),
        exportable_callback<ConfigurationSignal::IncomingTrustRequest>(bind(&IotConfigurationManager::incomingTrustRequest, confM, _1, _2, _3, _4 )),
        exportable_callback<ConfigurationSignal::ContactAdded>(bind(&IotConfigurationManager::contactAdded, confM, _1, _2, _3 )),
        exportable_callback<ConfigurationSignal::ContactRemoved>(bind(&IotConfigurationManager::contactRemoved, confM, _1, _2, _3 )),
        exportable_callback<ConfigurationSignal::ExportOnRingEnded>(bind(&IotConfigurationManager::exportOnRingEnded, confM, _1, _2, _3 )),
        exportable_callback<ConfigurationSignal::KnownDevicesChanged>(bind(&IotConfigurationManager::knownDevicesChanged, confM, _1, _2 )),
        exportable_callback<ConfigurationSignal::NameRegistrationEnded>(bind(&IotConfigurationManager::nameRegistrationEnded, confM, _1, _2, _3 )),
        exportable_callback<ConfigurationSignal::RegisteredNameFound>(bind(&IotConfigurationManager::registeredNameFound, confM, _1, _2, _3, _4 )),
        exportable_callback<ConfigurationSignal::DeviceRevocationEnded>(bind(&IotConfigurationManager::deviceRevocationEnded, confM, _1, _2, _3)),
        exportable_callback<ConfigurationSignal::CertificatePinned>(bind(&IotConfigurationManager::certificatePinned, confM, _1 )),
        exportable_callback<ConfigurationSignal::CertificatePathPinned>(bind(&IotConfigurationManager::certificatePathPinned, confM, _1, _2 )),
        exportable_callback<ConfigurationSignal::CertificateExpired>(bind(&IotConfigurationManager::certificateExpired, confM, _1 )),
        exportable_callback<ConfigurationSignal::CertificateStateChanged>(bind(&IotConfigurationManager::certificateStateChanged, confM, _1, _2, _3 )),
        exportable_callback<ConfigurationSignal::MediaParametersChanged>(bind(&IotConfigurationManager::mediaParametersChanged, confM, _1 )),
        exportable_callback<ConfigurationSignal::MigrationEnded>(bind(&IotConfigurationManager::migrationEnded, confM, _1, _2 )),
    };

    // Presence event handlers
    const std::map<std::string, SharedCallback> presEvHandlers = {
        exportable_callback<PresenceSignal::NewServerSubscriptionRequest>(bind(&IotPresenceManager::newServerSubscriptionRequest, presM, _1)),
        exportable_callback<PresenceSignal::ServerError>(bind(&IotPresenceManager::serverError, presM, _1, _2, _3)),
        exportable_callback<PresenceSignal::NewBuddyNotification>(bind(&IotPresenceManager::newBuddyNotification, presM, _1, _2, _3, _4)),
        exportable_callback<PresenceSignal::SubscriptionStateChanged>(bind(&IotPresenceManager::subscriptionStateChanged, presM, _1, _2, _3)),
    };

    const std::map<std::string, SharedCallback> audioEvHandlers = {
        exportable_callback<AudioSignal::DeviceEvent>(bind(&IotConfigurationManager::audioDeviceEvent, confM)),
    };

#ifdef RING_VIDEO
    // Video event handlers
    const std::map<std::string, SharedCallback> videoEvHandlers = {
        exportable_callback<VideoSignal::DeviceEvent>(bind(&IotVideoManager::deviceEvent, videoM)),
        exportable_callback<VideoSignal::DecodingStarted>(bind(&IotVideoManager::startedDecoding, videoM, _1, _2, _3, _4, _5)),
        exportable_callback<VideoSignal::DecodingStopped>(bind(&IotVideoManager::stoppedDecoding, videoM, _1, _2, _3)),
    };
#endif

    if (!DRing::init(static_cast<DRing::InitFlag>(flags)))
        return -1;

    registerCallHandlers(callEvHandlers);
    registerConfHandlers(configEvHandlers);
    registerPresHandlers(presEvHandlers);
    registerPresHandlers(audioEvHandlers);
#ifdef RING_VIDEO
    registerVideoHandlers(videoEvHandlers);
#endif

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
    while(!pollNoMore_)
    {
        DRing::pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
