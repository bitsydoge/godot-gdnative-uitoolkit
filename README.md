# UIToolkit GDNative

## How to use
- You'll need everything needed to build godot
- Clone with recursive `git clone --recursive https://github.com/Coldragon/UIToolkit-GDNative.git`
- Build godot-cpp, go inside the godot-cpp folder and use scons
```
scons platform=<your_platform> generate_bindings=yes
```
For example on Windows
```
scons platform=windows generate_bindings=yes
```
- Build the UIToolkit library 

```
scons platform=windows
```
- You can now launch the godot demo project in the game folder (Tested with Godot master during beta3+)
