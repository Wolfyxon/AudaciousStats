#include "main.h"

AudaciousStats aud_plugin_instance;

bool AudaciousStats::init() {
    aud_config_set_defaults(CONF_SECTION, defaults);
    hook_associate("playback begin", _playing, this);

    try {
        StatFile stats = getStats();

        stats.cleanup({
            .deleteEntriesAfterDays = aud_get_int(CONF_SECTION, "delete_entries_after_days"),
            .deleteMissingAfterDays = aud_get_int(CONF_SECTION, "delete_missing_files_after_days"),
            .dontDeleteIfPlayedMoreThan = aud_get_int(CONF_SECTION, "dont_delete_if_played_more_than")
        });
    } catch(Json::Exception e) {
        char err[256];

        snprintf(err, sizeof(err), "Stat cleanup failed: ", e.what());
        aud_ui_show_error(err);
    }

    return true;
}

void AudaciousStats::cleanup() {
    hook_dissociate("playback begin", _playing, this);
}

void AudaciousStats::_playing(void* data, void* user) {
    SongData song = getCurrentSong();
    int minSongDuration = aud_get_int(CONF_SECTION, "min_song_duration");

    if(!song.valid)
        return;

    if(song.duration / 1000 < minSongDuration)
        return;

    printSongData(&song);

    StatFile stats = getStats();
    stats.songPlayed(song);
}

String AudaciousStats::getStatFilePath() {
    const char* userPath = aud_get_path(AudPath::UserDir);
    const char* fileName = "/stats.json";

    size_t outputLen = strlen(userPath) + strlen(fileName);

    char res[outputLen];
    strcpy(res, userPath);
    strcat(res, fileName);
    
    return String(res);
}

StatFile AudaciousStats::getStats() {
    return StatFile(getStatFilePath());
}

const char* AudaciousStats::getCurrentFilename() {
    Playlist pl = Playlist::active_playlist();
    
    int pos = pl.get_position();

    if(pos == -1)
        return String("");
    
    String fileUri = pl.entry_filename(pos);

    return uri_to_filename(fileUri);
}

SongData AudaciousStats::getCurrentSong() {
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
