#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Fork failed!\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello\n");
  } else {
    sleep(1);
    printf("goodbye\n");
  }
  return 0;
}

/*
 * 在不使用 wait() 的前提下，
 * 也许可以通过添加 sleep 来让子进程先打印
 */
