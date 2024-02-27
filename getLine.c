#include "shell.h"

/**
 * input_buf -the buffers chained commands
 * @info: the parameter struct
 * @buf: the address of buffer
 * @len: the address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t m = 0;
	size_t len_q = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		m = getline(buf, &len_q, stdin);
#else
		m = _getline(info, buf, &len_q);
#endif
		if (m > 0)
		{
			if ((*buf)[m - 1] == '\n')
			{
				(*buf)[m - 1] = '\0';
				m--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = m;
				info->cmd_buf = buf;
			}
		}
	}
	return (m);
}

/**
 * get_input - finds a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t j, i, len;
	ssize_t m = 0;
	char **buf_q = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	m = input_buf(info, &buf, &len);
	if (m == -1) /* EOF */
		return (-1);
	if (len)
	{
		i = j;
		q = buf + j;

		check_chain(info, buf, &i, j, len);
		while (i < len)
		{
			if (is_chain(info, buf, &i))
				break;
			i++;
		}

		j = i + 1;
		if (j >= len)
		{
			j = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_q = q;
		return (_strlen(q));
	}

	*buf_q = buf;
	return (m);
}

/**
 * read_buf - reads the buffer
 * @info: parameter struct
 * @buf: buffer
 * @j: size
 *
 * Return: m
 */
ssize_t read_buf(info_t *info, char *buf, size_t *j)
{
	ssize_t m = 0;

	if (*j)
		return (0);
	m = read(info->readfd, buf, READ_BUF_SIZE);
	if (m >= 0)
		*j = m;
	return (m);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info:the parameter struct
 * @ptr: the address of pointer to buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t z;
	ssize_t m = 0, s = 0;
	char *q = NULL, *new_q = NULL, *c;

	q = *ptr;
	if (q && length)
		s = *length;
	if (j == len)
		j = len = 0;

	m = read_buf(info, buf, &len);
	if (m == -1 || (m == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	z = c ? 1 + (unsigned int)(c - buf) : len;
	new_q = _realloc(q, s, s ? s + z : z + 1);
	if (!new_q) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (s)
		_strncat(new_q, buf + j, z - j);
	else
		_strncpy(new_q, buf + j, z - j + 1);

	s += z - j;
	j = z;
	q = new_q;

	if (length)
		*length = s;
	*ptr = q;
	return (s);
}

/**
 * sigintHandler - it blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
