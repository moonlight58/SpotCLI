#ifndef SPOTIFY_INTERNAL_H
#define SPOTIFY_INTERNAL_H

#include "api.h"
#include <json-c/json.h>
#include <stdbool.h>

// PUBLIC INTERFACE (WHAT USERS CAN SEE)
/**
 * encoding method
 */
char* url_encode(const char *str);

/**
 * All the api request (PUT/POST/DELETE)
 */
bool spotify_api_delete_empty(SpotifyToken *token, const char *url);
bool spotify_api_post(SpotifyToken *token, const char *url, const char *json_data);
bool spotify_api_post_empty(SpotifyToken *token, const char *url);
bool spotify_api_put(SpotifyToken *token, const char *url, const char *json_data);
bool spotify_api_put_empty(SpotifyToken *token, const char *url);
struct json_object* spotify_api_delete_json(SpotifyToken *token, const char *url, const char *json_data);
struct json_object* spotify_api_get(SpotifyToken *token, const char *url);
struct json_object* spotify_api_post_json(SpotifyToken *token, const char *url, const char *json_data);

/**
 * All the parsers known used
 */

void parse_artist_json(struct json_object *item, SpotifyArtist *artist);
void parse_device_json(struct json_object *device_obj, SpotifyDevice *device);
void parse_player_state_json(struct json_object *root, SpotifyPlayerState *state);
void parse_playlist_full_json(struct json_object *root, SpotifyPlaylistFull *playlist);
void parse_playlist_json(struct json_object *item, SpotifyPlaylist *playlist);
void parse_queue_json(struct json_object *root, SpotifyQueue *queue);
void parse_track_json(struct json_object *item, SpotifyTrack *track);

#endif // SPOTIFY_INTERNAL_H
