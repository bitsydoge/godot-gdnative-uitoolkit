# QuakeScroll GDNative

## How to use
- You'll need everything needed to build godot
- Clone with recursive `git clone --recursive https://github.com/Coldragon/godot-quake_scroll-gdnative.git`
- Build godot-cpp, go inside the godot-cpp folder and use scons
```
scons platform=<your_platform> generate_bindings=yes
```
For example on Windows
```
scons platform=windows generate_bindings=yes
```
- Build the library that contain QuakeScroll class

```
scons platform=windows
```
- You can now launch the godot project in the game folder (Godot 3.1.2)
