/*************************************************************
* Project:   /dev/e                                          *
* File:      e_digits.c                                      *
* Name:      Sabrina Aravena                                 *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE* dev_file;
  char *buffer;
  int f_read;
  int file_number;

  /* checks for correct number of arguments */
  if (argc < 3) {
    printf("Not enouh arguments were entered. TRY AGAIN\n");
  } else if (argc > 3) {
    printf("There are too many arguments. TRY AGAIN\n");
  } else {
    /* checks for valid arguments */
    if ((atoi(argv[2])) < (atoi(argv[1]))) {
      printf("Second argument cannot be larger than the first. TRY AGAIN\n");
    } else if ((atoi(argv[1])) < 0) {
      printf("Argument buffer cannot be below 0. TRY AGAIN\n");
    } else {
      /* Converts command arguments to integers */
      int begin = atoi(argv[1]);
      int end = atoi(argv[2]);
      /* add the first and last index */
      int total = begin + end;

      /* add one to index if first argument is zero */
      if (begin == 0) {
        total += 1;
      }

      /* open file to access e_driver */
      dev_file = fopen("/dev/e", "r");
      /* Checks if driver exists */
      if(dev_file == NULL) {
        perror("This file does not exist. TRY AGAIN\n");
        return 1;
      }

      /* Create a buffer to allocate appropriate amount of spcae */
      buffer = (char*) malloc((total + 1)*sizeof(char));
      /* Reads in approriate number of bytes (plus one) */
      file_number = fileno(dev_file);
      f_read = read(file_number, buffer, (total + 1));
      /* checks if number of bytes is correct */
      if(f_read != (total + 1)) {
        printf("Error reading file. TRY AGAIN\n");
      }

      /* Prints substring to the terminal */
      int i;
      for(i = atoi(argv[1]); i < (total+1); i++) {
        printf("%c", buffer[i]);
      }
      printf("\n");

      /* Free allocated memory and close file */
      free(buffer);
      fclose(dev_file);
    }
  }
  return 0;
} /* end main */
