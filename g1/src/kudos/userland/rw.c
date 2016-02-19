#include "lib.h"

int main(void) {
  char strPrint[30] = "Skriv et tegn!\n";
  char str[25];
  char instr[20] = "Du skrev: ";
  syscall_write(1, &strPrint, 30);
  syscall_read(0, &str, 25);
  syscall_write(1, &instr, 20);
  syscall_write(1, &str, 25);

  char newline[2] = "\n";
  syscall_write(1, &newline, 2);

  syscall_halt();
  return 0;
}
