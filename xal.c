#include <X11/Xlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define P(C, F, ...) do { printf(C "│ " F RESET "\n", ##__VA_ARGS__); fflush(stdout); } while (0)
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED    "\033[1;31m"
#define RESET  "\033[0m"

volatile sig_atomic_t r = 1;
void q(int _) { r = 0; }

int main() {
    signal(SIGINT, q);
    Display *d = XOpenDisplay(NULL); if (!d) return 1;
    Window w = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, 500, 500, 1, 0, 0xffffff);
    XSelectInput(d, w, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask);
    XMapWindow(d, w);

    XEvent e;
    puts("╭─ XAL started");
    while (r && XNextEvent(d, &e) == 0)
        switch (e.type) {
            case KeyPress:      P(GREEN,  ", Key %3d pressed", e.xkey.keycode); break;
            case KeyRelease:    P(RED,    ". Key %3d released", e.xkey.keycode); break;
            case ButtonPress:   P(GREEN,  "? Button %d down (%3d,%3d)", e.xbutton.button, e.xbutton.x, e.xbutton.y); break;
            case ButtonRelease: P(RED,    "! Button %d up   (%3d,%3d)", e.xbutton.button, e.xbutton.x, e.xbutton.y); break;
            case MotionNotify:  P(YELLOW, "> Moved (%3d,%3d)", e.xmotion.x, e.xmotion.y); break;
            case FocusIn:       P(GREEN,  "# Focus in"); break;
            case FocusOut:      P(RED,    "@ Focus out"); break;
        }
    XDestroyWindow(d, w);
    XCloseDisplay(d);
    return 0;
}
