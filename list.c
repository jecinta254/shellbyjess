#include "shell.h"

/**
 * our_add_node - adds a node to the start of the list
 * @our_head: address of pointer to head node
 * @our_str: str field of node
 * @our_num: node index used by history
 *
 * Return: size of list
 */
our_list_t *our_add_node(our_list_t **our_head, const char *our_str, int our_num)
{
	our_list_t *new_our_head;

	if (!our_head)
		return (NULL);
	new_our_head = malloc(sizeof(our_list_t));
	if (!new_our_head)
		return (NULL);
	our_memset((void *)new_our_head, 0, sizeof(our_list_t));
	new_our_head->num = our_num;
	if (our_str)
	{
		new_our_head->str = our_strdup(our_str);
		if (!new_our_head->str)
		{
			free(new_our_head);
			return (NULL);
		}
	}
	new_our_head->next = *our_head;
	*our_head = new_our_head;
	return (new_our_head);
}

/**
 * our_add_node_end - adds a node to the end of the list
 * @our_head: address of pointer to head node
 * @our_str: str field of node
 * @our_num: node index used by history
 *
 * Return: size of list
 */
our_list_t *our_add_node_end(our_list_t **our_head, const char *our_str, int our_num)
{
	our_list_t *new_our_node, *our_node;

	if (!our_head)
		return (NULL);
	our_node = *our_head;
	new_our_node = malloc(sizeof(our_list_t));
	if (!new_our_node)
		return (NULL);
	our_memset((void *)new_our_node, 0, sizeof(our_list_t));
	new_our_node->num = our_num;
	if (our_str)
	{
		new_our_node->str = our_strdup(our_str);
		if (!new_our_node->str)
		{
			free(new_our_node);
			return (NULL);
		}
	}
	if (our_node)
	{
		while (our_node->next)
			our_node = our_node->next;
		our_node->next = new_our_node;
	}
	else
		*our_head = new_our_node;
	return (new_our_node);
}

/**
 * our_print_list_str - prints only the str element of a our_list_t linked list
 * @our_h: pointer to first node
 *
 * Return: size of list
 */
size_t our_print_list_str(const our_list_t *our_h)
{
	size_t i = 0;

	while (our_h)
	{
		our_puts(our_h->str ? our_h->str : "(nil)");
		our_puts("\n");
		our_h = our_h->next;
		i++;
	}
	return (i);
}

/**
 * our_delete_node_at_index - deletes node at given index
 * @our_head: address of pointer to first node
 * @our_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int our_delete_node_at_index(our_list_t **our_head, unsigned int our_index)
{
	our_list_t *our_node, *our_prev_node;
	unsigned int i = 0;

	if (!our_head || !*our_head)
		return (0);
	if (!our_index)
	{
		our_node = *our_head;
		*our_head = (*our_head)->next;
		free(our_node->str);
		free(our_node);
		return (1);
	}
	our_node = *our_head;
	while (our_node)
	{
		if (i == our_index)
		{
			our_prev_node->next = our_node->next;
			free(our_node->str);
			free(our_node);
			return (1);
		}
		i++;
		our_prev_node = our_node;
		our_node = our_node->next;
	}
	return (0);
}

/**
 * our_free_list - frees all nodes of a list
 * @our_head_ptr: address of pointer to head node
 *
 * Return: void
 */
void our_free_list(our_list_t **our_head_ptr)
{
	our_list_t *our_node, *our_next_node, *our_head;

	if (!our_head_ptr || !*our_head_ptr)
		return;
	our_head = *our_head_ptr;
	our_node = our_head;
	while (our_node)
	{
		our_next_node = our_node->next;
		free(our_node->str);
		free(our_node);
		our_node = our_next_node;
	}
	*our_head_ptr = NULL;
}
