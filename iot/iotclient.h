/*
 *  Copyright (C) 2004-2017 Savoir-faire Linux Inc.
 *
 *  Author: Pierre-Luc Beaudoin <pierre-luc.beaudoin@savoirfairelinux.com>
 *  Author: Guillaume Roguez <guillaume.roguez@savoirfairelinux.com>
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

#pragma once

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <memory>

#include "dring/dring.h"
#include "dring/callmanager_interface.h"
#include "dring/configurationmanager_interface.h"
#include "dring/presencemanager_interface.h"
#include "iotcallmanager.h"
#include "iotconfigurationmanager.h"
#include "iotpresencemanager.h"

#ifdef RING_VIDEO
#include "dring/videomanager_interface.h"
#include "iotvideomanager.h"
#endif

class IotClient {
    public:
        IotClient(int flags, bool persistent);
        ~IotClient();

        int event_loop() noexcept;
        int exit() noexcept;

    private:
        int initLibrary(int flags);
        void finiLibrary() noexcept;

        bool pollNoMore_ = false;

        std::unique_ptr<IotCallManager>          callManager_;
        std::unique_ptr<IotConfigurationManager> configurationManager_;
        std::unique_ptr<IotPresenceManager>      presenceManager_;

#ifdef RING_VIDEO
        std::unique_ptr<IotVideoManager>         videoManager_;
#endif
};
