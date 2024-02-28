#include "shell.h"

/**
 * **strtow - separates a string into words. ignore repeated delimiters
 * @str: input string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int j, i, z, r, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!is_delim(str[j], d) && (is_delim(str[j + 1], d) || !str[j + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, i = 0; i < numwords; i++)
	{
		while (is_delim(str[j], d))
			j++;
		z = 0;
		while (!is_delim(str[j + z], d) && str[j + z])
			z++;
		s[i] = malloc((z + 1) * sizeof(char));
		if (!s[i])
		{
			for (z = 0; z < i; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < z; r++)
			s[i][r] = str[j++];
		s[i][r] = 0;
	}
	s[i] = NULL;
	return (s);
}

/**
 * **strtow2 - separates a string into words
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int j, i, z, r, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (j = 0; str[j] != '\0'; j++)
		if ((str[j] != d && str[j + 1] == d) ||
		    (str[j] != d && !str[j + 1]) || str[j + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, i = 0; i < numwords; i++)
	{
		while (str[j] == d && str[j] != d)
			j++;
		m = 0;
		while (str[j + z] != d && str[j + z] && str[j + z] != d)
			z++;
		s[i] = malloc((z + 1) * sizeof(char));
		if (!s[i])
		{
			for (z = 0; z < i; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < z; r++)
			s[i][r] = str[j++];
		s[i][r] = 0;
	}
	s[i] = NULL;
	return (s);
}
