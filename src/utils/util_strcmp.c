#include "utils.h"
/**
 * str_srch - search a character inside a string
 * @array: string to search
 * @charac: character to search for
 * Return: Always 0 on success
 */
int str_srch(char *array, char charac)
{
	int index = -1, i = 0;

	for (; array[i]; i++)
	{
		if (charac == array[i])
		{
			index = i;
			return (index);
		}
	}
	return (index);
}

/**
 * _strncmp - compares strings
 * @p1: string to compare
 * @p2: string to compare
 * @n: max len to compare
 * Return: Always 0 on success
 */
int _strncmp(char *p1, char *p2, int n)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;
	int i = 1;

	do {
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0' || i++ == n)
			return (c1 - c2);
	} while (c1 == c2);
	return (c1 - c2);
}

