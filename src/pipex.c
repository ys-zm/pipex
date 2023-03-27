#include "pipex.h"
#include <stddef.h>

//compares not more than n characters.
//return int >, + or < 0. - if s1 is >, + < s2.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*(unsigned char *)s1 == 0 || *(unsigned char *)s2 == 0)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
//access() to check if the function exists
int main(int argc, char **argv, char **envp)
{
    
}