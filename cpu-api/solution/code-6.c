#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int rc = fork();
  if (rc < 0) {
    perror("Fork failed!\n");
    exit(1);
  } else if (rc == 0) {
    printf("pid(child): %d\n", getpid());
  } else {
    waitpid(-1, NULL, 0);
    printf("pid(parent): %d\n", getpid());
  }
  return 0;
}

/*
 * 使用 waitpid 可以获得更细粒度的控制。
 * wait 在其任何一个子进程退出时终止，
 * 而使用 waitpid 可以使用参数控制（具体见 man wait）。
 * 使用 waitpid 还可以指定具体哪个子进程停止时结束等待。
 */
