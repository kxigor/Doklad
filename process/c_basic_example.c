#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int channels[2] = {};
  pipe(channels);
  
  int child_pid = fork();
  if (child_pid == 0) {
    close(channels[0]);
    dup2(channels[1], STDOUT_FILENO);
    close(channels[1]);
    execlp("gcc", "gcc", "--version", NULL);
    exit(1);
  }

  close(channels[1]);
  
  char buffer[1024] = {};
  ssize_t bytes_read = 0;
  while ((bytes_read = read(channels[0], buffer, sizeof(buffer))) > 0) {
    write(STDOUT_FILENO, buffer, bytes_read);
  }

  int wait_status = 0;
  wait(&wait_status);

  close(channels[0]);

  return 0;
}