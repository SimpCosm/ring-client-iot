/*
 *  Copyright (C) 2004-2017 Savoir-faire Linux Inc.
 *
 *  Author: Philippe Proulx <philippe.proulx@savoirfairelinux.com>
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

#include "iotvideomanager.h"
#include "client/videomanager.h"

IotVideoManager::IotVideoManager()
{}

auto
IotVideoManager::getDeviceList() -> decltype(DRing::getDeviceList())
{
    return DRing::getDeviceList();
}

auto
IotVideoManager::getCapabilities(const std::string& name) -> decltype(DRing::getCapabilities(name))
{
    return DRing::getCapabilities(name);
}

auto
IotVideoManager::getSettings(const std::string& name) -> decltype(DRing::getSettings(name))
{
    return DRing::getSettings(name);
}

void
IotVideoManager::applySettings(const std::string& name, const std::map<std::string, std::string>& settings)
{
    DRing::applySettings(name, settings);
}

void
IotVideoManager::setDefaultDevice(const std::string& dev)
{
    DRing::setDefaultDevice(dev);
}

auto
IotVideoManager::getDefaultDevice() -> decltype(DRing::getDefaultDevice())
{
    return DRing::getDefaultDevice();
}

void
IotVideoManager::startCamera()
{
    DRing::startCamera();
}

void
IotVideoManager::stopCamera()
{
    DRing::stopCamera();
}

auto
IotVideoManager::switchInput(const std::string& resource) -> decltype(DRing::switchInput(resource))
{
    return DRing::switchInput(resource);
}

auto
IotVideoManager::hasCameraStarted() -> decltype(DRing::hasCameraStarted())
{
    return DRing::hasCameraStarted();
}
