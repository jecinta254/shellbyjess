#include "shell.h"

/**
 * jnj_getline - This is a getline function
 *
 */

ssize_t jnj_getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buffer[BUFFER_SIZE];
    static size_t buffer_index = 0;
    static size_t chars_in_buffer = 0;

    ssize_t total_chars_read = 0;
    char *current_position;

    if (*lineptr == NULL || *n == 0)
    {
        *n = BUFFER_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
        {
            return -1;
        }
    }

    current_position = *lineptr;

    while (1)
    {
        if (buffer_index == chars_in_buffer)
        {
            chars_in_buffer = read(fileno(stream), buffer, BUFFER_SIZE);

            if (chars_in_buffer <= 0)
            {
                if (total_chars_read == 0)
                {
                    return chars_in_buffer;
                }
                else
                {
                    break;
                }
            }

            buffer_index = 0;
        }

        *(current_position++) = buffer[buffer_index++];

        total_chars_read++;

        if (buffer_index > 0 && buffer[buffer_index - 1] == '\n')
        {
            break;
        }

        if ((size_t)total_chars_read >= *n)
        {
            *n += BUFFER_SIZE;
            *lineptr = realloc(*lineptr, *n);
            if (*lineptr == NULL)
            {
                return -1;
            }
        }
    }

    *current_position = '\0';

    return total_chars_read;
}
