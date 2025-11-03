#include "auth.h"
#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_menu() {
    printf("\n=== findSpot - Spotify CLI ===\n");
    printf("1. Search for tracks\n");
    printf("2. View saved tracks\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

void search_and_save(SpotifyToken *token) {
    char query[256];
    printf("\nEnter search query: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    printf("\nSearching for '%s'...\n", query);
    SpotifyTrackList *results = spotify_search_tracks(token, query, 10);
    
    if (!results || results->count == 0) {
        printf("No tracks found.\n");
        if (results) spotify_free_track_list(results);
        return;
    }

    printf("\nFound %d results (total: %d)\n\n", results->count, results->total);
    
    for (int i = 0; i < results->count; i++) {
        spotify_print_track(&results->tracks[i], i + 1);
        printf("\n");
    }

    printf("Enter track number to save (or 0 to cancel): ");
    int choice;
    scanf("%d", &choice);
    getchar(); // consume newline

    if (choice > 0 && choice <= results->count) {
        const char *track_id = results->tracks[choice - 1].id;
        
        printf("Saving track...\n");
        if (spotify_save_tracks(token, &track_id, 1)) {
            printf("✅ Track saved to your library!\n");
        } else {
            printf("❌ Failed to save track.\n");
        }
    }

    spotify_free_track_list(results);
}

void view_saved_tracks(SpotifyToken *token) {
    printf("\nFetching your saved tracks...\n");
    
    SpotifyTrackList *saved = spotify_get_saved_tracks(token, 20, 0);
    
    if (!saved || saved->count == 0) {
        printf("No saved tracks found.\n");
        if (saved) spotify_free_track_list(saved);
        return;
    }

    printf("\nYou have %d saved tracks (showing first %d)\n\n", 
           saved->total, saved->count);
    
    for (int i = 0; i < saved->count; i++) {
        spotify_print_track(&saved->tracks[i], i + 1);
        printf("\n");
    }

    spotify_free_track_list(saved);
}

int main() {
    SpotifyToken token;
    
    if (!spotify_get_access_token(&token)) {
        fprintf(stderr, "Failed to get access token.\n");
        return 1;
    }

    printf("✅ Authenticated successfully!\n");

    while (1) {
        print_menu();
        
        int choice;
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                search_and_save(&token);
                break;
            case 2:
                view_saved_tracks(&token);
                break;
            case 3:
                printf("\nGoodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
