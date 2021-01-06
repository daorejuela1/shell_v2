#include "utils.h"
/**
 * _puts - writes a string in stdout
 * @s: The string to print
 * Return: On length of characters written
 */
int _puts(char *s)
{
	int length = 0;

	while (*(s + length) != 0)
	{
		_putchar(*(s + length));
		length++;
	}
	return (length);
}
