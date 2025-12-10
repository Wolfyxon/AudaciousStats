# Audacious Stats

An [Audacious](https://audacious-media-player.org) plugin for tracking your song plays.

## Project status
This is still being worked on.
The development may be slow due to lack of documentation of the Audacious plugin API, which requires me to analyze the Audacious code. 

Features
- [x] Tracking & saving the stats
- [ ] More detailed stats
  - [ ] Plays last month
  - [ ] Last play date
- [ ] Automatic cleanup
  - [ ] Not including short audio
  - [ ] Deleting stats of songs that were played long time ago only for a few times
- [ ] Graphical interface to view the stats

The stats file is stored at:
```
/home/<username>/.config/audacious/stats.json
```

## Installation / compiling
**Note:** Currently only Linux is supported

1. Install the required packages: *audacious*, *jsoncpp*, *g++*, *make*
2. Open your terminal in the project's root directory
3. Compile the plugin: `make`
4. Install the compiled plugin `sudo cp AudaciousStats.so /usr/lib/audacious/General/AudaciousStats.so`
5. Delete this project to save space (optional)
6. In Audacious, go to **Services** > **Plugins** > **General**
7. Enable *Audacious Stats*
