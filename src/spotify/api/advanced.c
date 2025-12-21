#include "spotify/api/advanced.h"
#include "spotify/api/endpoints.h"

// ===== USER PROFILE FUNCTIONS =====

SpotifyUserProfile* spotify_get_current_user_profile(SpotifyToken *token) {
    return spotify_get_user_profile(token, NULL);
}

SpotifyUserProfile* spotify_get_user_profile(SpotifyToken *token, const char *user_id) {
    if (!token) {
        fprintf(stderr, "Invalid token parameter\n");
        return NULL;
    }

    char url[256];
    if (user_id) {
        snprintf(url, sizeof(url), ENDPOINT_USER, user_id);
    } else {
        snprintf(url, sizeof(url), ENDPOINT_CURRENT_USER);
    }

    struct json_object *root = spotify_api_get(token, url);
    if (!root) {
        fprintf(stderr, "Failed to get user profile\n");
        return NULL;
    }

    SpotifyUserProfile *profile = malloc(sizeof(SpotifyUserProfile));
    if (!profile) {
        json_object_put(root);
        return NULL;
    }

    memset(profile, 0, sizeof(SpotifyUserProfile));

    struct json_object *obj;

    if (json_object_object_get_ex(root, "id", &obj)) {
        strncpy(profile->user_id, json_object_get_string(obj),
                sizeof(profile->user_id) - 1);
    }

    if (json_object_object_get_ex(root, "display_name", &obj)) {
        const char *name = json_object_get_string(obj);
        if (name) {
            strncpy(profile->display_name, name, sizeof(profile->display_name) - 1);
        }
    }

    struct json_object *followers;
    if (json_object_object_get_ex(root, "followers", &followers)) {
        if (json_object_object_get_ex(followers, "total", &obj)) {
            profile->followers = json_object_get_int(obj);
        }
    }

    if (json_object_object_get_ex(root, "external_urls", &obj)) {
        struct json_object *spotify_url;
        if (json_object_object_get_ex(obj, "spotify", &spotify_url)) {
            strncpy(profile->profile_url, json_object_get_string(spotify_url),
                    sizeof(profile->profile_url) - 1);
        }
    }

    struct json_object *images;
    if (json_object_object_get_ex(root, "images", &images) &&
        json_object_array_length(images) > 0) {
        struct json_object *image = json_object_array_get_idx(images, 0);
        if (json_object_object_get_ex(image, "url", &obj)) {
            strncpy(profile->profile_image_url, json_object_get_string(obj),
                    sizeof(profile->profile_image_url) - 1);
        }
    }

    json_object_put(root);
    return profile;
}

// ===== RECENTLY PLAYED FUNCTIONS =====

SpotifyRecentlyPlayed* spotify_get_recently_played(SpotifyToken *token, int limit) {
    if (!token) {
        fprintf(stderr, "Invalid token parameter\n");
        return NULL;
    }

    if (limit <= 0) limit = 20;
    if (limit > 50) limit = 50;

    char url[256];
    snprintf(url, sizeof(url),
             "%s?limit=%d",
            ENDPOINT_RECENTLY_PLAYED, limit);

    struct json_object *root = spotify_api_get(token, url);
    if (!root) {
        fprintf(stderr, "Failed to get recently played\n");
        return NULL;
    }

    struct json_object *items;
    if (!json_object_object_get_ex(root, "items", &items)) {
        json_object_put(root);
        return NULL;
    }

    int count = json_object_array_length(items);
    SpotifyRecentlyPlayed *history = malloc(sizeof(SpotifyRecentlyPlayed));
    history->history = malloc(sizeof(SpotifyPlayHistory) * count);
    history->count = count;

    for (int i = 0; i < count; i++) {
        struct json_object *item = json_object_array_get_idx(items, i);
        struct json_object *track;

        if (json_object_object_get_ex(item, "track", &track)) {
            parse_track_json(track, &history->history[i].track);
        }

        struct json_object *obj;
        if (json_object_object_get_ex(item, "played_at", &obj)) {
            strncpy(history->history[i].played_at, json_object_get_string(obj),
                    sizeof(history->history[i].played_at) - 1);
        }

        struct json_object *context;
        if (json_object_object_get_ex(item, "context", &context) && context) {
            if (json_object_object_get_ex(context, "type", &obj)) {
                strncpy(history->history[i].context_type, json_object_get_string(obj),
                        sizeof(history->history[i].context_type) - 1);
            }
        }
    }

    json_object_put(root);
    return history;
}

