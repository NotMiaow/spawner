# Spawner

## Description
Launches a program and waits for it to finish.<br>
When said other program finishes, relaunch it,<br>
unless Stop() was called for by writing "stop"<br>
in the console.

## Details
Works on Ubuntu 20.04

## Building and using

On ubuntu 20.04 or compatible distro (with this program)<br>
(I don't know them, sorry..!)

```
cd \[your gits folder path\]
git clone https://github.com/NotMiaow/spawner.git
mkdir build
cd build
cmake ../
make
```

## Modifying

Change `"relay_bot"` in "main.cpp" for the name of<br>
your executable to spawn. Copy built "spawner" to <br>
the executable's parent folder.
