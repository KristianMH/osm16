#include "lib.h"

#define BOB     "[^_^]" // we don't use bob for anything, bob is useless !
#define ALICE   "(^0^)" // we did however user alice for something ...
#define JOHN    "{-_-}" // john just is angry that we used alice !

#define ALLOC_ERROR -1
#define FOUR_PAGES  4096*4

int main() {
  char* a_string;

  // Find the current heap end.
  a_string  = syscall_memlimit(NULL);

  // give me 4 pages !
  if (syscall_memlimit(a_string + FOUR_PAGES) == NULL) {
    return ALLOC_ERROR;
  }

  // write my looong 'a' string
  for (size_t i = 0; i < FOUR_PAGES-1; i++) {
    a_string[i] = 'a';
  }

  a_string[FOUR_PAGES-1] = '\n';

  // write text to screen
  syscall_write(1, a_string, FOUR_PAGES);

  return 0;
}
