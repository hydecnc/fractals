#!/bin/sh
emcc $1 -s USE_SDL=2 -s FULL_ES2=1 -s WASM=1 -o fractals.html
