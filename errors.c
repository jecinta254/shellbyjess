#include "shell.h"
/**
 * _our_eputs - prints an input string to stderr
 * @str: the string to be printed
 * Return: Nothing
 */
void _our_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_our_eputchar(str[i]);
		i++;
	}
}

/**
 * _our_eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _our_eputchar(char c)
{
	static int i;
	static char buf[OUR_WRITE_BUF_SIZE];

	if (c == OUR_BUF_FLUSH || i >= OUR_WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != OUR_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _our_putfd - writes the character c to a given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _our_putfd(char c, int fd)
{
	static int i;
	static char buf[OUR_WRITE_BUF_SIZE];

	if (c == OUR_BUF_FLUSH || i >= OUR_WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != OUR_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _our_putsfd - prints an input string to a given fd
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * Return: the number of characters put
 */
int _our_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _our_putfd(*str++, fd);
	}
	return (i);
}
