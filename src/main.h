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

class AudaciousRank : GeneralPlugin {
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
        
        constexpr AudaciousRank() : GeneralPlugin (info, false) {};

        bool init();
        void cleanup();

        static void _loop(void* data);
        static void _playing(void* data, void* user);

        static String getStatFilePath();
        static StatFile getStats();
        static const char* getCurrentFilename();
};

// Change later
const PreferencesWidget AudaciousRank::widgets[] = {
    WidgetLabel (N_("<b>Audacious Stats settings</b>"))
};

const PluginPreferences AudaciousRank::prefs = {{widgets}};

const char AudaciousRank::about[] = N_(
    "Audacious Stats\n"
    "by Wolfyxon\n"
    "\n"
    "This plugins tracks the amount of plays of your songs to determine what you listen to the most.\n"
    "This plugin is under development and currently there's no graphical interface. For now you have to view the stats JSON file. \n"
    "\n"
    "\nSource code & bug reports: \n"
    "https://github.com/Wolfyxon/AudaciousStats"
);
