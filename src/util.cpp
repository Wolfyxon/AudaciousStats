#include "util.h"

bool songsEqual(SongData* a, SongData* b) {
    return (
        a->filePath == b->filePath ||
        (
            !strempty(a->title) && !strempty(b->title) &&
            !strempty(a->artist) && !strempty(b->artist) &&
            a->title == b->title && a->artist == b->artist
        )
    );
}

SongData songFromJson(Json::Value json) {
    if(!json.isObject()) {
        return {
            .valid = false
        };
    }

    return {
        .valid = true,
        .title = jsonGetStringOrEmpty(json, "title"),
        .artist = jsonGetStringOrEmpty(json, "artist"),
        .filePath = jsonGetStringOrEmpty(json, "path")
    };
}

void jsonIncrement(Json::Value parent, const char* keyName, int offset) {
    if(parent.isMember(Json::String(keyName))) {
        parent[keyName] = parent[keyName].asInt() + offset;
    } else {
        parent[keyName] = offset;
    }
}

bool strempty(const char* str) {
    return strlen(str) == 0;
}

const char* jsonGetStrOrEmpty(Json::Value value, const char* key) {
    if(!value.isObject())
        return "";
    if(!value.isMember(key))
        return "";

    return value[key].asCString();
}

String jsonGetStringOrEmpty(Json::Value value, const char* key) {
    return String(jsonGetStrOrEmpty(value, key));
}

void jsonSetStrIfNotEmpty(Json::Value* value, const char* key, const char* str) {
    if(str != nullptr && !strempty(str)) {
        (*value)[key] = str;
    }
}

const char* strc(String str) {
    return (const char*) str;
}

void printSongData(SongData* songData) {
    if(!songData->valid) {
        printf("Invalid song! \n");
    }

    printf("Title: '%s' Artist: '%s' Path: '%s'\n", strc(songData->title), strc(songData->artist), strc(songData->filePath));
}

