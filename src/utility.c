#include <rogue.h>

/*
Helper method for Sort Inventory.
Currently not implemented but will be used later in conjuction with Q-sort.
*/
int CompareStrings(const void *a, const void *b) {
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;

    return strcmp(strA, strB);
}

/* Used to count number of digits in a number.*/
int GetNumberOfDigits(int input) {
  int count;
  int temp = abs(input);
  // condition ? expression_if_true : expression_if_false, this one handles a zero input.
  count = (temp == 0) ? 0 : (int)log10(temp) + 1;
  return count;
}

/* Returns true if escape was passed in.*/
/* Usually the passed in int 'ch' will be from getch().*/
bool CheckEscape(int ch) {
    int next_ch;
    if (ch == 27) { 
            // check for escape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            return true;
        }
    return false;
}

/*
Highlights the coordinates at given, and the length you would like to highlight.
for example passing "41, 30, 20" would highlight the square at 41, 30, and then the 20 squares to the right of it.
*/
void Cursor(int x, int y, int length){
    //A_BLINK 
    mvchgat(x, y, length, A_BOLD | A_STANDOUT | A_DIM, VISIBLE_COLOR, NULL);
}

void RemoveCursor(int x, int y, int length) {
    mvchgat(x, y, length, A_NORMAL, 0, NULL);
}