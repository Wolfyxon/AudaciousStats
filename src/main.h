#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libaudcore/hook.h>
#include <libaudcore/audstrings.h>
#include <libaudcore/i18n.h>
#include <libaudcore/interface.h>
#include <libaudcore/playlist.h>
#include <libaudcore/plugin.h>
#include <libaudcore/preferences.h>
#include <libaudcore/runtime.h>
#include <stdio.h>

#include "util.h"
#include "stat_file.h"
#include "config.h"

class AudaciousStats : GeneralPlugin {
    public:
        static const PluginPreferences prefs;
        static const PreferencesWidget widgets[];
        static const char about[];

        static constexpr PluginInfo info = {
            N_("Audacious Stats"),
            N_("audaciousStats"),
            about,
            &prefs
        };
        
        constexpr AudaciousStats() : GeneralPlugin (info, false) {};

        bool init();
        void cleanup();

        static void _loop(void* data);
        static void _playing(void* data, void* user);

        static String getStatFilePath();
        static StatFile getStats();
        static SongData getCurrentSong();
        static const char* getCurrentFilename();
};

const PreferencesWidget AudaciousStats::widgets[] = {
    WidgetLabel (N_("<b>Audacious Stats settings</b>")),
    WidgetLabel (N_("NOTE: These are placeholders and don't work yet")),
    
    WidgetLabel (N_("<b>Garbage collection:</b>")),

    WidgetSpin(
        N_("Min song duration:"),
        WidgetInt(CONF_SECTION, CONF_MIN_SONG_DURATION),
        {0, 5000, 1, N_("s")}
    ),

    WidgetSpin(
        N_("Delete entries after:"),
        WidgetInt(CONF_SECTION, CONF_DELETE_AFTER_DAYS),
        {0, 36500, 1, N_("days")}
    ),

    WidgetSpin(
        N_("Don't delete if played over:"),
        WidgetInt(CONF_SECTION, CONF_DELETE_MAX_PLAYS),
        {0, 1000, 1, N_("times")}
    )
};

const PluginPreferences AudaciousStats::prefs = {{widgets}};

const char AudaciousStats::about[] = N_(
    "Audacious Stats\n"
    "by Wolfyxon\n"
    "\n"
    "This plugins tracks the amount of plays of your songs to determine what you listen to the most.\n"
    "This plugin is under development and currently there's no graphical interface. For now you have to view the stats JSON file. \n"
    "\n"
    "\nSource code & bug reports: \n"
    "https://github.com/Wolfyxon/AudaciousStats"
);
