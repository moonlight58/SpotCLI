#ifndef SPOTIFY_PLAYLIST_H
#define SPOTIFY_PLAYLIST_H

#include "api.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

SpotifyPlaylistFull* spotify_create_playlist(SpotifyToken *token, const char *name, const char *description, bool is_public, bool is_collaborative);
SpotifyPlaylistFull* spotify_get_playlist(SpotifyToken *token, const char *playlist_id, bool fetch_tracks, int track_limit);
bool spotify_update_playlist(SpotifyToken *token, const char *playlist_id, SpotifyPlaylistUpdate *updates);
SpotifyPlaylistResult* spotify_add_tracks_to_playlist(SpotifyToken *token, const char *playlist_id, const char **track_uris, int count, int position);
SpotifyPlaylistResult* spotify_remove_tracks_from_playlist(SpotifyToken *token, const char *playlist_id, const char **track_uris, int count, const char *snapshot_id);
bool spotify_unfollow_playlist(SpotifyToken *token, const char *playlist_id);

#endif

