/*
 *  Copyright (C) 2004-2017 Savoir-faire Linux Inc.
 *
 *  Author: Edric Milaret <edric.ladent-milaret@savoirfairelinux.com>
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

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <getopt.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <json/json.h>

#include "dring/dring.h"
#include "dring/configurationmanager_interface.h"
#include "dring/account_const.h"
#include "logger.h"

using namespace std::placeholders;

static int ringFlags = 0;
bool loop = true;

static void
print_title()
{
    std::cout
        << "Ring Daemon " << DRing::version()
        << ", by Savoir-faire Linux 2004-2017" << std::endl
        << "http://www.ring.cx/" << std::endl
#ifdef RING_VIDEO
        << "[Video support enabled]" << std::endl
#endif
        << std::endl;
}

static void
print_usage()
{
    std::cout << std::endl <<
    "-c, --console \t- Log in console (instead of syslog)" << std::endl <<
    "-d, --debug \t- Debug mode (more verbose)" << std::endl <<
    "-p, --persistent \t- Stay alive after client quits" << std::endl <<
    "--auto-answer \t- Force automatic answer to incoming calls" << std::endl <<
    "-h, --help \t- Print help" << std::endl;
}

// Parse command line arguments, setting debug options or printing a help
// message accordingly.
// returns true if we should quit (i.e. help was printed), false otherwise
static bool
parse_args(int argc, char *argv[], bool& persistent)
{
    int consoleFlag = false;
    int debugFlag = false;
    int helpFlag = false;
    int versionFlag = false;
    int autoAnswer = false;

    const struct option long_options[] = {
        /* These options set a flag. */
        {"debug", no_argument, NULL, 'd'},
        {"console", no_argument, NULL, 'c'},
        {"persistent", no_argument, NULL, 'p'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"auto-answer", no_argument, &autoAnswer, true},
        {0, 0, 0, 0} /* Sentinel */
    };

    while (true) {
        /* getopt_long stores the option index here. */
        int option_index = 0;

        auto c = getopt_long(argc, argv, "dcphv", long_options, &option_index);

        // end of the options
        if (c == -1)
            break;

        switch (c) {
            case 'd':
                debugFlag = true;
                break;

            case 'c':
                consoleFlag = true;
                break;

            case 'p':
                persistent = true;
                break;

            case 'h':
            case '?':
                helpFlag = true;
                break;

            case 'v':
                versionFlag = true;
                break;

            default:
                break;
        }
    }

    if (helpFlag) {
        print_usage();
        return true;
    }

    if (versionFlag) {
        // We've always print the title/version, so we can just exit
        return true;
    }

    if (consoleFlag)
        ringFlags |= DRing::DRING_FLAG_CONSOLE_LOG;

    if (debugFlag)
        ringFlags |= DRing::DRING_FLAG_DEBUG;

    if (autoAnswer)
        ringFlags |= DRing::DRING_FLAG_AUTOANSWER;

    return false;
}

void IncomingMessages(const std::string& accountID, 
                    const std::string& from,
                    const std::map<std::string, std::string>& payloads)
{
    printf("accountID : %s\n", accountID.c_str());
    printf("from : %s\n", from.c_str());
    for (auto& it : payloads) {
        printf("%s : %s\n", it.first.c_str(), it.second.c_str());
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(it.second, root))
        {
            const Json::Value cmd = root["command"];
            const Json::Value mesg = cmd["mesg"];
            std::string uri = mesg["uri"].asString();
            std::string info = mesg["info"].asString();
            std::map<std::string, std::string> payloads;
            std::string mimetype("text/plain");
            payloads.insert(std::make_pair(mimetype, info));
            DRing::sendAccountTextMessage(accountID, uri, payloads);
        }
    }
}


int kbhit(void)
{
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);
    select(1, &read_fd, NULL, /*No writes*/NULL, /*No exceptions*/&tv);
    return FD_ISSET(0, &read_fd);
}

std::string parseCmd(std::string msg)
{
    Json::Value root;
    Json::Value cmd;
    std::string action = msg.substr(0, 4);
    if (action == "mesg") {
            std::string uri = msg.substr(5, 40);
            std::string info = msg.substr(46);
            Json::Value mesg;
            mesg["uri"] = uri;
            mesg["info"] = info;
            cmd["mesg"] = mesg;
    }
    root["command"] = cmd;
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(root);
    return output;
}
std::map<std::string, std::string> inputMessage()
{
    std::map<std::string, std::string> payloads;
    std::string mimetype("text/plain");
    std::string msg;
    getline(std::cin, msg);
    payloads.insert(std::make_pair(mimetype, parseCmd(msg)));
    return payloads;
}
static int
run()
{
 
    using SharedCallback = std::shared_ptr<DRing::CallbackWrapperBase>;
    using DRing::exportable_callback;
    using DRing::ConfigurationSignal;
    using std::bind;

    std::map<std::string, SharedCallback> configHandlers;
    configHandlers.insert(exportable_callback<ConfigurationSignal::IncomingAccountMessage>(bind(&IncomingMessages, _1, _2, _3)));
    
    if (!DRing::init(static_cast<DRing::InitFlag>(ringFlags))) {
        RING_ERR("DRing init error!");
        return -1;
    }
    
    registerConfHandlers(configHandlers);
    
    if (!DRing::start()) {
        RING_ERR("DRing start error!");
        return -1;
    }

    const std::vector<std::string> accountList(DRing::getAccountList());
    RING_INFO("********ADD ACCOUNT**********");
    if (accountList.empty()) {
        RING_INFO("TRYING TO ADD ACCOUNT");
        auto details = DRing::getAccountTemplate(DRing::Account::ProtocolNames::RING);
        details["Account.alias"] = "loveST";
        details["Account.archivePassword"] = "loveST1MARING";
        details["Account.deviceID"] = "6bf905c7894c620894e0b40d0ef9f468f2c358d1";
        details["Account.deviceName"] = "cosmos";
        details["Account.displayName"] = "loveST";
        details["Account.hostname"] = "bootstrap.ring.cx";
        details["Account.username"] = "ring:3e4ae4861d1e888522b7c1530c202f8c43e99d71";
        details["RingNS.account"] = "ccd0eeaf90ca0d75a6fa277fee8b822a32ef93fa";
        DRing::addAccount(details);
    }
    else {
        if (!accountList.empty()) {
            for (auto &item : accountList)
                RING_INFO("%s", item.c_str());
        }
    }

   // std::map<std::string, std::string> payloads;
    std::string accountID(accountList.front());
    std::string toUri("ring:fd9d8b64610500a8f7b87579fbfc75562ff97f3c");

    RING_INFO("-----------------------------LOOP BEGIN----------------------");
    while (loop) {
        DRing::pollEvents();
        if (kbhit()) {
            std::map<std::string, std::string> payloads(inputMessage());
            DRing::sendAccountTextMessage(accountID, toUri, payloads);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}

static void
interrupt()
{
    loop = false;
}

static void
signal_handler(int code)
{
    std::cerr << "Caught signal " << code
              << ", terminating..." << std::endl;
    // Unset signal handlers
    signal(SIGINT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);

    interrupt();
}

int
main(int argc, char *argv [])
{
    // make a copy as we don't want to modify argv[0], copy it to a vector to
    // guarantee that memory is correctly managed/exception safe
    std::string programName {argv[0]};
    std::vector<char> writable(programName.size() + 1);
    std::copy(programName.begin(), programName.end(), writable.begin());

	print_title();

    bool persistent = false;
    if (parse_args(argc, argv, persistent))
        return 0;

    // TODO: Block signals for all threads but the main thread, decide how/if we should
    // handle other signals
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    return run();
}
