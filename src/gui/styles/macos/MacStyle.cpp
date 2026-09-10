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

#include "MacStyle.h"

#include "gui/osutils/macutils/MacUtils.h"

namespace
{
    // Palette tokens, light and dark, taken from the AppKit semantic colours of the same name.
    struct MacPalette
    {
        QRgb window; // windowBackgroundColor
        QRgb content; // controlBackgroundColor / textBackgroundColor
        QRgb alternateRow; // alternatingContentBackgroundColors
        QRgb button; // secondary push button fill
        QRgb selectionInactive; // unemphasizedSelectedContentBackgroundColor
        QRgb accentFallback; // controlAccentColor when AppKit cannot supply it
        QRgb link; // linkColor
        QRgb label; // labelColor, alpha applied over the surface it sits on
        // labelColor and its secondary, tertiary and quaternary tiers
        qreal labelOpacity[4];
    };

    const MacPalette LightPalette =
        {0xECECEC, 0xFFFFFF, 0xF4F5F5, 0xFFFFFF, 0xDCDCDC, 0x007AFF, 0x0068DA, 0x000000, {0.85, 0.50, 0.25, 0.10}};

    const MacPalette DarkPalette =
        {0x323232, 0x1E1E1E, 0x262626, 0x616161, 0x464646, 0x0A84FF, 0x419CFF, 0xFFFFFF, {0.85, 0.55, 0.25, 0.10}};

    QColor overlay(QRgb ground, QRgb ink, qreal opacity)
    {
        const QColor g(ground), i(ink);
        return QColor::fromRgbF(g.redF() + (i.redF() - g.redF()) * opacity,
                                g.greenF() + (i.greenF() - g.greenF()) * opacity,
                                g.blueF() + (i.blueF() - g.blueF()) * opacity);
    }
} // namespace

MacStyle::MacStyle()
    : BaseStyle()
{
}

QPalette MacStyle::standardPalette() const
{
    const bool dark = macUtils()->isDarkMode();
    const auto& t = dark ? DarkPalette : LightPalette;

    auto accent = macUtils()->accentColor();
    if (!accent.isValid()) {
        accent = QColor(t.accentFallback);
    }

    const auto label = [&t](QRgb ground, int tier) { return overlay(ground, t.label, t.labelOpacity[tier]); };
    const QColor windowText = label(t.window, 0);
    const QColor text = label(t.content, 0);
    const QColor buttonText = label(t.button, 0);
    const QColor secondary = label(t.window, 1);
    const QColor tertiary = label(t.window, 2);
    const QColor separator = label(t.window, 3);

    auto palette = BaseStyle::standardPalette();
    palette.setColor(QPalette::All, QPalette::Window, t.window);
    palette.setColor(QPalette::All, QPalette::WindowText, windowText);
    palette.setColor(QPalette::Disabled, QPalette::WindowText, tertiary);

    palette.setColor(QPalette::All, QPalette::Base, t.content);
    palette.setColor(QPalette::All, QPalette::AlternateBase, t.alternateRow);
    palette.setColor(QPalette::All, QPalette::Text, text);
    palette.setColor(QPalette::Disabled, QPalette::Text, label(t.content, 2));
    palette.setColor(QPalette::All, QPalette::PlaceholderText, label(t.content, 2));
    palette.setColor(QPalette::All, QPalette::BrightText, Qt::white);

    palette.setColor(QPalette::All, QPalette::Button, t.button);
    palette.setColor(QPalette::All, QPalette::ButtonText, buttonText);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, label(t.button, 2));

    palette.setColor(QPalette::All, QPalette::ToolTipBase, t.window);
    palette.setColor(QPalette::All, QPalette::ToolTipText, windowText);

    palette.setColor(QPalette::Active, QPalette::Highlight, accent);
    palette.setColor(QPalette::Inactive, QPalette::Highlight, t.selectionInactive);
    palette.setColor(QPalette::Disabled, QPalette::Highlight, t.selectionInactive);
    palette.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);
    palette.setColor(QPalette::Inactive, QPalette::HighlightedText, windowText);
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, tertiary);

    palette.setColor(QPalette::All, QPalette::Light, t.content);
    palette.setColor(QPalette::All, QPalette::Midlight, t.alternateRow);
    palette.setColor(QPalette::All, QPalette::Mid, separator);
    palette.setColor(QPalette::All, QPalette::Dark, tertiary);
    palette.setColor(QPalette::All, QPalette::Shadow, secondary);

    palette.setColor(QPalette::All, QPalette::Link, t.link);
    palette.setColor(QPalette::All, QPalette::LinkVisited, t.link);
    palette.setColor(QPalette::Disabled, QPalette::Link, tertiary);
    palette.setColor(QPalette::Disabled, QPalette::LinkVisited, tertiary);

    return palette;
}
