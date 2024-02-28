#include "shell.h"

/**
 **_memset - fill memory with a constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - frees string of strings
 * @pp: string of strings
 */
void ffree(char **qq)
{
	char **a = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(a);
}

/**
 * _realloc - relocates a block of memory
 * @ptr: ptr to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
