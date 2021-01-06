#include "utils.h"
/**
 *_realloc - array with the range of integer
 *@ptr: array
 *@old_size: old array sizee
 *@new_size: new array size
 *Return: int array with min to max
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *array = NULL;
	unsigned int minimum, i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	array = malloc(new_size);
	if (array == NULL)
	{
		free(ptr);
		return (NULL);
	}
	_memset(array, 0, new_size);
	if (ptr == NULL)
	{
		return (array);
	}
	if (new_size > old_size)
		minimum = old_size;
	else
		minimum = new_size;
	for (i = 0; i < minimum; i++)
		array[i] = *((char *)ptr + i);
	free(ptr);
	return ((void *)array);
}
