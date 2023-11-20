#include "shell.h"
/**
 * _our_strncpy - copies a string
 * @our_dest: the destination string to be copied to
 * @our_src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_our_strncpy(char *our_dest, char *our_src, int n)
{
	int i, j;
	char *s = our_dest;

	i = 0;
	while (our_src[i] != '\0' && i < n - 1)
	{
		our_dest[i] = our_src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			our_dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _our_strncat - concatenates two strings
 * @our_dest: the first string
 * @our_src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_our_strncat(char *our_dest, char *our_src, int n)
{
	int i, j;
	char *s = our_dest;

	i = 0;
	j = 0;
	while (our_dest[i] != '\0')
		i++;
	while (our_src[j] != '\0' && j < n)
	{
		our_dest[i] = our_src[j];
		i++;
		j++;
	}
	if (j < n)
		our_dest[i] = '\0';
	return (s);
}

/**
 * _our_strchr - locates a character in a string
 * @our_s: the string to be parsed
 * @our_c: the character to look for
 * Return: (our_s) a pointer to the memory area s
 */
char *_our_strchr(char *our_s, char our_c)
{
	do {
		if (*our_s == our_c)
			return (our_s);
	} while (*our_s++ != '\0');

	return (NULL);
}
