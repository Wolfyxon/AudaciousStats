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

bool fileExists(const char* path);
bool songsEqual(SongData* a, SongData* b);
SongData songFromJson(Json::Value json);
void jsonIncrement(Json::Value* parent, const char* keyName, int offset);
bool strempty(const char* str);
const char* jsonGetStrOrEmpty(Json::Value value, const char* key);
String jsonGetStringOrEmpty(Json::Value value, const char* key);
void jsonSetStrIfNotEmpty(Json::Value* value, const char* key, const char* str);
const char* strc(String str);
void printSongData(SongData* songData);