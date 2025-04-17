# XAL - X Activity Logger
Creates a window that tracks keystrokes, mouse clicks, etc.

## Manifesto
This program is a minimal and readable replacement for the XEV utility, the syntax is more declarative, the logic is simple. It is also designed to study the Xlib library.

## Installation
```bash
git clone https://github.com/Ad4ndi/xal
cd xal
clang -I/usr/X11R6/include -L/usr/X11R6/lib -o xal xal.c -lX11
```
