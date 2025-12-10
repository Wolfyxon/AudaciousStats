#pragma once

#include <libaudcore/audstrings.h>
#include <libaudcore/tuple.h>
#include <json/json.h>
#include <fstream>
#include <ctime>

#include "util.h"

/*
Example stats JSON

{
    "formatVersion": 1,
    songs: [
        {
            "path": "/home/person/Music/coolSong.mp3",
            "totalPlays": 103
        }
    ]
}

*/

typedef struct {
    int deleteEntriesAfterDays;
    int deleteMissingAfterDays;
    int dontDeleteIfPlayedMoreThan;
} StatFileCleanupConfig;

class StatFile {
    public:
        StatFile(const char* path);
        ~StatFile();

        void save();
        void songPlayed(SongData songData);
        void cleanup(StatFileCleanupConfig config);
    private:
        String path;
        std::fstream file;
        Json::Value jsonRoot;
        bool writeMode = false;

        void addSong(SongData song);
        void fillEntry(Json::Value* json, SongData* song);
        void create();
        void formatData();
};
