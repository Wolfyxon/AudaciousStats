# Audacious Stats

An [Audacious](https://audacious-media-player.org) plugin for tracking your song plays.

## Features
- [x] Tracking & saving the stats
- [ ] More detailed stats
  - [ ] Plays last month
  - [x] Last play date
- [x] Automatic cleanup
  - [x] Not including short audio
  - [x] Deleting stats of songs that were played long time ago only for a few times
- [ ] Graphical interface to view the stats

The stats file is stored at:
```
/home/<username>/.config/audacious/stats.json
```

The stats can be displayed in a fancy way on [SongWrap](https://wolfyxon.github.io/SongWrap/) ([source code](https://github.com/Wolfyxon/SongWrap))

## Installation
**Note:** Currently only Linux is supported

### Manual
1. [Download the latest release](https://github.com/wolfyxon/AudaciousStats/releases/latest) or compile AudaciousStats (explained in the section below)
2. Copy it to `/usr/lib/audacious/General`: `sudo cp AudaciousStats.so /usr/lib/audacious/General/AudaciousStats.so`
3. Open Audacious, go to **Services** > **Plugins** > **General**
4. Enable *Audacious Stats*

## Compiling
1. Install the required dependencies: *audacious*, *jsoncpp*, *g++*, *make*
2. Open your terminal in the project's root directory
3. Compile the plugin: `make`
4. You should see a file named `AudaciousStats.so`, you can now install it
