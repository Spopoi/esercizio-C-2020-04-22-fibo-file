/*
 * esercizio-C-2020-04-22-fibo-file.c
 *
 *  Created on: 24 apr 2020
 *      Author: utente
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

unsigned long fibonacci(unsigned long n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

unsigned long* fibonacci_array(unsigned int n) {
	unsigned long *result = calloc(1, sizeof(unsigned long));
	for (int i = 0; i < n + 1; i++) {
		result = realloc(result, (i + 1) * sizeof(unsigned long));
		result[i] = fibonacci(i);
	}
	return result;
}

char* itoa_printf(int number) {
	char *result;

	// include '\0'
	//printf("minimum string len: %d\n",min_string_len(number));

	result = calloc(12, sizeof(char));

	snprintf(result, // zona di memoria in cui snprintf scriverà la stringa di caratteri
			12, // dimensione della zona di memoria
			"%d", // stringa di formattazione
			number); // numero intero da convertire in stringa

	return result;
}

int main(int argc, char *argv[]) {

	unsigned long *fibonacci_result = fibonacci_array(39);
	int fd = open("fibonacci.txt", O_CREAT | O_TRUNC | O_WRONLY,
	S_IRUSR | S_IWUSR);
	if (fd == -1) { // errore!

		perror("open()");

		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 40; i++) {
		char *text_to_write = itoa_printf(fibonacci_result[i]);
		text_to_write = strcat(text_to_write, "\n");
		int res = write(fd, text_to_write, strlen(text_to_write) + 1);
		if (res == -1) {
			perror("write()");
			exit(EXIT_FAILURE);
		} else if (res != strlen(text_to_write) + 1)
			printf("Non ho scritto tutti i byte");
	}

	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	printf("bye!\n");
	free(fibonacci_result);
	exit(EXIT_SUCCESS);
}

