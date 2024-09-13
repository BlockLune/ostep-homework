#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    perror("Fork failed!\n");
    exit(1);
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    printf("Hello world after the STDOUT_FILENO closed.");
  } else {
    wait(NULL);
  }
  return 0;
}

/*
 * 关闭标准输出，
 * 所以屏幕上没有输出
 */
