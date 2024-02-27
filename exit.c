#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, i;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		i = j;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (s);
}

/**
 **_strncat -it  concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: the amount of bytes to be maximally used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, i;
	char *s = dest;

	j = 0;
	i = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0' && i < n)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	if (i < n)
		dest[j] = '\0';
	return (s);
}

/**
 **_strchr - it locates a character in a string
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
