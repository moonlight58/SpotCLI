#ifndef SPOTIFY_SEARCH_H
#define SPOTIFY_SEARCH_H

SpotifyTrackList* spotify_search_tracks(SpotifyToken *token, const char *query, int limit);
SpotifyArtistList* spotify_search_artists(SpotifyToken *token, const char *query, int limit);
SpotifyTrackList* spotify_get_artist_top_tracks(SpotifyToken *token, const char *artist_id, const char *market);
spotifyalbumlist* spotify_get_artist_albums(spotifytoken *token, const char *artist_id);

#endif

