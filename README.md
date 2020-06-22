# dmenu-emoji-picker

A c++ script that I created because the shell script I was using to select emoji with dmenu couldn't correctly copy [ZWJ emoji](https://en.wikipedia.org/wiki/Zero-width_joiner).

## Configuration

Before you compile, change the location of the `emoji` file in the code. Also change the `dmenu-custom` to the correct name of your emoji-supporting dmenu build.

## Compiling

`` gcc dmenu-emoji-picker.cpp -lstdc++ -o dmenu-emoji-picker``
