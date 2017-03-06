#include <stdio.h>

size_t strlen(char *str);
int strcmp(const char *s1, const char *s2);

int main(int ac, char **av)
{
  if (ac >= 2)
    printf("%s got len of %lu\n",av[1], strlen(av[1]));
  if (ac >= 3)
    printf("cmp %s and %s = %d\n", av[1], av[2], strcmp(av[1], av[2]));
}
