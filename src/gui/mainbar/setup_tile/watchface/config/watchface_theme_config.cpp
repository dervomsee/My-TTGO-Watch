/****************************************************************************
 *   Aug 11 17:13:51 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "watchface_theme_config.h"

watchface_theme_config_t::watchface_theme_config_t() : BaseJsonConfig( WATCHFACE_THEME_JSON_CONFIG_FILE ) {}

bool watchface_theme_config_t::onSave(JsonDocument& doc ) {
    int32_t labelcount = 0;

    doc["api_level"] = dial.api_level;

    if ( dial.dial.enable ) {
        doc["dial"]["enable"] = dial.dial.enable;
        doc["dial"]["x_offset"] = dial.dial.x_offset;
        doc["dial"]["y_offset"] = dial.dial.y_offset;
    }
    if ( dial.hour.enable ) {
        doc["hour"]["enable"] = dial.hour.enable;
        doc["hour"]["x_offset"] = dial.hour.x_offset;
        doc["hour"]["y_offset"] = dial.hour.y_offset;
    }
    if ( dial.min.enable ) {
        doc["min"]["enable"] = dial.min.enable;
        doc["min"]["smooth"] = dial.min.smooth;
        doc["min"]["x_offset"] = dial.min.x_offset;
        doc["min"]["y_offset"] = dial.min.y_offset;
    }
    if ( dial.sec.enable ) {
        doc["sec"]["enable"] = dial.sec.enable;;
        doc["sec"]["x_offset"] = dial.sec.y_offset;
        doc["sec"]["y_offset"] = dial.sec.y_offset;
    }

    if ( dial.hour_shadow.enable ) {
        doc["hour_shadow"]["enable"] = dial.hour_shadow.enable;
        doc["hour_shadow"]["x_offset"] = dial.hour_shadow.x_offset;
        doc["hour_shadow"]["y_offset"] = dial.hour_shadow.y_offset;
    }
    if ( dial.min_shadow.enable ) {
        doc["min_shadow"]["enable"] = dial.min_shadow.enable;
        doc["min_shadow"]["x_offset"] = dial.min_shadow.x_offset;
        doc["min_shadow"]["y_offset"] = dial.min_shadow.y_offset;
    }
    if ( dial.sec_shadow.enable ) {
        doc["sec_shadow"]["enable"] = dial.sec_shadow.enable;
        doc["sec_shadow"]["x_offset"] = dial.sec_shadow.x_offset;
        doc["sec_shadow"]["y_offset"] = dial.sec_shadow.y_offset;
    }

    for( int i = 0 ; i < WATCHFACE_LABEL_NUM ; i++ ) {
        if ( dial.label[ i ].enable ) {
            doc["label"][ labelcount ]["enable"] = dial.label[ i ].enable;
            doc["label"][ labelcount ]["type"] = dial.label[ i ].type;
            doc["label"][ labelcount ]["label"] = dial.label[ i ].label;
            doc["label"][ labelcount ]["font"] = dial.label[ i ].font;
            doc["label"][ labelcount ]["font_color"] = dial.label[ i ].font_color;
            doc["label"][ labelcount ]["font_size"] = dial.label[ i ].font_size;
            doc["label"][ labelcount ]["align"] = dial.label[ i ].align;
            doc["label"][ labelcount ]["hide_interval"] = dial.label[ i ].hide_interval;
            doc["label"][ labelcount ]["x_offset"] = dial.label[ i ].x_offset;
            doc["label"][ labelcount ]["y_offset"] = dial.label[ i ].y_offset;
            doc["label"][ labelcount ]["x_size"] = dial.label[ i ].x_size;
            doc["label"][ labelcount ]["y_size"] = dial.label[ i ].y_size;
            labelcount++;
        }
    }
    
    return true;
}

bool watchface_theme_config_t::onLoad(JsonDocument& doc) {
    dial.api_level = doc["api_level"] | API_LEVEL;

    dial.dial.enable = doc["dial"]["enable"] | false;
    dial.dial.x_offset = doc["dial"]["x_offset"] | 0;
    dial.dial.y_offset = doc["dial"]["y_offset"] | 0;

    dial.hour.enable = doc["hour"]["enable"] | false;
    dial.hour.x_offset = doc["hour"]["x_offset"] | 0;
    dial.hour.y_offset = doc["hour"]["y_offset"] | 0;
    dial.min.enable = doc["min"]["enable"] | false;
    dial.min.smooth = doc["min"]["smooth"] | false;
    dial.min.x_offset = doc["min"]["x_offset"] | 0;
    dial.min.y_offset = doc["min"]["y_offset"] | 0;
    dial.sec.enable = doc["sec"]["enable"] | false;
    dial.sec.x_offset = doc["sec"]["x_offset"] | 0;
    dial.sec.y_offset = doc["sec"]["y_offset"] | 0;

    dial.hour_shadow.enable = doc["hour_shadow"]["enable"] | false;
    dial.hour_shadow.x_offset = doc["hour_shadow"]["x_offset"] | 5;
    dial.hour_shadow.y_offset = doc["hour_shadow"]["y_offset"] | 5;
    dial.min_shadow.enable = doc["min_shadow"]["enable"] | false;
    dial.min_shadow.x_offset = doc["min_shadow"]["x_offset"] | 5;
    dial.min_shadow.y_offset = doc["min_shadow"]["y_offset"] | 5;
    dial.sec_shadow.enable = doc["sec_shadow"]["enable"] | false;
    dial.sec_shadow.x_offset = doc["sec_shadow"]["x_offset"] | 5;
    dial.sec_shadow.y_offset = doc["sec_shadow"]["y_offset"] | 5;

    for( int i = 0 ; i < WATCHFACE_LABEL_NUM ; i++ ) {
        dial.label[ i ].enable = doc["label"][i]["enable"] | false;
        strncpy( dial.label[ i ].type, doc["label"][i]["type"] | "text", sizeof( dial.label[ i ].type ) );
        strncpy( dial.label[ i ].label, doc["label"][i]["label"] | "" , sizeof( dial.label[ i ].label ) );
        strncpy( dial.label[ i ].font, doc["label"][i]["font"] | "Ubuntu" , sizeof( dial.label[ i ].font ) );
        dial.label[ i ].font_size = doc["label"][i]["font_size"] | 12;
        strncpy( dial.label[ i ].font_color, doc["label"][i]["font_color"] | "#ffffff" , sizeof( dial.label[ i ].font_color ) );
        strncpy( dial.label[ i ].align, doc["label"][i]["align"] | "center" , sizeof( dial.label[ i ].align ) );
        dial.label[ i ].hide_interval = doc["label"][i]["hide_interval"] | 0;
        dial.label[ i ].x_offset = doc["label"][i]["x_offset"] | 0;
        dial.label[ i ].y_offset = doc["label"][i]["y_offset"] | 0;
        dial.label[ i ].x_size = doc["label"][i]["x_size"] | 0;
        dial.label[ i ].y_size = doc["label"][i]["y_size"] | 0;
    }
    return true;
}

bool watchface_theme_config_t::onDefault( void ) {
    dial.api_level = API_LEVEL;
    /**
     * set default dial
     */
    dial.dial.enable = true;
    dial.dial.x_offset = 0;
    dial.dial.y_offset = 0;
    /**
     * set default index
     */
    dial.hour.enable = true;
    dial.hour.x_offset = 0;
    dial.hour.y_offset = 0;
    dial.min.enable = true;
    dial.min.smooth = true;
    dial.min.x_offset = 0;
    dial.min.y_offset = 0;
    dial.sec.enable = true;
    dial.sec.x_offset = 0;
    dial.sec.y_offset = 0;
    /**
     * set default shadow
     */
    dial.hour_shadow.enable = true;
    dial.hour_shadow.x_offset = 5;
    dial.hour_shadow.y_offset = 5;
    dial.min_shadow.enable = true;
    dial.min_shadow.x_offset = 5;
    dial.min_shadow.y_offset = 5;
    dial.sec_shadow.enable = true;
    dial.sec_shadow.x_offset = 5;
    dial.sec_shadow.y_offset = 5;
    /**
     * clear all labels
     */
    for( int i = 0 ; i < WATCHFACE_LABEL_NUM ; i++ ) {
        dial.label[ i ].enable = false;
        strncpy( dial.label[ i ].type, "text", sizeof( dial.label[ i ].type ) );
        strncpy( dial.label[ i ].label, "n/a" , sizeof( dial.label[ i ].label ) );
        strncpy( dial.label[ i ].font, "Ubuntu" , sizeof( dial.label[ i ].font ) );
        dial.label[ i ].font_size = 12;
        strncpy( dial.label[ i ].font_color, "#000000" , sizeof( dial.label[ i ].font_color ) );
        strncpy( dial.label[ i ].align, "center" , sizeof( dial.label[ i ].align ) );
        dial.label[ i ].hide_interval = 0;
        dial.label[ i ].x_offset = 0;
        dial.label[ i ].y_offset = 0;
        dial.label[ i ].x_size = 0;
        dial.label[ i ].y_size = 0;
    }
    /**
     * setup default date label
     */
    dial.label[ 0 ].enable = true;
    strncpy( dial.label[ 0 ].type, "date", sizeof( dial.label[ 0 ].type ) );
    strncpy( dial.label[ 0 ].label, "%d.%b", sizeof( dial.label[ 0 ].label ) );
    strncpy( dial.label[ 0 ].font, "Ubuntu" , sizeof( dial.label[ 0 ].font ) );
    dial.label[ 0 ].font_size = 32;
    strncpy( dial.label[ 0 ].font_color, "#000000", sizeof( dial.label[ 0 ].font_color ) );
    strncpy( dial.label[ 0 ].align, "center" , sizeof( dial.label[ 0 ].align ) );
    dial.label[ 0 ].hide_interval = 0;
    dial.label[ 0 ].x_offset = 64;
    dial.label[ 0 ].y_offset = 64;
    dial.label[ 0 ].x_size = 112;
    dial.label[ 0 ].y_size = 40;

    return true;
}