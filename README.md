> [!IMPORTANT]
> Ce projet n'est plus maintenu. Le développement s'arrête ici pour des raisons politiques liées aux activités de Spotify.
> Renseignez-vous, faites vos propres choix.
> Voir plus à la section "Pourquoi ce projet n'est plus maintenu" à la fin de ce README.

> [!IMPORTANT]
> This project is no longer maintained. Development stops here due to political reasons related to Spotify's activities.
> Do your own research, make your own choices.
> See more at the section "Why this project is no longer maintained" at the end of this README.


# spotCLI

A lightweight CLI tool to search Spotify music and add tracks to your liked songs without opening the Spotify app or website.

## Features

- Search for tracks
- Save tracks to your library
- View your saved tracks
- Interactive and command-line modes
- Automatic OAuth authentication
- Token refresh handling

## Installation

### Prerequisites

#### Debian/Ubuntu
```bash
sudo apt install libcurl4-openssl-dev libjson-c-dev build-essential
```

#### Fedora/RHEL
```bash
sudo dnf install libcurl-devel json-c-devel gcc make
```

#### Arch Linux
```bash
sudo pacman -S curl json-c base-devel
```

#### macOS
```bash
brew install curl json-c
```

### Build & Install

```bash
# Clone or download the repository
git clone https://github.com/moonlight58/spotCLI.git
cd spotCLI

# Build using Make
make

# Install system-wide (optional)
sudo make install
```

Or build manually:
```bash
gcc src/*.c -o spotCLI -lcurl -ljson-c
sudo mv spotCLI /usr/local/bin/
```

## Setup

### 1. Create Spotify Application

1. Go to [Spotify Developer Dashboard](https://developer.spotify.com/dashboard)
2. Click "Create app"
3. Fill in the details:
   - **App name**: spotCLI (or any name you like)
   - **App description**: CLI music search tool
   - **Redirect URI**: `http://127.0.0.1:8888/callback` since the webAPI doesn't support localhost anymore
4. Save your app and note the **Client ID** and **Client Secret**

### 2. Configure Environment Variables

Create a `.env` file in the project directory:

```bash
cat > .env << EOF
CLIENT_ID=your_spotify_client_id_here
CLIENT_SECRET=your_spotify_client_secret_here
REDIRECT_URI=http://127.0.0.1:8888/callback
EOF
```

**Important**: Never commit your `.env` file to version control!

### 3. First Run

```bash
./spotCLI
```

The app will:
1. Display an authorization URL
2. Open a temporary local server on port 8888
3. Wait for you to authorize the app in your browser
4. Automatically save your tokens to `~/.config/spotCLI/token.json`

## Usage

### Interactive Mode (default)

```bash
spotCLI
# or
spotCLI -i
```

### Command Line Mode

#### Search for tracks
```bash
spotCLI "PTSMR"
spotCLI "Bohemian Rhapsody"
spotCLI "tyler, the creator EARFQUAKE"
```

#### List saved tracks
```bash
spotCLI --list
# or
spotCLI -l
```

## Make Commands

```bash
make          # Build the project
make run      # Build and run in interactive mode
make clean    # Remove build files
make rebuild  # Clean and rebuild
make debug    # Build with debug symbols
make install  # Install to /usr/local/bin (requires sudo)
make uninstall # Remove from system
make logout   # Remove authentication token
make help     # Show all available commands
```

## Options

| Option | Short | Description |
|--------|-------|-------------|
| `--track` | `-t` | Search for tracks (default) |
| `--artist` | `-a` | Search for artists |
| `--album` | `-A` | Search for albums |
| `--playlist` | `-p` | Search for playlists |
| `--user` | `-u` | Search for users (coming soon) |
| `--audiobook` | `-b` | Search for audiobooks (coming soon) |
| `--list` | `-l` | List your saved tracks |
| `--interactive` | `-i` | Start interactive mode |
| `--help` | `-h` | Show help message |

## Configuration Files

```
~/.config/spotCLI/
└── token.json  # Stored authentication tokens (auto-generated)
```

To log out and clear tokens:
```bash
make logout
# or manually
rm ~/.config/spotCLI/token.json
```

## Troubleshooting

### "No tracks found" for valid searches

1. Check your token is valid:
   ```bash
   cat ~/.config/spotCLI/token.json
   ```

2. Delete token and re-authenticate:
   ```bash
   make logout
   ./spotCLI
   ```

3. Verify your `.env` file has correct credentials

### "Failed to start callback server"

Port 8888 might be in use. Check with:
```bash
lsof -i :8888
```

### Compilation errors

Make sure all dependencies are installed:
```bash
# Check if libraries are available
pkg-config --libs libcurl json-c
```

## API Scopes

The app requests the following Spotify scopes:
- `user-library-read` - View your saved tracks
- `user-library-modify` - Save tracks to your library
- `playlist-modify-public`
- `playlist-modify-private`
- `user-read-playback-state`
- `user-modify-playback-state`

## Roadmap

### Web API implementation
- [ ] Albums
  - [x] Get Albums
  - [x] Get Several Albums
  - [ ] Get Album Tracks
  - [x] Get User's Saved Albums
  - [x] Save Albums for Current User
  - [x] Remove User's Saved Albums
  - [x] Check User's Saved Albums
  - [ ] Get New Releases
- [ ] Artists
  - [x] Get Artist
  - [x] Get Several Artists
  - [x] Get Artist's Albums
  - [x] Get Artist's Top Tracks
- [ ] Player
  - [x] Get Playback State
  - [x] Transfer Playback
  - [x] Get Available Devices
  - [ ] Get Currently Playing Track
  - [x] Start/Resume Playback
  - [x] Pause Playback
  - [x] Skip To Next
  - [x] Skip To Previous
  - [ ] Skip To Position
  - [x] Set Repeat Mode
  - [x] Set Playback Volume
  - [x] Toggle Playback Shuffle
  - [x] Get Recently Played Tracks
  - [x] Get the User's Queue
  - [x] Add Item to Playback Queue
- [ ] Playlists
  - [x] Get Playlist
  - [x] Change Playlist Details
  - [ ] Get Playlist Items
  - [ ] Update Playlist Items
  - [x] Add Items to Playlist
  - [x] Remove Playlist Items
  - [ ] Get Current User's Playlists
  - [ ] Get User's Playlists
  - [x] Create Playlist
- [ ] Search
  - [x] Search for Item
- [ ] Tracks
  - [ ] Get Track
  - [ ] Get Several Tracks
  - [x] Get User's Saved Tracks
  - [x] Save Tracks for Current User
  - [ ] Remove User's Saved Tracks
  - [ ] Check User's Saved Tracks
- [ ] User
  - [x] Get Current User's Profile
  - [ ] Get User's Top Items
  - [x] Get User's Profile
  - [ ] Follow Playlist
  - [x] Unfollow Playlist
  - [ ] Get Followed Artists
  - [ ] Follow Artists or Users
  - [ ] Check if User Follow Artists or Users
  - [ ] Check if Current User Follows Playlist

---

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

MIT License - see LICENSE file for details

## Acknowledgments

- Built with [libcurl](https://curl.se/libcurl/) for HTTP requests
- JSON parsing with [json-c](https://github.com/json-c/json-c)
- [Spotify Web API](https://developer.spotify.com/documentation/web-api/)

# Pourquoi ce projet est archivé

Plusieurs éléments ont motivé l'arrêt du développement :

- **Investissements militaires** : Daniel Ek, fondateur de Spotify, est chairman de [Helsing](https://www.helsing.ai/), une entreprise d'IA militaire allemande dans laquelle il a personnellement investi. Helsing a des contrats avec Rheinmetall, Saab et Airbus — des entreprises impliquées dans des livraisons d'armes à Israël. ([Les Inrocks](https://www.lesinrocks.com/musique/le-pdg-de-spotify-investit-600-millions-deuros-dans-larmement-677863-04-08-2025/), [Le Figaro](https://www.lefigaro.fr/musique/fuck-spotify-les-investissements-de-daniel-ek-dans-le-secteur-de-l-armement-font-enrager-artistes-et-abonnes-20250730))

- **Publicités ICE** : En octobre 2025, Spotify a diffusé des publicités de recrutement pour l'ICE (Immigration and Customs Enforcement) américaine, refusant ensuite de modifier sa politique publicitaire. ([The Guardian](https://www.theguardian.com/technology/2026/jan/09/spotify-no-longer-running-ice-recruitment-ads-after-us-government-campaign-ends))

- **Publicités pour les prisons israéliennes** : Spotify a diffusé des publicités pour le service pénitentiaire israélien, sous la tutelle du ministre Itamar Ben-Gvir.

- **Partenariat avec Partner Communications** : Spotify a lancé en Israël via un accord avec cette entreprise listée dans la base de données de l'ONU pour son implication dans les colonies illégales.

Pour aller plus loin : [BDS Movement – Boycott Spotify](https://bdsmovement.net/boycott-spotify) · [Reddit r/spotify](https://www.reddit.com/r/spotify/comments/1ll26zd/spotifys_blood_money_funding_death_with_art/)

**Chacun fait ce qu'il veut avec cette information.** Le code reste disponible sous licence MIT pour ceux qui souhaitent le forker ou s'en inspirer.

# Why this project is archived

Several factors motivated the decision to stop development:

- **Military investments**: Daniel Ek, Spotify's founder, is chairman of [Helsing](https://www.helsing.ai/), a German military AI company in which he has personally invested. Helsing has contracts with Rheinmetall, Saab and Airbus — companies involved in arms deliveries to Israel. ([Les Inrocks](https://www.lesinrocks.com/musique/le-pdg-de-spotify-investit-600-millions-deuros-dans-larmement-677863-04-08-2025/), [Le Figaro](https://www.lefigaro.fr/musique/fuck-spotify-les-investissements-de-daniel-ek-dans-le-secteur-de-l-armement-font-enrager-artistes-et-abonnes-20250730))

- **ICE recruitment ads**: In October 2025, Spotify ran recruitment ads for the U.S. Immigration and Customs Enforcement (ICE), refusing to modify its advertising policy afterward. ([The Guardian](https://www.theguardian.com/technology/2026/jan/09/spotify-no-longer-running-ice-recruitment-ads-after-us-government-campaign-ends))

- **Israeli prison advertisements**: Spotify ran advertisements for the Israeli prison system, under the supervision of Minister Itamar Ben-Gvir.

- **Partnership with Partner Communications**: Spotify launched in Israel through an agreement with this company listed in the UN database for its involvement in illegal settlements.

To learn more : [BDS Movement – Boycott Spotify](https://bdsmovement.net/boycott-spotify) · [Reddit r/spotify](https://www.reddit.com/r/spotify/comments/1ll26zd/spotifys_blood_money_funding_death_with_art/) 

**Each person can do what they want with this information.** The code remains available under the MIT license for those who wish to fork it or draw inspiration from it.
