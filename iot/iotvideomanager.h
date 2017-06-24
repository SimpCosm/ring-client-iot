/*
 *  Copyright (C) 2012-2017 Savoir-faire Linux Inc.
 *
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

#ifndef __RING_IOTVIDEOMANAGER_H__
#define __RING_IOTVIDEOMANAGER_H__

#include <vector>
#include <map>
#include <string>

#pragma GCC diagnostic warning "-Wignored-qualifiers"

#if __GNUC__ >= 5 || (__GNUC__ >=4 && __GNUC_MINOR__ >= 6)
/* This warning option only exists for gcc 4.6.0 and greater. */
#pragma GCC diagnostic warning "-Wunused-but-set-variable"
#endif

class IotVideoManager
{
    public:
        IotVideoManager();

        // Methods
        std::vector<std::string> getDeviceList();
        std::map<std::string, std::map<std::string, std::vector<std::string>>> getCapabilities(const std::string& name);
        std::map<std::string, std::string> getSettings(const std::string& name);
        void applySettings(const std::string& name, const std::map<std::string, std::string>& settings);
        void setDefaultDevice(const std::string& dev);
        std::string getDefaultDevice();
        void startCamera();
        void stopCamera();
        bool switchInput(const std::string& resource);
        bool hasCameraStarted();
};

#endif // __RING_IOTVIDEOMANAGER_H__
