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
    int wc_child = wait(NULL);
    printf("pid(child): %d\n", getpid());
    printf("wc(child): %d\n", wc_child);
  } else {
    int wc_parent = wait(NULL);
    printf("pid(parent): %d\n", getpid());
    printf("wc(parent): %d\n", wc_parent);
  }
  return 0;
}

/*
 * 父进程中的 wait 返回的是等待的子进程的 pid，
 * 在子进程中使用 wait，返回 -1
 */
