#include "spotify_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Parse track data from JSON object into SpotifyTrack struct
 */
void parse_track_json(struct json_object *item, SpotifyTrack *track) {
    struct json_object *obj;
    
    memset(track, 0, sizeof(SpotifyTrack));
    
    // ID
    if (json_object_object_get_ex(item, "id", &obj)) {
        strncpy(track->id, json_object_get_string(obj), sizeof(track->id) - 1);
    }
    
    // Name
    if (json_object_object_get_ex(item, "name", &obj)) {
        strncpy(track->name, json_object_get_string(obj), sizeof(track->name) - 1);
    }
    
    // Artist
    struct json_object *artists;
    if (json_object_object_get_ex(item, "artists", &artists) && 
        json_object_array_length(artists) > 0) {
        struct json_object *artist = json_object_array_get_idx(artists, 0);
        if (json_object_object_get_ex(artist, "name", &obj)) {
            strncpy(track->artist, json_object_get_string(obj), sizeof(track->artist) - 1);
        }
    }
    
    // Album
    struct json_object *album;
    if (json_object_object_get_ex(item, "album", &album) &&
        json_object_object_get_ex(album, "name", &obj)) {
        strncpy(track->album, json_object_get_string(obj), sizeof(track->album) - 1);
    }
    
    // Duration
    if (json_object_object_get_ex(item, "duration_ms", &obj)) {
        track->duration_ms = json_object_get_int(obj);
    }
    
    // URI
    if (json_object_object_get_ex(item, "uri", &obj)) {
        strncpy(track->uri, json_object_get_string(obj), sizeof(track->uri) - 1);
    }
}

/**
 * Parse artist data from JSON object into SpotifyArtist struct
 */
void parse_artist_json(struct json_object *item, SpotifyArtist *artist) {
    struct json_object *obj;
    
    memset(artist, 0, sizeof(SpotifyArtist));
    
    // ID
    if (json_object_object_get_ex(item, "id", &obj)) {
        strncpy(artist->id, json_object_get_string(obj), sizeof(artist->id) - 1);
    }
    
    // Name
    if (json_object_object_get_ex(item, "name", &obj)) {
        strncpy(artist->name, json_object_get_string(obj), sizeof(artist->name) - 1);
    }
    
    // Genres
    struct json_object *genres;
    if (json_object_object_get_ex(item, "genres", &genres)) {
        int genre_count = json_object_array_length(genres);
        char genres_str[512] = {0};
        for (int j = 0; j < genre_count && j < 5; j++) {
            struct json_object *genre = json_object_array_get_idx(genres, j);
            if (j > 0) strcat(genres_str, ", ");
            strncat(genres_str, json_object_get_string(genre), 
                    sizeof(genres_str) - strlen(genres_str) - 1);
        }
        if (genres_str[0] != '\0') {
            strncpy(artist->genres, genres_str, sizeof(artist->genres) - 1);
            artist->genres[sizeof(artist->genres) - 1] = '\0';
        }
    }
    
    // Followers
    struct json_object *followers_obj;
    if (json_object_object_get_ex(item, "followers", &followers_obj) &&
        json_object_object_get_ex(followers_obj, "total", &obj)) {
        artist->followers = json_object_get_int(obj);
    }
    
    // Popularity
    if (json_object_object_get_ex(item, "popularity", &obj)) {
        artist->popularity = json_object_get_int(obj);
    }
    
    // URI
    if (json_object_object_get_ex(item, "uri", &obj)) {
        strncpy(artist->uri, json_object_get_string(obj), sizeof(artist->uri) - 1);
    }
    
    // Image URL
    struct json_object *images;
    if (json_object_object_get_ex(item, "images", &images) && 
        json_object_array_length(images) > 0) {
        struct json_object *image = json_object_array_get_idx(images, 0);
        if (json_object_object_get_ex(image, "url", &obj)) {
            strncpy(artist->image_url, json_object_get_string(obj), sizeof(artist->image_url) - 1);
        }
    }
}

/**
 * Parse playlist data from JSON object into SpotifyPlaylist struct
 */
void parse_playlist_json(struct json_object *item, SpotifyPlaylist *playlist) {
    struct json_object *obj;

    memset(playlist, 0, sizeof(SpotifyPlaylist));
    
    // ID
    if (json_object_object_get_ex(item, "id", &obj)) {
        strncpy(playlist->id, json_object_get_string(obj), sizeof(playlist->id) - 1);
    }

    // Name
    if (json_object_object_get_ex(item, "name", &obj)) {
        strncpy(playlist->name, json_object_get_string(obj), sizeof(playlist->name) - 1);
    }

    // URI
    if (json_object_object_get_ex(item, "uri", &obj)) {
        strncpy(playlist->uri, json_object_get_string(obj), sizeof(playlist->uri) - 1);
    }
    
    // Public (correction du type dans api.h si nécessaire)
    if (json_object_object_get_ex(item, "public", &obj)) {
        playlist->is_public = json_object_get_boolean(obj);
    }
    
    // Track count
    struct json_object *tracks_obj;
    if (json_object_object_get_ex(item, "tracks", &tracks_obj) &&
        json_object_object_get_ex(tracks_obj, "total", &obj)) {
        playlist->count_tracks = json_object_get_int(obj);
    }
}
