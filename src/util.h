#pragma once

#include <libaudcore/audstrings.h>
#include <libaudcore/tuple.h>
#include <json/json.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    bool valid;
    String title;
    String artist;
    String filePath;
    int duration; // miliseconds
} SongData;
bool strempty(const char* str);
const char* strc(String str);
bool fileExists(const char* path);

SongData songFromJson(Json::Value json);
bool songsEqual(SongData* a, SongData* b);
void printSongData(SongData* songData);

void jsonIncrement(Json::Value* parent, const char* keyName, int offset);
const char* jsonGetStrOrEmpty(Json::Value value, const char* key);
String jsonGetStringOrEmpty(Json::Value value, const char* key);
void jsonSetStrIfNotEmpty(Json::Value* value, const char* key, const char* str);