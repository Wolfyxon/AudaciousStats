# Audacious Stats

An Audacious plugin for tracking your song plays.

## Project status
This is still being worked on.
The development may be slow due to lack of documentation of the Audacious plugin API, which requires me to analyze the Audacious code. 

Features
- [x] Tracking & saving the stats
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
6. 