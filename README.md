# OpenTorium
Game inspired by [Auditorium](https://store.steampowered.com/app/205870/Auditorium/) made using C++ and [openFrameworks](https://openframeworks.cc/), an OpenGL wrapper.

The game is powered by a particle system fueled by a simple force-based physics
engine. The goal of the game is to direcy rays of particles from emitters
to containers using so-called force and color fields, revealing the level's
complete melody.

A demo of a basic game level is presented below,

<p align="center">
  <img src="extra/demo.gif" alt="Coins GIF"/>
</p>

# Installation

The most important step is having openFrameworks installed on your system
(see the [guide](https://openframeworks.cc/download/) for your specific platform).

Once you have done this and have the library in your PATH, you have to build the
project using the provided Makefile. Assuming the usage of a shell, this 
would be equivalent to
```bash
cd OpenTorium && make -jX
```
where `X` would be the preferred number of cores to be used for compiling.

# Getting Started
Once installed, the game can be started by executing
```bash
make RunRelease
```

Both the installation and this step can be easily adapted to your 
preferred IDE/shell.

# Configuration
Levels can be created by modifying the `level.xml` file.

One can currently add Emitters, Color Fields, Force Fields and Targets to
a level, with various customization options such as position, size, color/force,
mobility. For more details, see the provided `level.xml` example file.

# Plans for the Future
1. [ ] Create a game menu and implement level sequencing capabilities.
2. [ ] Implement in-house shader for better control over glow effect. From 
    prior experience it might be tricky to implement this in the openFrameworks draw pipeline,
    so investigate.
3. [ ] Implement new game functionalities (reflecting bar, repeller field, etc.)
4. [ ] Design new levels.
5. [ ] Find/create MIDI tracks for target songs.
6. [ ] Improve and customize game appearance (maybe using shaders).
7. [ ] Enhance general feel of the game (fade-in/out effects, sound effects, smoothenss).
8. [ ] In-game level editor.
