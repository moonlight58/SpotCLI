#ifndef SPOTIFY_SEARCH_H
#define SPOTIFY_SEARCH_H

#include "api.h"

SpotifyTrackList* spotify_search_tracks(SpotifyToken *token, const char *query, int limit);
SpotifyArtistList* spotify_search_artists(SpotifyToken *token, const char *query, int limit);
SpotifyTrackList* spotify_get_artist_top_tracks(SpotifyToken *token, const char *artist_id, const char *market);
SpotifyAlbumList* spotify_get_artist_albums(SpotifyToken *token, const char *artist_id);

#endif

