#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    perror("Fork failed!\n");
    exit(1);
  } else if (rc == 0) {
    printf("The child process running...\n");
    char* args[] = {"/bin/ls", NULL};
    execv(args[0], args);
  } else {
    printf("The parent process finished.\n");
  }
  return 0;
}

/*
 * 不同的 exec 变种使用不同的后缀表示一些功能上的细分，
 * 具体的细分使用 man exec 查看
 */
