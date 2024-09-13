#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int x = 100;

  printf("(x: %d) from pid(%d)\n", x, getpid());

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Fork failed!\n");
    exit(1);
  } else if (rc == 0) {
    printf("(x: %d) from pid(%d) (child)\n", x, getpid());
    x = 200; // try to modify x in child process
    printf("(x: %d) from pid(%d) (child) (modified)\n", x, getpid());
  } else {
    printf("(x: %d) from pid(%d)\n", x, getpid());
    x = 300;
    printf("(x: %d) from pid(%d) (modified)\n", x, getpid());
  }
  return 0;
}

/* Example Output:

(x: 100) from pid(239428)
(x: 100) from pid(239428)
(x: 300) from pid(239428) (modified)
(x: 100) from pid(239428)
(x: 100) from pid(239429) (child)
(x: 200) from pid(239429) (child) (modified)

子进程中的变量一开始会拥有父进程中对应变量的值，但是是独立的两个变量；
当子进程和父进程都改变变量 x 时，实际上是改变各自进程中的同名变量的值。
*/

