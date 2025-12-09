#include "stat_file.h"

// TODO: File and parse error handling

StatFile::StatFile(const char* path) {    
    file.open(path, std::ios::binary | std::ios::in | std::ios::out);

    if(!file) {
        create(path);
    } else {
        file >> jsonRoot;
    }
}

StatFile::~StatFile() {
    save();
    file.close();
}

void StatFile::create(const char* path) {
    file.open(path, std::ios::binary | std::ios::out | std::ios::trunc);
    
    if(!file) {
        printf("Unable to create %s \n", path);
        return;
    }

    formatData();
    save();
}

void StatFile::save() {
    file.seekp(0);
    file << jsonRoot.toStyledString();
}

void StatFile::formatData() {
    jsonRoot = Json::Value();

    jsonRoot["formatVersion"] = 1;
    jsonRoot["songs"] = Json::Value(Json::arrayValue);
}

void StatFile::songPlayed(const char* path) {
    Json::Value songs = jsonRoot["songs"];

    // Song exists
    for(int i = 0; i < songs.size(); i++) {
        Json::Value song = songs[i];

        if(song["path"].asString() == Json::String(path)) {
            jsonIncrement(song, "totalPlays", 1);
            songs[i] = song;
            jsonRoot["songs"] = songs;

            return;
        }
    }

    // Song doesn't exist
    Json::Value song;

    song["path"] = path;
    song["totalPlays"] = 1;

    songs.append(song);
    jsonRoot["songs"] = songs;
}

void jsonIncrement(Json::Value parent, const char* keyName, int offset) {
    if(parent.isMember(Json::String(keyName))) {
        parent[keyName] = parent[keyName].asInt() + offset;
    } else {
        parent[keyName] = offset;
    }
}
