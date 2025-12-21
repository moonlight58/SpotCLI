#ifndef SPOTIFY_API_ADVANCED_H
#define SPOTIFY_API_ADVANCED_H

#include "spotify/internal.h"


// ===== ALBUM FUNCTIONS =====

/**
 * Get detailed album information including all tracks
 * 
 * @param token - Valid Spotify token
 * @param album_id - Spotify album ID
 * @return SpotifyAlbumDetailed struct with tracks and album info, or NULL on error
 */
SpotifyAlbumDetailed* spotify_get_album(SpotifyToken *token, const char *album_id);

/**
 * Search for albums
 * 
 * @param token - Valid Spotify token
 * @param query - Search query
 * @param limit - Max number of results (1-50)
 * @return SpotifyAlbumList or NULL on error
 */
SpotifyAlbumList* spotify_search_albums(SpotifyToken *token, const char *query, int limit);

// ===== USER PROFILE FUNCTIONS =====

/**
 * Get current user's profile information
 * 
 * @param token - Valid Spotify token
 * @return SpotifyUserProfile or NULL on error
 */
SpotifyUserProfile* spotify_get_current_user_profile(SpotifyToken *token);

/**
 * Get another user's profile information
 * 
 * @param token - Valid Spotify token
 * @param user_id - Target user ID
 * @return SpotifyUserProfile or NULL on error
 */
SpotifyUserProfile* spotify_get_user_profile(SpotifyToken *token, const char *user_id);

// ===== RECENTLY PLAYED FUNCTIONS =====

/**
 * Get user's recently played tracks
 * 
 * @param token - Valid Spotify token
 * @param limit - Number of recent tracks to return (1-50)
 * @return SpotifyRecentlyPlayed or NULL on error
 */
SpotifyRecentlyPlayed* spotify_get_recently_played(SpotifyToken *token, int limit);

/**
 * Get user's saved albums
 * 
 * @param token - Valid Spotify token
 * @param limit - Number of albums to return (1-50, default 20)
 * @param offset - Index of first album to return (default 0)
 * @return SpotifyAlbumList or NULL on error
 */
SpotifyAlbumList* spotify_get_user_saved_albums(SpotifyToken *token, int limit, int offset);

/**
 * Remove albums from current user's 'Your Music' library
 * 
 * @param token - Valid Spotify token
 * @param album_ids - Array of Spotify album IDs to remove
 * @param count - Number of album IDs (max 50)
 * @return true if successful, false otherwise
 */
bool spotify_remove_albums(SpotifyToken *token, const char **album_ids, int count);

/**
 * Check if one or more albums are saved in current user's 'Your Music' library
 * 
 * @param token - Valid Spotify token
 * @param album_ids - Array of Spotify album IDs to check
 * @param count - Number of album IDs (max 50)
 * @param result_count - Output parameter for number of results returned
 * @return Array of booleans (true = saved, false = not saved), or NULL on error
 *         Caller must free the returned array
 */
bool* spotify_check_saved_albums(SpotifyToken *token, const char **album_ids, int count, int *result_count);



// ===== FREE FUNCTIONS =====

void spotify_free_album_detailed(SpotifyAlbumDetailed *album);
void spotify_free_user_profile(SpotifyUserProfile *profile);
void spotify_free_recently_played(SpotifyRecentlyPlayed *history);

// ===== PRINT FUNCTIONS =====

void spotify_print_album_detailed(SpotifyAlbumDetailed *album);
void spotify_print_user_profile(SpotifyUserProfile *profile);
void spotify_print_recently_played(SpotifyRecentlyPlayed *history);

#endif
