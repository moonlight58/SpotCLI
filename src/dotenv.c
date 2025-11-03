#include "dotenv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Trim whitespace from both ends of a string
static char* trim(char *str) {
    char *end;
    
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return str;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    end[1] = '\0';
    return str;
}

bool load_dotenv(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "Warning: Could not open %s\n", filepath);
        return false;
    }
    
    char line[1024];
    int line_num = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        
        // Trim whitespace
        char *trimmed = trim(line);
        
        // Skip empty lines and comments
        if (trimmed[0] == '\0' || trimmed[0] == '#') {
            continue;
        }
        
        // Find the '=' separator
        char *equals = strchr(trimmed, '=');
        if (!equals) {
            fprintf(stderr, "Warning: Invalid line %d in %s (no '=' found)\n", 
                    line_num, filepath);
            continue;
        }
        
        // Split into key and value
        *equals = '\0';
        char *key = trim(trimmed);
        char *value = trim(equals + 1);
        
        // Remove quotes from value if present
        size_t value_len = strlen(value);
        if (value_len >= 2 && 
            ((value[0] == '"' && value[value_len-1] == '"') ||
             (value[0] == '\'' && value[value_len-1] == '\''))) {
            value[value_len-1] = '\0';
            value++;
        }
        
        // Set environment variable
        if (setenv(key, value, 1) != 0) {
            fprintf(stderr, "Warning: Failed to set environment variable %s\n", key);
        }
    }
    
    fclose(file);
    return true;
}
