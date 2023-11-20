#include "shell.h"
/**
 * our_fpointer - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Return: 1 if freed and success, else 0.
 */
int our_fpointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
