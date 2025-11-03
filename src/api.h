#ifndef API_H
#define API_H

#include "auth.h"
#include <stdbool.h>

typedef struct {
    char id[64];
    char name[256];
    char artist[256];
    char album[256];
    int duration_ms;
    char uri[128];
} SpotifyTrack;

typedef struct {
    SpotifyTrack *tracks;
    int count;
    int total;
} SpotifyTrackList;

// Search for tracks
SpotifyTrackList* spotify_search_tracks(SpotifyToken *token, const char *query, int limit);

// Add tracks to user's library
bool spotify_save_tracks(SpotifyToken *token, const char **track_ids, int count);

// Get user's saved tracks
SpotifyTrackList* spotify_get_saved_tracks(SpotifyToken *token, int limit, int offset);

// Free track list memory
void spotify_free_track_list(SpotifyTrackList *list);

// Helper to print track info
void spotify_print_track(SpotifyTrack *track, int index);

#endif
