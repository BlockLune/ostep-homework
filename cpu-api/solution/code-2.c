#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // open, close, fork ...
#include <fcntl.h> // O_CREAT ...
#include <sys/wait.h> // wait
 
#define MSIZE 10

int main(int argc, char *argv[]) {
  // O_CREAT: 如果文件不存在则自动创建
  int fd_read = open("./coding-2.input", O_CREAT); // fd: file descriptor
  if (fd_read < 0) {
    fprintf(stderr, "Failed to get a file descriptor");
    exit(1);
  }

  // O_RDWR | O_CREAT | O_TRUNC: 读写，如果不存在则创建，如果存在则截断
  int fd_write = open("./coding-2.output", O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd_write < 0) {
    fprintf(stderr, "Failed to get a file descriptor");
    exit(1);
  }

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "Fork failed!\n");
    close(fd_read);
    close(fd_write);
    exit(1);
  } else if (rc == 0) {
    printf("The file descriptors from child: %d, %d\n", fd_read, fd_write);

    // read
    char* buf = (char *)malloc(sizeof(char) * (MSIZE + 1));
    read(fd_read, buf, MSIZE);
    buf[MSIZE] = '\0';
    printf("Read from child: %s\n", buf);

    // write
    const char* str = "Write from child\n";
    write(fd_write, str, strlen(str));
  } else {
    printf("The file descriptors from parent: %d, %d\n", fd_read, fd_write);

    // read
    char* buf = (char *)malloc(sizeof(char) * (MSIZE + 1));
    read(fd_read, buf, MSIZE);
    buf[MSIZE] = '\0';
    printf("Read from parent: %s\n", buf);

    // write
    const char* str = "Write from parent\n";
    write(fd_write, str, strlen(str));
  }

  close(fd_read);
  close(fd_write);

  if (rc > 0) {
    wait(NULL); // parent should wait child
  }

  return 0;
}

/*
 * 父子进程可以同时访问一个文件描述符，
 * 但是由于文件的读取位置（文件偏移量）于同一个文件共享，
 * 其中一个进程可能无法读取到内容。
 * 同时写入可能导致多种问题，
 * 例如由于文件偏移量混乱、覆盖写入、写入顺序不对等。
 */
