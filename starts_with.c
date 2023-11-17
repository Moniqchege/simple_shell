#include "shell.h"

/**
 * starts_with - checks if a string starts with a specified prefix
 * @str: the string to check
 * @prefix: the prefix to look for
 *
 * Return: pointer to the start of the prefix in str if found, otherwise NULL
 */
char *starts_with(char *str, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix != *str)
            return NULL;
        prefix++;
        str++;
    }
    return str;
}
