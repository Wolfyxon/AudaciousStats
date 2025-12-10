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

void StatFile::songPlayed(SongData songData) {
    Json::Value songs = jsonRoot["songs"];
    
    for(int i = 0; i < songs.size(); i++) {
        Json::Value songJson = songs[i];
        SongData song = songFromJson(songJson);

        if(songsEqual(&songData, &song)) {
            jsonIncrement(&songJson, "totalPlays", 1);
            songJson["lastPlay"] = std::time(NULL);
            
            songs[i] = songJson;
            jsonRoot["songs"] = songs;

            return;
        }
    }

    addSong(songData);
}

void StatFile::addSong(SongData songData) {
    Json::Value songs = jsonRoot["songs"];
    Json::Value song;
    std::time_t now = std::time(NULL);

    song["path"] = Json::String(songData.filePath);
    song["lastPlay"] = Json::Int(now);
    song["firstPlay"] = Json::Int(now);
    song["totalPlays"] = 1;

    jsonSetStrIfNotEmpty(&song, "title", songData.title);
    jsonSetStrIfNotEmpty(&song, "artist", songData.artist);
    
    songs.append(song);
    jsonRoot["songs"] = songs;
}

void StatFile::cleanup(StatFileCleanupConfig config) {
    std::time_t now = std::time(NULL);
    Json::Value songs = jsonRoot["songs"];
    Json::Value newSongs = Json::arrayValue;

    for(int i = 0; i < songs.size(); i++) {
        Json::Value song = songs[i];

        int playCount = song["totalPlays"].asInt();
        time_t timeDiff = now - song["lastPlay"].asInt();
        time_t daysDiff = ((timeDiff / 60) / 60) / 24;
        
        if(config.deleteEntriesAfterDays > daysDiff || playCount > config.dontDeleteIfPlayedMoreThan) {
            newSongs.append(song);
        }
    }

    jsonRoot["songs"] = newSongs;
}
