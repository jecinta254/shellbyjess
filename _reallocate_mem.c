#include "shell.h"
/**
 **our_memset - fills memory with a constant byte
 *@our_s: the pointer to the memory area
 *@our_b: the byte to fill *custom_s with
 *@our_n: the amount of bytes to be filled
 *Return: (our_s) a pointer to the memory area custom_s
 */
char *our_memset(char *our_s, char our_b, unsigned int our_n)
{
	unsigned int i;

	for (i = 0; i < our_n; i++)
		our_s[i] = our_b;
	return (our_s);
}

/**
 * our_ffree - frees a string of strings
 * @our_pp: string of strings
 */
void our_ffree(char **our_pp)
{
	char **a = our_pp;

	if (!our_pp)
		return;
	while (*our_pp)
		free(*our_pp++);
	free(a);
}

/**
 * our_realloc - reallocates a block of memory
 * @our_ptr: pointer to previous malloc'ated block
 * @our_old_size: byte size of previous block
 * @our_new_size: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *our_realloc(void *our_ptr,
unsigned int our_old_size, unsigned int our_new_size)
{
	char *p;

	if (!our_ptr)
		return (malloc(our_new_size));
	if (!our_new_size)
		return (free(our_ptr), NULL);
	if (our_new_size == our_old_size)
		return (our_ptr);

	p = malloc(our_new_size);
	if (!p)
		return (NULL);

	our_old_size = our_old_size < our_new_size ?
	our_old_size : our_new_size;
	while (our_old_size--)
		p[our_old_size] = ((char *)our_ptr)[our_old_size];
	free(our_ptr);
	return (p);
}
