#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#define GREEN_BOLD_INTENS "\e[1;92m"
#define RED_BOLD_INTENS "\e[1;91m"
#define CLEAR "\e[0m"

int main(int ac, char **av)
{
  void *handle;

  printf(GREEN_BOLD_INTENS"ASM TEST\n"CLEAR);
  if ((handle = dlopen("./libasm.so", RTLD_LAZY)) == NULL)
    {
      printf("Can't open lib\n");
      return (0);
    }

  //STRLEN
  size_t (*my_strlen)(const char *s);

  printf(GREEN_BOLD_INTENS"STRLEN:\n"CLEAR);
  if ((my_strlen = dlsym(handle, "strlen")) == NULL)
    {
      printf("Can't load strlen\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\t'%s' got len of %lu\n", "My sentence", my_strlen("My sentence"));
  printf("\t\t'%s' got len of %lu\n", "", my_strlen(""));

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\t'%s' got len of %lu\n", "My sentence", strlen("My sentence"));
  printf("\t\t'%s' got len of %lu\n", "", strlen(""));


  //STRCMP
  int (*my_strcmp)(const char *s, const char *s2);
  char *cmp1 = "abac";
  char *cmp2 = "ab";
  char *cmp3 = "abbc";

  printf(GREEN_BOLD_INTENS"STRCMP:\n"CLEAR);
  if ((my_strcmp = dlsym(handle, "strcmp")) == NULL)
    {
      printf("Can't load strcmp\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
    printf("\t\tcompare 'abac' with 'abac' = %d\n",
	 my_strcmp(cmp1, cmp1));
  printf("\t\tcompare 'abac' with 'ab' = %d\n",
	 my_strcmp(cmp1, cmp2));
  printf("\t\tcompare 'abac' with 'abbc' = %d\n",
	 my_strcmp(cmp1, cmp3));

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tcompare 'abac' with 'abac' = %d\n",
	 strcmp(cmp1, cmp1));
  printf("\t\tcompare 'abac' with 'ab' = %d\n",
	 strcmp(cmp1, cmp2));
  printf("\t\tcompare 'abac' with 'abbc' = %d\n",
	 strcmp(cmp1, cmp3));

  //STRNCMP
  int (*my_strncmp)(const char *s, const char *s2, size_t n);

  printf(GREEN_BOLD_INTENS"STRNCMP:\n"CLEAR);
  if ((my_strncmp = dlsym(handle, "strncmp")) == NULL)
    {
      printf("Can't load strncmp\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\tcompare 'abac' with 'abbc' for %d bytes = %d\n",
	 2, my_strncmp("abac", "abbc", 2));
  printf("\t\tcompare 'abac' with 'abbc' for %d bytes = %d\n",
	 4, my_strncmp("abac", "abbc", 4));
  printf("\t\tcompare 'abac' with 'abac' for %d bytes = %d\n",
	 10, my_strncmp("abac", "abac", 10));
  printf("\t\tcompare 'abac' with 'abac' for %d bytes = %d\n",
	 0, my_strncmp("abac", "abac", 0));

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tcompare 'abac' with 'abbc' for %d bytes = %d\n",
	 2, strncmp("abac", "abbc", 2));
  printf("\t\tcompare 'abac' with 'abbc' for %d bytes = %d\n",
	 4, strncmp("abac", "abbc", 4));
  printf("\t\tcompare 'abac' with 'abac' for %d bytes = %d\n",
	 10, strncmp("abac", "abac", 10));
  printf("\t\tcompare 'abac' with 'abac' for %d bytes = %d\n",
	 0, strncmp("abac", "abac", 0));


  //STRCASECMP
  int (*my_strcasecmp)(const char *s, const char *s2);

  printf(GREEN_BOLD_INTENS"STRCASECMP:\n"CLEAR);
  if ((my_strcasecmp = dlsym(handle, "strcasecmp")) == NULL)
    {
      printf("Can't load strcasecmp\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\tcompare 'abac' with 'ABAC' = %d\n",
	 my_strcasecmp("abac", "ABAC"));
  printf("\t\tcompare 'abac' with 'aBaB' = %d\n",
	 my_strcasecmp("abac", "aBaB"));
  printf("\t\tcompare 'aba' with 'ABaC' = %d\n",
	 my_strcasecmp("aba", "ABaC"));

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tcompare 'abac' with 'ABAC' = %d\n",
	 strcasecmp("abac", "ABAC"));
  printf("\t\tcompare 'abac' with 'aBaB' = %d\n",
	 strcasecmp("abac", "aBaB"));
  printf("\t\tcompare 'aba' with 'ABaC' = %d\n",
	 strcasecmp("aba", "ABaC"));

  //MEMSET
  void *(*my_memset)(void *s, int c, size_t n);
  char str[]="hello";
  char str1[]="hello";
  char str2[]="hello";
  char str3[]="hello";

  printf(GREEN_BOLD_INTENS"MEMSET:\n"CLEAR);
  if ((my_memset = dlsym(handle, "memset")) == NULL)
    {
      printf("Can't load memset\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\tset 'hello' to 'a' for %d: %s\n",
	 3, (char *)my_memset(str, 'a', 3));
  printf("\t\tset 'hello' to 'a' for %d: %s\n",
	 0, (char *)my_memset(str1, 'a', 0));
  printf("\t\tset 'hello' to 'a' for %d: %s\n",
  1, (char *)my_memset(str1, 'a', 1));

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tset 'hello' to 'a' for %d: %s\n",
	 3, (char *)memset(str2, 'a', 3));
  printf("\t\tset 'hello' to 'a' for %d: %s\n",
	 0, (char *)memset(str3, 'a', 0));
  printf("\t\tset 'hello' to 'a' for %d: %s\n",
	 1, (char *)memset(str3, 'a', 1));


  //RINDEX
  char *str4="abac";
  char *res_index;
  char *(*my_rindex)(const char *s, int c);

  printf(GREEN_BOLD_INTENS"RINDEX:\n"CLEAR);
  if ((my_rindex = dlsym(handle, "rindex")) == NULL)
    {
      printf("Can't load rindex\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  res_index = my_rindex(str4, 'a');
  printf("\t\trindex 'a' in 'abac': %s\n",
	 res_index ? res_index :"NULL");
  res_index = my_rindex(str4, '\0');
  printf("\t\trindex '\\0' in 'abac': %s\n",
	 res_index ? res_index :"NULL");
  res_index = my_rindex(str4, 'd');
  printf("\t\trindex 'd' in abac: %s\n",
	 res_index ? res_index :"NULL");

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  res_index = rindex(str4, 'a');
  printf("\t\trindex 'a' in 'abac': %s\n",
	 res_index ? res_index :"NULL");
  res_index = rindex(str4, '\0');
  printf("\t\trindex '\\0' in 'abac': %s\n",
	 res_index ? res_index :"NULL");
  res_index = rindex(str4, 'd');
  printf("\t\trindex 'd' in abac: %s\n",
	 res_index ? res_index :"NULL");

  //MEMCPY
  void *(*my_memcpy)(void *src, void *dest, size_t n);
  char strcpy[]="hello";
  char strcpy1[]="hello";
  char strcpy2[]="hello";
  char strcpy3[]="hello";
  char strsrc[]="bonjour";

  printf(GREEN_BOLD_INTENS"MEMCPY:\n"CLEAR);
  if ((my_memcpy = dlsym(handle, "memcpy")) == NULL)
    {
      printf("Can't load memcpy\n");
      return (0);
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 3, (char *)my_memcpy(strcpy, strsrc, 3));
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 0, (char *)my_memcpy(strcpy1, strsrc, 0));
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 1, (char *)my_memcpy(strcpy1, strsrc, 1));

  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 3, (char *)memcpy(strcpy, strsrc, 3));
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 0, (char *)memcpy(strcpy1, strsrc, 0));
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 1, (char *)memcpy(strcpy1, strsrc, 1));



  //CLOSE
  dlclose(handle);
}
