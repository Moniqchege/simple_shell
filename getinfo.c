#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **) info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar (BUF_FLUSH);
	}
}

/**
 * replace_alias - replaces aliases in the input string
 * @info: parameter struct
 *
 * Return: void
 */
void replace_alias(info_t *info)
{
    list_t *alias_list = info->alias;
    char *input = info->arg;
    char *alias, *value;

    while (alias_list)
    {
        alias = _strdup(alias_list->str);
        value = _strchr(alias, '=');

        if (value)
        {
            *value = '\0'; /* Null-terminate alias */
            value++;
            if (starts_with(input, alias))
            {
                /* Replace alias with its value in the input string */
                char *replacement = _strdup(value);
                char *rest_of_input = input + _strlen(alias);

                char *new_input = _realloc(NULL, _strlen(replacement) + _strlen(rest_of_input) + 1, 0);
                _strcpy(new_input, replacement);
                _strcat(new_input, rest_of_input);

                free(info->arg); /* Free the old input */
                info->arg = new_input;
                input = new_input; /* Update the input pointer */
            }
        }

        free(alias);
        alias_list = alias_list->next;
    }
}
