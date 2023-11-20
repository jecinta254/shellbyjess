#include "shell.h"
/**
 * our_list_len - determines length of linked list
 * @current_node: pointer to the current node
 * Return: size of list
 */
size_t our_list_len(const our_list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * our_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **our_list_to_strings(our_list_t *head)
{
	our_list_t *current_node = head;
	size_t size = our_list_len(head), index;
	char **strings_array;
	char *str;

	size_t j;

	if (!head || !size)
		return (NULL);

	strings_array = malloc(sizeof(char *) * (size + 1));
	if (!strings_array)
		return (NULL);

	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		str = malloc(our_strlen(current_node->str) + 1);
		if (!str)
		{
			for (j = 0; j < index; j++)
				free(strings_array[j]);
			free(strings_array);
			return (NULL);
		}

		str = our_strcpy(str, current_node->str);
		strings_array[index] = str;
	}

	strings_array[index] = NULL;
	return (strings_array);
}


/**
 * our_print_list - prints all elements of a our_list_t linked list
 * @current_node: pointer to current node
 *
 * Return: size of list
 */
size_t our_print_list(const our_list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		our_puts(our_convert_number(current_node->num, 10, 0));
		our_putchar(':');
		our_putchar(' ');
		our_puts(current_node->str ? current_node->str : "(nil)");
		our_puts("\n");
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * our_node_starts_with - returns node whose string starts with prefix
 * @current_node: pointer to current node
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
our_list_t *our_node_starts_with(our_list_t
*current_node, char *prefix, char c)
{
	char *p = NULL;

	while (current_node)
	{
		p = our_starts_with(current_node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * our_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @target_node: pointer to the target node
 *
 * Return: index of node or -1
 */
ssize_t our_get_node_index(our_list_t *head, our_list_t *target_node)
{
	size_t index = 0;

	while (head)
	{
		if (head == target_node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
