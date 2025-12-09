#include "main.h"

AudaciousRank aud_plugin_instance;

bool AudaciousRank::init() {
    hook_associate("playback begin", _playing, this);

    return true;
}

void AudaciousRank::cleanup() {
    
}

void AudaciousRank::_playing(void* data, void* user) {
    printf("playing \n");

    StatFile stats = getStats();
    stats.songPlayed(AudaciousRank::getCurrentFilename());

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
