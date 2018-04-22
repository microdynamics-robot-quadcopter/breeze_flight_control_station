/******************************************************************************
 * Software License Agreement (GPL V3 License)
 *
 * Copyright (C) 2017 qijiabo
 * Copyright (c) 2018 myyerrol(Team MicroDynamics)
 *
 * This file is part of breeze_flight_control_station.
 *
 * breeze_flight_control_station is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.

 * breeze_flight_control_station is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with breeze_flight_control_station.  If not, see
 * <http://www.gnu.org/licenses/>.
 ******************************************************************************

 ******************************************************************************
 * File:
 * fcs_custom_tab_style.h
 *
 * Author:
 * qijiabo
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * qijiabo       2017.07.04     --            Finish custom tab style
 * myyerrol      2018.03.14     1.0.0         Modify custom tab style
 *
 * Description:
 * This .h file defines some elements for implementing the custom tab style of
 * QTabWidget according to qijiabo's tutorial.
 *****************************************************************************/

#ifndef FCS_CUSTOM_TAB_STYLE_H
#define FCS_CUSTOM_TAB_STYLE_H

#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionTab>

class FCSCustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type,
                           const QStyleOption *option,
                           const QSize &size,
                           const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);

        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rheight() = 50;
            s.rwidth()  = 100;
        }

        return s;
    }
    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab =
                qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect rect = tab->rect;
                painter->save();
                painter->setPen(Qt::gray);
                painter->drawRect(rect.adjusted(0, 0, 0, -1));
                painter->restore();
                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(Qt::gray);
                    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    painter->drawRect(rect.adjusted(0, 0, 0, -1));
                    painter->restore();
                }
                else {
                    ;
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                painter->drawText(rect, tab->text, option);
                return;
            }
            else {
                ;
            }
        }
        else {
            ;
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
        else {
            ;
        }
    }
};

#endif // FCS_CUSTOM_TAB_STYLE_H
