#include "main.h"

AudaciousRank aud_plugin_instance;

bool AudaciousRank::init() {
    hook_associate("playback begin", _playing, this);

    return true;
}

void AudaciousRank::cleanup() {
    
}

void AudaciousRank::_playing(void* data, void* user) {
    SongData song = getCurrentSong();
    
    if(!song.valid)
        return;

    printSongData(&song);

    StatFile stats = getStats();
    stats.songPlayed(song);

    stats.save();
}

String AudaciousRank::getStatFilePath() {
    const char* userPath = aud_get_path(AudPath::UserDir);
    const char* fileName = "/stats.json";

    size_t outputLen = strlen(userPath) + strlen(fileName);

    char res[outputLen];
    strcpy(res, userPath);
    strcat(res, fileName);
    
    return String(res);
}

StatFile AudaciousRank::getStats() {
    return StatFile(getStatFilePath());
}

const char* AudaciousRank::getCurrentFilename() {
    Playlist pl = Playlist::active_playlist();
    
    int pos = pl.get_position();

    if(pos == -1)
        return String("");
    
    String fileUri = pl.entry_filename(pos);

    return uri_to_filename(fileUri);
}

SongData AudaciousRank::getCurrentSong() {
    Playlist pl = Playlist::active_playlist();
    int pos = pl.get_position();

    if(pos == -1) {
        return {
            .valid = false
        };
    }

    String metaError;

    Tuple meta = pl.entry_tuple(pos, Playlist::GetMode::Wait, &metaError);
    meta.generate_fallbacks();

    if(!meta.valid()) {
        printf("Invalid metadata \n");
        return {
            .valid = false
        };
    }

    return {
        .valid = true,
        .title = meta.get_str(Tuple::Title),
        .artist = meta.get_str(Tuple::Artist),
        .filePath = String(uri_to_filename(pl.entry_filename(pos))),
        .duration = meta.get_int(Tuple::Length)
    };
}
