/*
 *  Copyright (C) 2026 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSXC_MACSTYLE_H
#define KEEPASSXC_MACSTYLE_H

#include "gui/styles/base/BaseStyle.h"

/**
 * Theme following the macOS system appearance: light or dark from the OS, the highlight
 * colour from the system accent colour, and the remaining palette from AppKit's semantic
 * colours. Selectable on macOS only.
 */
class MacStyle : public BaseStyle
{
    Q_OBJECT

public:
    MacStyle();
    QPalette standardPalette() const override;
};

#endif // KEEPASSXC_MACSTYLE_H
