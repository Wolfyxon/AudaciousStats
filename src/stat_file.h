#pragma once

#include <libaudcore/audstrings.h>
#include <json/json.h>
#include <fstream>

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

void jsonIncrement(Json::Value parent, const char* keyName, int offset);

class StatFile {
    public:
        StatFile(const char* path);
        ~StatFile();

        void save();
        void songPlayed(const char* path);
    private:
        std::fstream file;
        Json::Value jsonRoot;

        void create(const char* path);
        void formatData();
};
