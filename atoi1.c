#include "shell.h"

/**
 * ourInteractive - returns true if shell is in interactive mode
 * @Struct: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int ourInteractive(our_info_t *Struct)
{
	return (isatty(STDIN_FILENO) && Struct->readFileDescriptor <= 2);
}

/**
 * ourDelimiter - checks if character is a delimiter
 * @character: the char to check
 * @delm: the delimiter string
 * Return: 1 if true, 0 if false
 */
int ourDelimiter(char character, char *delm)
{
	while (*delm)
		if (*delm++ == character)
			return (1);
	return (0);
}

/**
 * ourAlpha - checks for alphabetic character
 * @character: The character to input
 * Return: 1 if character is alphabetic, 0 otherwise
 */
int ourAlpha(int character)
{
	if ((character >= 'a' && character <= 'z') ||
			(character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToInteger - converts a string to an integer
 * @inputString: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int stringandInteger(char *ourString)
{
	int index, sign = 1, flag = 0, change;
	unsigned int Value = 0;

	for (index = 0; ourString[index] != '\0' && flag != 2; index++)
	{
		if (ourString[index] == '-')
			sign *= -1;

		if (ourString[index] >= '0' && ourString[index] <= '9')
		{
			flag = 1;
			Value *= 10;
			Value += (ourString[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		change = -Value;
	else
		change = Value;

	return (change);
}
