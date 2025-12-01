#ifndef SPOTIFY_LIBRARY_H
#define SPOTIFY_LIBRARY_H

#include "spotify/spotify_internal.h"
#include <stdio.h>

SpotifyTrackList* spotify_get_saved_tracks(SpotifyToken *token, int limit, int offset);
bool spotify_save_tracks(SpotifyToken *token, const char **track_ids, int count);
SpotifyPlaylistList* spotify_get_user_playlists(SpotifyToken *token, int limit, int offset);

#endif

