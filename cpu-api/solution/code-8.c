#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const char* output = "Hello world!";

  int pipefd[2];

  if (pipe(pipefd) == -1) {
    perror("Pipe failed!\n");
    exit(1);
  }

  int cpid_1 = fork();

  if (cpid_1 < 0) {
    perror("Fork failed!\n");
    exit(1);
  } else if (cpid_1 == 0) {
    // child process 1 continues
    close(pipefd[0]); // close the read end
    write(pipefd[1], output, strlen(output) + 1);
    close(pipefd[1]); // close the write end after writing
    exit(0);
  } else {
    // parent process continues
    int cpid_2 = fork();
    if (cpid_2 < 0) {
      perror("Fork failed!\n");
      exit(1);
    } else if (cpid_2 == 0) {
      // child process 2 continues
      close(pipefd[1]); // close the write end
      char buf;
      while (read(pipefd[0], &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
      }
      close(pipefd[0]); // close the read end after reading
      exit(0);
    } else {
      close(pipefd[0]);
      close(pipefd[1]);
      waitpid(cpid_1, NULL, 0);
      waitpid(cpid_2, NULL, 0);
    }
  }
  return 0;
}

/*
 * 错误记录：
 * 1. 不要在父进程中连续两次调用 fork，这会产生三个子进程而非两个。
 *    首先，父进程调用 fork 产生了子进程 1；
 *    接着，父进程和子进程 1 同时继续运行产生了子进程 2 和 3。
 * 2. 在每个进程中，都应该关闭不需要使用的管道文件描述符
 *
 * 备注：
 * 不需要在子进程 2 中手动等待子进程 1 的写入结束，管道本身提供了同步。
 * 管道本身带有阻塞行为：
 * - 写入时，如果读取端没有读取，写操作会阻塞，直到有数据被读取或缓冲区被填满；
 * - 读取时，如果写入端没有写入，读操作会阻塞，直到有数据被写入。
 * 子进程 1 在写入完成后关闭写端，这会向子进程 2 发送 EOF 信号，通知子进程 2 没有更多数据可读。
 */
