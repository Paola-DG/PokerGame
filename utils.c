#include "utils.h"
#ifdef _WIN32
#include <conio.h>
#include <signal.h>

int getch(void) {
    int ch = _getch(); // ASCII value for Ctrl+C
    if (ch == 3) {
        raise(SIGINT);
    }
    return ch;
}

#else
#include <termios.h>
#include <unistd.h>
#include <signal.h>

int getch(void) {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (ch == 3) { // ASCII value for Ctrl+C
        raise(SIGINT); 
    }
    return ch;
}
#endif
