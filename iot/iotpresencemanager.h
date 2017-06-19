/*
 *  Copyright (C) 2013-2017 Savoir-faire Linux Inc.
 *
 *  Author: Patrick Keroulas <patrick.keroulas@savoirfairelinux.com>
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

#ifndef __RING_IOTPRESENCEMANAGER_H__
#define __RING_IOTPRESENCEMANAGER_H__

#include <vector>
#include <map>
#include <string>

#if __GNUC__ >= 5 || (__GNUC__ >=4 && __GNUC_MINOR__ >= 6)
/* This warning option only exists for gcc 4.6.0 and greater. */
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

class IotPresenceManager :
{
    public:
        IotPresenceManager();

        // Methods
        void publish(const std::string& accountID, const bool& status, const std::string& note);
        void answerServerRequest(const std::string& uri, const bool& flag);
        void subscribeBuddy(const std::string& accountID, const std::string& uri, const bool& flag);
        std::vector<std::map<std::string, std::string>> getSubscriptions(const std::string& accountID);
        void setSubscriptions(const std::string& accountID, const std::vector<std::string>& uris);
};

#endif // __RING_IOTPRESENCEMANAGER_H__
