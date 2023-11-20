#include "shell.h"

/**
 * main - entry point
 * @our_ac: arg count
 * @our_av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int our_ac, char **our_av)
{
	our_info_t info[] = { OUR_INFO_INIT };
	int our_fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (our_fd)
		: "r" (our_fd));

	if (our_ac == 2)
	{
		our_fd = open(our_av[1], O_RDONLY);
		if (our_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_our_eputs(our_av[0]);
				_our_eputs(": 0: Can't open ");
				_our_eputs(our_av[1]);
				_our_eputchar('\n');
				_our_eputchar(OUR_BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readFileDescriptor = our_fd;
	}
	populate_our_env_list(info);
	our_read_history(info);
	our_hsh(info, our_av);
	return (EXIT_SUCCESS);
}
