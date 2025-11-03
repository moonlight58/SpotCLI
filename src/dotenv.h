#ifndef DOTENV_H
#define DOTENV_H

#include <stdbool.h>

// Load environment variables from .env file
bool load_dotenv(const char *filepath);

#endif
