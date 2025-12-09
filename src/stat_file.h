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
        std::fstream file;
        Json::Value jsonRoot;

        void addSong(SongData song);
        void create(const char* path);
        void formatData();
};
