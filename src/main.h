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

        static constexpr PluginInfo info = {
            N_("Audacious Stats"),
            N_("idk"), // TODO: figure out what this is
            nullptr,
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
    WidgetLabel (N_("<b>Hello there</b>")),
    WidgetCheck (N_("GENERAL KENOBI"),
    WidgetBool ("some_setting_probably", "also_setting_idk"))
};

const PluginPreferences AudaciousRank::prefs = {{widgets}};
