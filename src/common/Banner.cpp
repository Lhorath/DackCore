/*
 * Copyright (C) 2009-2019 ImmortalCore <https://worldofimmortality.com/>
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Banner.h"
#include "GitRevision.h"
#include "StringFormat.h"

void Trinity::Banner::Show(char const* applicationName, void(*log)(char const* text), void(*logExtraInfo)())
{
    log(Trinity::StringFormat("%s (%s)", GitRevision::GetFullVersion(), applicationName).c_str());
    log("<Ctrl-C> to stop.\n");
    log(" ");
    log(" 8888888  Copyright 2009 - 2019 World of Immortality  888             888       .d8888b.                           ");
    log("   888                                                888             888      d88P  Y88b                          ");
    log("   888                                                888             888      888    888                          ");
    log("   888   88888b.d88b.  88888b.d88b.   .d88b.  888d888 888888  8888b.  888      888         .d88b.  888d888 .d88b.  ");
    log("   888   888 '888 '88b 888 '888 '88b d88''88b 888P'   888        '88b 888      888        d88''88b 888P'  d8P  Y8b ");
    log("   888   888  888  888 888  888  888 888  888 888     888    .d888888 888      888    888 888  888 888    88888888 ");
    log("   888   888  888  888 888  888  888 Y88..88P 888     Y88b.  888  888 888      Y88b  d88P Y88..88P 888    Y8b.     ");
    log(" 8888888 888  888  888 888  888  888  'Y88P'  888      'Y888 'Y888888 888       'Y8888P'   'Y88P'  888     'Y8888  ");
    log(" ");
    log(" https://worldofimmortality.com                                                 Devs: Hellfrost, Lhorath & Grimfate");
    log(" ");
    log(" For use by World of Immortality & associated Servers Only                            Version 1.2 - The DK Zone Fix");

    if (logExtraInfo)
        logExtraInfo();
}
