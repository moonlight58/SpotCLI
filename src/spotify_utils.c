#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void spotify_free_track_list(SpotifyTrackList *list) {
    if (!list) return;
    free(list->tracks);
    free(list);
}

void spotify_free_artist_list(SpotifyArtistList *list) {
    if (!list) return;
    free(list->artists);
    free(list);
}

void spotify_free_album_list(SpotifyAlbumList *list) {
    if (!list) return;
    free(list->albums);
    free(list);
}

void spotify_free_playlist_list(SpotifyPlaylistList *list) {
    if (!list) return;
    free(list->playlists);
    free(list);
}

void spotify_free_player_state(SpotifyPlayerState *state) {
    if (!state) return;
    free(state);
}

void spotify_print_track(SpotifyTrack *track, int index) {
    printf("%d. %s\n", index, track->name);
    printf("   Artist: %s\n", track->artist);
    printf("   Album: %s\n", track->album);
    printf("   Duration: %d:%02d\n", 
           track->duration_ms / 60000, 
           (track->duration_ms / 1000) % 60);
    printf("   ID: %s\n", track->id);
}

void spotify_print_artist(SpotifyArtist *artist, int index) {
    printf("%d. %s\n", index, artist->name);
    printf("   Followers: %d\n", artist->followers);
    printf("   Popularity: %d/100\n", artist->popularity);
    if (strlen(artist->genres) > 0) {
        printf("   Genres: %s\n", artist->genres);
    }
    printf("   ID: %s\n", artist->id);
}

void spotify_print_album(SpotifyAlbum *album, int index) {
    printf("%d. %s\n", index, album->name);
    printf("   Artist: %s\n", album->artist);
    printf("   ID: %s\n", album->id);
}

void spotify_print_playlist(SpotifyPlaylist *playlist, int index) {
    printf("%d. %s\n", index, playlist->name);
    printf("   Tracks: %d\n", playlist->count_tracks);
    printf("   Public: %s\n", playlist->is_public ? "Yes" : "No");
    printf("   ID: %s\n", playlist->id);
}

void spotify_print_player_state(SpotifyPlayerState *state) {
    if (!state) {
        printf("No playback state available\n");
        return;
    }
    
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                      SPOTIFY PLAYER STATE                      ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    
    // Track info
    printf("║ Track: %s\n", state->track_name);
    printf("║ Artist: %s\n", state->artist_name);
    printf("║ Album: %s\n", state->album_name);
    
    // Progress
    int progress_sec = state->progress_ms / 1000;
    int duration_sec = state->duration_ms / 1000;
    printf("║ Progress: %d:%02d / %d:%02d\n", 
           progress_sec / 60, progress_sec % 60,
           duration_sec / 60, duration_sec % 60);
    
    // Progress bar
    int bar_width = 50;
    int filled = (state->duration_ms > 0) ? 
                 (state->progress_ms * bar_width / state->duration_ms) : 0;
    printf("║ [");
    for (int i = 0; i < bar_width; i++) {
        printf(i < filled ? "#" : ".");
    }
    printf("]\n");
    
    // Playback state
    printf("║ Status: %s\n", state->is_playing ? "▶ Playing" : "⏸ Paused");
    printf("║ Shuffle: %s\n", state->shuffle_state ? "On" : "Off");
    printf("║ Repeat: %s\n", state->repeat_state);
    
    // Context
    if (strlen(state->context_type) > 0) {
        printf("║ Context: %s\n", state->context_type);
    }
    
    // Device info
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ Device: %s (%s)\n", state->device.device_name, state->device.device_type);
    printf("║ Volume: %d%%\n", state->device.volume_percent);
    printf("║ Active: %s\n", state->device.is_active ? "Yes" : "No");
    
    printf("╚════════════════════════════════════════════════════════════════╝\n");
}

void spotify_print_device(SpotifyDevice *device, int index) {
    printf("%d. %s\n", index, device->device_name);
    printf("   Type: %s\n", device->device_type);
    printf("   Volume: %d%%\n", device->volume_percent);
    printf("   Active: %s\n", device->is_active ? "✓ Yes" : "No");
    printf("   ID: %s\n", device->device_id);
}
