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

typedef struct { // List of all the tracks
    SpotifyTrack *tracks;
    int count;
    int total;
} SpotifyTrackList;

typedef struct {
    char id[64];
    char name[256];
    char genres[512];  // Comma-separated genres
    int followers;
    int popularity;
    char uri[128];
    char image_url[512];
} SpotifyArtist;

typedef struct { // List of all the artists
    SpotifyArtist *artists;
    int count;
    int total;
} SpotifyArtistList;

typedef struct {
    char id[64];
    char name[256];
    char artist[256];
} SpotifyAlbum;

typedef struct { // List of all the albums
    SpotifyAlbum *albums;
    int count;
    int total;
} SpotifyAlbumList;

typedef struct {
    char id[64];
    char name[256];
    char uri[128];
    bool is_public;
    int count_tracks;
} SpotifyPlaylist;

typedef struct { // List of all the playlists
    SpotifyPlaylist* playlists;
    int count;
    int total;
} SpotifyPlaylistList;

typedef struct {
    char device_id[64];
    char device_name[256];
    char device_type[64];  // "Computer", "Smartphone", "Speaker", etc.
    int volume_percent;
    bool is_active;
    bool is_private_session;
    bool is_restricted;
} SpotifyDevice;

typedef struct {
    // Track info
    char track_id[64];
    char track_name[256];
    char artist_name[256];
    char album_name[256];
    int duration_ms;
    char track_uri[128];
    
    // Playback state
    bool is_playing;
    int progress_ms;
    int timestamp;  // Unix timestamp
    
    // Context (playlist, album, etc.)
    char context_type[32];  // "playlist", "album", "artist", etc.
    char context_uri[128];
    
    // Settings
    bool shuffle_state;
    char repeat_state[16];  // "off", "track", "context"
    
    // Device
    SpotifyDevice device;
} SpotifyPlayerState;

typedef struct {
    SpotifyTrack currently_playing;
    SpotifyTrack *queue;
    int queue_count;
} SpotifyQueue;

typedef struct {
    char id[64];
    char name[256];
    char description[1024];
    char uri[128];
    char owner_id[64];
    char owner_name[256];
    char snapshot_id[128];
    bool is_public;
    bool is_collaborative;
    int total_tracks;
    SpotifyTrack *tracks;      // Array of tracks (when fetched with tracks)
    int tracks_count;          // Number of tracks in array
} SpotifyPlaylistFull;

typedef struct {
    char *name;                // New name (NULL to keep unchanged)
    char *description;         // New description (NULL to keep unchanged)  
    bool *is_public;           // New public status (NULL to keep unchanged)
    bool *is_collaborative;    // New collaborative status (NULL to keep unchanged)
} SpotifyPlaylistUpdate;

typedef struct {
    char snapshot_id[128];     // Returned snapshot ID after modification
    bool success;
} SpotifyPlaylistResult;

// Search for tracks, artists, artists top tracks
SpotifyArtistList* spotify_search_artists(SpotifyToken *token, const char *query, int limit);
SpotifyTrackList* spotify_get_artist_top_tracks(SpotifyToken *token, const char *artist_id, const char *market);
SpotifyTrackList* spotify_search_tracks(SpotifyToken *token, const char *query, int limit);

// Add tracks to user's library
bool spotify_save_tracks(SpotifyToken *token, const char **track_ids, int count);

// Get user's saved tracks, artists top tracks, artist's albums, user's albums, player's state
SpotifyAlbumList* spotify_get_artist_albums(SpotifyToken *token, const char *artist_id);
SpotifyPlayerState* spotify_get_player_state(SpotifyToken *token);
SpotifyPlaylistList* spotify_get_user_playlists(SpotifyToken *token, int limit, int offset);
SpotifyTrackList* spotify_get_artist_top_tracks(SpotifyToken *token, const char *artist_id, const char *market);
SpotifyTrackList* spotify_get_saved_tracks(SpotifyToken *token, int limit, int offset);

// Free track list, artist list, album list, player state, user's playlist memory
void spotify_free_album_list(SpotifyAlbumList *list);
void spotify_free_artist_list(SpotifyArtistList *list);
void spotify_free_player_state(SpotifyPlayerState *state);
void spotify_free_playlist_full(SpotifyPlaylistFull *playlist);
void spotify_free_playlist_list(SpotifyPlaylistList *list);
void spotify_free_playlist_result(SpotifyPlaylistResult *result);
void spotify_free_track_list(SpotifyTrackList *list);

// Helper to print track, artist, album, user's playlist, player state info
void spotify_print_album(SpotifyAlbum *album, int index);
void spotify_print_artist(SpotifyArtist *artist, int index);
void spotify_print_device(SpotifyDevice *device, int index);
void spotify_print_player_state(SpotifyPlayerState *state);
void spotify_print_playlist(SpotifyPlaylist *playlist, int index);
void spotify_print_playlist_full(SpotifyPlaylistFull *playlist);
void spotify_print_track(SpotifyTrack *track, int index);

// Control playback (pause/resume/start/toggle)
bool spotify_pause_playback(SpotifyToken *token, const char *device_id);
bool spotify_resume_playback(SpotifyToken *token, const char *device_id);
bool spotify_start_playback(SpotifyToken *token, const char *device_id, const char *context_uri, const char **uris, int uri_count);
bool spotify_toggle_playback(SpotifyToken *token);

// Control playback (skip to next/skip to previous/toggle shuffle)
SpotifyDevice* spotify_get_available_devices(SpotifyToken *token, int *device_count);
bool spotify_set_playback_volume(SpotifyToken *token, const char *device_id, int volume);
bool spotify_skip_next_playback(SpotifyToken *token, const char *device_id);
bool spotify_skip_previous_playback(SpotifyToken *token, const char *device_id);
bool spotify_toggle_playback_shuffle(SpotifyToken *token, const char *device_id, bool state_shuffle);
bool spotify_transfer_playback(SpotifyToken *token, const char *device_id, bool play);

// Queue tracks methods
SpotifyQueue* spotify_get_queue(SpotifyToken *token);
bool spotify_add_to_queue(SpotifyToken *token, const char *uri, const char *device_id);
void spotify_free_queue(SpotifyQueue *queue);
void spotify_print_queue(SpotifyQueue *queue);

// ===== PLAYLIST MANAGEMENT FUNCTIONS =====
SpotifyPlaylistFull* spotify_create_playlist(SpotifyToken *token, const char *name, const char *description, bool is_public, bool is_collaborative);
SpotifyPlaylistFull* spotify_get_playlist(SpotifyToken *token, const char *playlist_id, bool fetch_tracks, int track_limit);
SpotifyPlaylistResult* spotify_add_tracks_to_playlist(SpotifyToken *token, const char *playlist_id, const char **track_uris, int count, int position);
SpotifyPlaylistResult* spotify_remove_tracks_from_playlist(SpotifyToken *token, const char *playlist_id, const char **track_uris, int count, const char *snapshot_id);
bool spotify_unfollow_playlist(SpotifyToken *token, const char *playlist_id);
bool spotify_update_playlist(SpotifyToken *token, const char *playlist_id, SpotifyPlaylistUpdate *updates);
char* spotify_get_current_user_id(SpotifyToken *token);

#endif
