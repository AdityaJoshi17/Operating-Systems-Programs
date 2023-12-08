#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

void processA(int); // Function declaration for processA
void processB(int); // Function declaration for processB

void processA(int writefd) {
  int len;
  char buff[80];
  std::cout << "Enter a string: ";
  std::cin.getline(buff, 80); // Using std::cin.getline to read a line of input
  len = strlen(buff);
  if (buff[len - 1] == '\n') {
    len--;
  }
  write(writefd, buff, len);
}

void processB(int readfd) {
  int n, i, j;
  char str[80], temp;
  n = read(readfd, str, 80);
  str[n] = '\0';
  i = 0;
  j = strlen(str) - 1;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
  std::cout << "Reversed string: " << str << std::endl;
}

int main() {
  int pipe1[2];
  pid_t childpid;
  pipe(pipe1);

  childpid = fork();

  if (childpid == 0) {
    close(pipe1[1]);
    processB(pipe1[0]);
  } else {
    close(pipe1[0]);
    processA(pipe1[1]);
  }

  return EXIT_SUCCESS;
}
