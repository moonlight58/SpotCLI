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
