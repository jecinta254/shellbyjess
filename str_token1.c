#include "shell.h"
/**
 * our_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *our_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * our_strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *our_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * our_puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void our_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		our_putchar(str[i]);
		i++;
	}
}

/**
 * our_putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int our_putchar(char c)
{
	static int i;
	static char buf[OUR_WRITE_BUF_SIZE];

	if (c == OUR_BUF_FLUSH || i >= OUR_WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != OUR_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
