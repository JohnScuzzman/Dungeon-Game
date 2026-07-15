#include <rogue.h>
#define WINDOW_WIDTH 32
#define WINDOW_HEIGHT 10
#define OFFSET 11

bool MakeDescendWindow() {
    char *options[] = {
        "Yes",
        "No",
    };
    int n_options = sizeof(options) / sizeof(char*);
    int descendX = (COLS - WINDOW_WIDTH) / 2;
    int descendY = (LINES - WINDOW_HEIGHT) / 2;
    bool escFlag = false;
    bool descendChoice = false;
    int cursor = 0;
    int choice = -1;
    int ch;

    WINDOW *descend = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, descendY, descendX);
    keypad(descend, TRUE);

    RenderDescendMenu(descend, cursor, n_options, options);

    while(!escFlag) {
        ch = wgetch(descend);
        if(CheckEscape(ch)) {
            return false;
        }
        switch(ch) {
            case KEY_UP:
                if (cursor == 0) {
                    cursor = n_options - 1;
                }
                else {
                    cursor--;
                }
                break;
            case KEY_DOWN: 
                if (cursor == n_options - 1) {
                    cursor = 0;
                }
                else {
                    cursor++;
                }
                break;
            case 32: // SPB
                choice = cursor;
                escFlag = true;
                break;
            case 10: // ENTER
                choice = cursor;
                escFlag = true;
                break;
            default:
                break;
        }
        RenderDescendMenu(descend, cursor, n_options, options);
    }
    descendChoice = ProcessDescendSelect(choice, descend);
    return descendChoice;
}

void RenderDescendMenu(WINDOW *descend, int cursor, int n_options, char** options) {
    int y = 3;
    int bottom = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - 2;
    int top = 1;
    int promptStart = 5;

    box(descend, 0, 0);
    mvwprintw(descend, top, promptStart, "Descend to next floor?");
    mvwhline(descend, 2, top, ACS_HLINE, numLines);
    // mvwhline(descend, top, bottom - 1, ACS_HLINE, numLines );

    for (int i = 0; i < n_options; i++) {
        y++;
        if (cursor == i) {
            wattron(descend, COLOR_PAIR(HIGHLIGHT_COLOR));
            mvwprintw(descend, y, center, "%s", options[i]);
            wattroff(descend, COLOR_PAIR(HIGHLIGHT_COLOR));
            wattron(descend, COLOR_PAIR(HIGHLIGHT_OFF));
        }
        else {
            mvwprintw(descend, y, center, "%s", options[i]);
        }
        y++;
    }
    wrefresh(descend);
}

bool ProcessDescendSelect(int choice, WINDOW* descend) {
    switch(choice){
        case 0: // Yes
            refresh();
            delwin(descend);
            return true;
            break;
        case 1: // No
            // Do the options window here
            refresh();
            delwin(descend);
            return false;
            break;
        default:
            refresh();
            delwin(descend);
            return false;
            break;
    }
}