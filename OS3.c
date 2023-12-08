#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void processA(int); //processA: Writes a string to a given file descriptor.
void processB(int); //processB: Reads a string from a given file descriptor, reverses it, and prints the reversed string.

/*
ProcessA Function:
Takes an integer writefd as an argument, which represents the file descriptor for writing to the pipe.
Asks the user to enter a string using printf and fgets.
Removes the newline character if it exists.
Writes the string to the pipe using the write function.
*/

void processA(int writefd){
  int len;
  char buff[80];
  printf("Enter a string: ");
  fgets(buff, 80, stdin);
  len = strlen(buff);
  if (buff[len - 1] == '\n') {
    len--;
  }
  write(writefd, buff, len);
}

/*
ProcessB Function:
Takes an integer readfd as an argument, which represents the file descriptor for reading from the pipe.
Reads a string from the pipe using the read function.
Reverses the string in-place.
Prints the reversed string.
*/

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
  printf("Reversed string: %s\n", str);
}

int main() {
  int pipe1[2]; //Declares an array pipe1 to store the file descriptors of the pipe.
                //It's a two-element array where pipe1[0] is used for reading, and pipe1[1] is used for writing.
  pid_t childpid;
  pipe(pipe1); //Calls the pipe function to create an unnamed pipe.
                //The function populates the pipe1 array with the read and write file descriptors.
  childpid = fork(); // Calls the fork function to create a new process.
                    //After this point, there are two identical processes (parent and child) running the same code.
  /*
  Inside the child process block (if (childpid == 0)):
close(pipe1[1]);: Closes the writing end of the pipe (pipe1[1]) in the child process.
The child is going to read from the pipe.
processB(pipe1[0]);: Calls the processB function, passing the reading end of the pipe (pipe1[0]) as an argument.
This function reads a string from the pipe, reverses it, and prints the reversed string.
  */

  if (childpid == 0) {
    close(pipe1[1]);
    processB(pipe1[0]);
  }

  /*
  Inside the parent process block (else):
close(pipe1[0]);: Closes the reading end of the pipe (pipe1[0]) in the parent process.
The parent is going to write to the pipe.
processA(pipe1[1]);: Calls the processA function, passing the writing end of the pipe (pipe1[1]) as an argument.
This function prompts the user to enter a string, reads it, and writes it to the pipe.
  */

  else {
    close(pipe1[0]);
    processA(pipe1[1]);
  }

  return EXIT_SUCCESS;
  /*Both the parent and child processes continue to execute code after the fork point,
  including the return EXIT_SUCCESS;. This line ensures that both processes terminate successfully.
  */
}
