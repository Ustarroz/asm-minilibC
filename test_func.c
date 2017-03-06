#include <stdio.h>

size_t strlen(char *str);
int strcmp(const char *s1, const char *s2);
char *strchr(const char *s, int c);

int main(int ac, char **av)
{
  if (ac >= 2)
    printf("STRLEN: %s got len of %lu\n",av[1], strlen(av[1]));
  if (ac >= 3)
    printf("STRCMP: cmp %s and %s = %d\n", av[1], av[2], strcmp(av[1], av[2]));
  if (ac >= 3)
    printf("STRCHR: %s and %c = %s\n",
	   av[1], av[2][0], strchr(av[1], av[2][0]));
}
