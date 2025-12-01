
SpotifyAlbumDetailed* spotify_get_album(SpotifyToken *token, const char *album_id) {
    if (!token || !album_id) {
        fprintf(stderr, "Invalid parameters for get_album\n");
        return NULL;
    }

    char url[512];
    snprintf(url, sizeof(url),
             "https://api.spotify.com/v1/albums/%s", album_id);

    struct json_object *root = spotify_api_get(token, url);
    if (!root) {
        fprintf(stderr, "Failed to get album\n");
        return NULL;
    }

    SpotifyAlbumDetailed *album = malloc(sizeof(SpotifyAlbumDetailed));
    if (!album) {
        json_object_put(root);
        return NULL;
    }

    struct json_object *obj;

    // Album info
    if (json_object_object_get_ex(root, "id", &obj)) {
        strncpy(album->album_info.id, json_object_get_string(obj),
                sizeof(album->album_info.id) - 1);
    }

    if (json_object_object_get_ex(root, "name", &obj)) {
        strncpy(album->album_info.name, json_object_get_string(obj),
                sizeof(album->album_info.name) - 1);
    }

    if (json_object_object_get_ex(root, "release_date", &obj)) {
        strncpy(album->album_info.release_date, json_object_get_string(obj),
                sizeof(album->album_info.release_date) - 1);
    }

    // Artist
    struct json_object *artists;
    if (json_object_object_get_ex(root, "artists", &artists) &&
        json_object_array_length(artists) > 0) {
        struct json_object *artist = json_object_array_get_idx(artists, 0);
        if (json_object_object_get_ex(artist, "name", &obj)) {
            strncpy(album->album_info.artist, json_object_get_string(obj),
                    sizeof(album->album_info.artist) - 1);
        }
    }

    // Tracks
    struct json_object *tracks;
    if (json_object_object_get_ex(root, "tracks", &tracks)) {
        struct json_object *items;
        if (json_object_object_get_ex(tracks, "items", &items)) {
            int count = json_object_array_length(items);
            album->album_info.total_tracks = count;

            album->tracks = malloc(sizeof(SpotifyTrack) * count);
            if (album->tracks) {
                album->count = count;

                for (int i = 0; i < count; i++) {
                    struct json_object *item = json_object_array_get_idx(items, i);
                    parse_track_json(item, &album->tracks[i]);
                }
            }
        }
    }

    json_object_put(root);
    return album;
}


