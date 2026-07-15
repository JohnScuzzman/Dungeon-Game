#include <rogue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// This function will run ONLY if the game crashes catastrophically
void handle_crash(int sig) {
    // 1. Instantly tear down ncurses to restore the terminal state
    if (!isendwin()) {
        endwin(); 
    }

    // 2. Print a helpful message to stderr so you know what happened
	#ifdef _WIN32
	#ifndef SIGBUS
	#define SIGBUS SIGSEGV
	#endif
	#endif
    fprintf(stderr, "\n--- Crashed Gracefully ---\n");
    if (sig == SIGBUS) {
        fprintf(stderr, "Error: Caught SIGBUS (Bus Error: 10).\n");
        fprintf(stderr, "This usually means illegal memory alignment or accessing a bad memory page.\n");
    } else if (sig == SIGSEGV) {
        fprintf(stderr, "Error: Caught SIGSEGV (Segmentation Fault).\n");
        fprintf(stderr, "This usually means reading/writing to a NULL or uninitialized pointer.\n");
    } else {
        fprintf(stderr, "Error: Caught signal %d.\n", sig);
    }
    
    // 3. Exit with a failure status
    exit(EXIT_FAILURE);
}
