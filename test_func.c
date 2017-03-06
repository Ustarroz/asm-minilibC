#include <stdio.h>

size_t strlen(char *str);

int main(int ac, char **av)
{
  if (ac >= 2)
    printf("%s got len of %lu\n",av[1], strlen(av[1]));
}
