#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#define GREEN_BOLD_INTENS "\e[1;92m"
#define RED_BOLD_INTENS "\e[1;91m"
#define CLEAR "\e[0m"

void	my_strlen_test(void *handle)
{
  size_t (*my_strlen)(const char *s);

  printf(GREEN_BOLD_INTENS"STRLEN:\n"CLEAR);
  if ((my_strlen = dlsym(handle, "strlen")) == NULL)
    {
      printf("Can't load strlen\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\t'%s' got len of %lu\n", "My sentence", my_strlen("My sentence"));
  printf("\t\t'%s' got len of %lu\n", "", my_strlen(""));
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\t'%s' got len of %lu\n", "My sentence", strlen("My sentence"));
  printf("\t\t'%s' got len of %lu\n", "", strlen(""));
}

void	my_strchr_test(void *handle)
{
  char *(*my_strchr)(const char *s, char c);
  char *chr1 = "abac";
  char *chr2 = "ab";
  char *chr3 = "abbc";
  char *reschr;

  printf(GREEN_BOLD_INTENS"STRCHR:\n"CLEAR);
  if ((my_strchr = dlsym(handle, "strchr")) == NULL)
    {
      printf("Can't load strchr\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  reschr = my_strchr(chr1, 'b');
  printf("\t\tsearch 'b' in 'abac' = %s\n", reschr ? reschr : "NULL");
  reschr = my_strchr(chr1, 'f');
  printf("\t\tsearch 'f' in 'abac' = %s\n", reschr ? reschr : "NULL");
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  reschr = strchr(chr1, 'b');
  printf("\t\tsearch 'b' in 'abac' = %s\n", reschr ? reschr : "NULL");
  reschr = strchr(chr1, 'f');
  printf("\t\tsearch 'f' in 'abac' = %s\n", reschr ? reschr : "NULL");
}
void	my_strcmp_test(void *handle)
{
  int (*my_strcmp)(const char *s, const char *s2);
  char *cmp1 = "abac";
  char *cmp2 = "ab";
  char *cmp3 = "abbc";

  printf(GREEN_BOLD_INTENS"STRCMP:\n"CLEAR);
  if ((my_strcmp = dlsym(handle, "strcmp")) == NULL)
    {
      printf("Can't load strcmp\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\tcompare 'abac' with 'abac' = %d\n", my_strcmp(cmp1, cmp1));
  printf("\t\tcompare 'abac' with 'ab' = %d\n", my_strcmp(cmp1, cmp2));
  printf("\t\tcompare 'abac' with 'abbc' = %d\n", my_strcmp(cmp1, cmp3));
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tcompare 'abac' with 'abac' = %d\n", strcmp(cmp1, cmp1));
  printf("\t\tcompare 'abac' with 'ab' = %d\n", strcmp(cmp1, cmp2));
  printf("\t\tcompare 'abac' with 'abbc' = %d\n", strcmp(cmp1, cmp3));
}
void	my_memset_test(void * handle)
{
  void *(*my_memset)(void *s, int c, size_t n);
  char str[] ="hello";
  char str1[]="hello";
  char str2[]="hello";
  char str3[]="hello";

  printf(GREEN_BOLD_INTENS"MEMSET:\n"CLEAR);
  if ((my_memset = dlsym(handle, "memset")) == NULL)
    {
      printf("Can't load memset\n");
      return ;
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
}
void	my_memcpy_test(void *handle)
{
  void *(*my_memcpy)(void *src, void *dest, size_t n);
  char strcpy[] ="hello";
  char strcpy1[]="hello";
  char strcpy2[]="hello";
  char strcpy3[]="hello";
  char strsrc[]="bonjour";

  printf(GREEN_BOLD_INTENS"MEMCPY:\n"CLEAR);
  if ((my_memcpy = dlsym(handle, "memcpy")) == NULL)
    {
      printf("Can't load memcpy\n");
      return ;
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
	 3, (char *)memcpy(strcpy2, strsrc, 3));
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 0, (char *)memcpy(strcpy3, strsrc, 0));
  printf("\t\tset 'hello' to 'bonjour' for %d: %s\n",
	 1, (char *)memcpy(strcpy3, strsrc, 1));
}

void	my_memmove_test(void *handle)
{
  void *(*my_memmove)(void *src, void *dest, size_t n);
  char strmemove[]="Memmove can be very useful......";
  char strmemove1[]="Memmove can be very useful......";
  char strmemove2[]="Memmove can be very useful......";
  char strmemove3[]="Memmove can be very useful......";
  char strmemove4[]="Memmove can be very useful......";

  printf(GREEN_BOLD_INTENS"MEMMOVE:\n"CLEAR);
  if ((my_memmove = dlsym(handle, "memmove")) == NULL)
    {
      printf("Can't load memmove\n");
      return;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  my_memmove(strmemove1 + 20, strmemove1 + 15, 11);
  printf("\t\tmove bytes from 20 to 15 for '%s': %s\n", strmemove, strmemove1);
  my_memmove(strmemove2 + 15, strmemove2 + 20, 11);
  printf("\t\tmove 12 bytes from 15 to 20 for '%s': %s\n"
	 ,strmemove, strmemove2);
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  memmove(strmemove3 + 20, strmemove3 + 15, 11);
  printf("\t\tmove bytes from 20 to 15 for '%s': %s\n", strmemove, strmemove3);
  memmove(strmemove4 + 15, strmemove4 + 20, 11);
  printf("\t\tmove 12 bytes from 15 to 20 for '%s': %s\n"
	 ,strmemove, strmemove4);
}

void	my_strncmp_test(void *handle)
{
  int (*my_strncmp)(const char *s, const char *s2, size_t n);

  printf(GREEN_BOLD_INTENS"STRNCMP:\n"CLEAR);
  if ((my_strncmp = dlsym(handle, "strncmp")) == NULL)
    {
      printf("Can't load strncmp\n");
      return ;
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
}

void	my_strcasecmp_test(void *handle)
{
  int (*my_strcasecmp)(const char *s, const char *s2);

  printf(GREEN_BOLD_INTENS"STRCASECMP:\n"CLEAR);
  if ((my_strcasecmp = dlsym(handle, "strcasecmp")) == NULL)
    {
      printf("Can't load strcasecmp\n");
      return ;
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
}

void	my_rindex_test(void *handle)
{
  char *str4="abac";
  char *res_index;
  char *(*my_rindex)(const char *s, int c);

  printf(GREEN_BOLD_INTENS"RINDEX:\n"CLEAR);
  if ((my_rindex = dlsym(handle, "rindex")) == NULL)
    {
      printf("Can't load rindex\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  res_index = my_rindex(str4, 'a');
  printf("\t\trindex 'a' in 'abac': %s\n", res_index ? res_index :"NULL");
  res_index = my_rindex(str4, '\0');
  printf("\t\trindex '\\0' in 'abac': %s\n", res_index ? res_index :"NULL");
  res_index = my_rindex(str4, 'd');
  printf("\t\trindex 'd' in abac: %s\n", res_index ? res_index :"NULL");
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  res_index = rindex(str4, 'a');
  printf("\t\trindex 'a' in 'abac': %s\n", res_index ? res_index :"NULL");
  res_index = rindex(str4, '\0');
  printf("\t\trindex '\\0' in 'abac': %s\n", res_index ? res_index :"NULL");
  res_index = rindex(str4, 'd');
  printf("\t\trindex 'd' in abac: %s\n", res_index ? res_index :"NULL");
}

void	my_strstr_test(void *handle)
{
  char *(*my_strstr)(const char *hay, const char *needle);
  char str_str1[]="abbcabacab";
  char str_str2[]="bac";
  char str_str3[]="cabb";
  char *res_str;
  char *test;

  printf(GREEN_BOLD_INTENS"STRSTR:\n"CLEAR);
  if ((my_strstr = dlsym(handle, "strstr")) == NULL)
    {
      printf("Can't load strstr\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  res_str = my_strstr(str_str1, str_str2);
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, str_str2, res_str ? res_str : "NULL");
  res_str = my_strstr(str_str1, str_str3);
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, str_str3, res_str ? res_str : "NULL");
  res_str = my_strstr(str_str1, "");
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, "", res_str ? res_str : "NULL");
  res_str = my_strstr(str_str1, "acab");
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, "acab", res_str ? res_str : "NULL");
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  res_str = strstr(str_str1, str_str2);
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, str_str2, res_str ? res_str : "NULL");
  res_str = strstr(str_str1, str_str3);
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, str_str3, res_str ? res_str : "NULL");
  res_str = strstr(str_str1, "");
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, "", res_str ? res_str : "NULL");
  res_str = strstr(str_str1, "acab");
  printf("\t\tstrstr: haystack '%s';needle '%s'; res '%s'\n",
	 str_str1, "acab", res_str ? res_str : "NULL");
}

void	my_strpbrk_test(void *handle)
{
  char *strpbrk1="I look in my sentence";
  char *strpbrk2="Je cherche dans ma phrase";
  char *strpbrk3="try";
  char *strpbrk4="look";
  char *res_strpbrk;
  char *(*my_strpbrk)(const char *s, const char *accept);

  printf(GREEN_BOLD_INTENS"STRPBRK:\n"CLEAR);
  if ((my_strpbrk = dlsym(handle, "strpbrk")) == NULL)
    {
      printf("Can't load strpbrk\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  res_strpbrk = my_strpbrk(strpbrk1, strpbrk3);
  printf("\t\tstrpbrk '%s' in '%s': %s\n",
	 strpbrk3, strpbrk1, res_strpbrk ? res_strpbrk :"NULL");
  res_strpbrk = my_strpbrk(strpbrk2, strpbrk3);
  printf("\t\tstrpbrk '%s' in '%s': %s\n",
	 strpbrk3, strpbrk2, res_strpbrk ? res_strpbrk :"NULL");
  res_strpbrk = my_strpbrk(strpbrk2, strpbrk4);
  printf("\t\tstrpbrk '%s' in '%s': %s\n",
  strpbrk4, strpbrk2, res_strpbrk ? res_strpbrk :"NULL");
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  res_strpbrk = strpbrk(strpbrk1, strpbrk3);
  printf("\t\tstrpbrk '%s' in '%s': %s\n",
	 strpbrk3, strpbrk1, res_strpbrk ? res_strpbrk :"NULL");
  res_strpbrk = strpbrk(strpbrk2, strpbrk3);
  printf("\t\tstrpbrk '%s' in '%s': %s\n",
	 strpbrk3, strpbrk2, res_strpbrk ? res_strpbrk :"NULL");
  res_strpbrk = strpbrk(strpbrk2, strpbrk4);
  printf("\t\tstrpbrk '%s' in '%s': %s\n",
	 strpbrk4, strpbrk2, res_strpbrk ? res_strpbrk :"NULL");
}

void	my_strcspn_test(void *handle)
{
  char *strcspn1="try in my sentence";
  char *strcspn2="Je cherche dans ma phrase";
  char *strcspn3="try";
  char *strcspn4="look";
  size_t res_strcspn;
  size_t (*my_strcspn)(const char *s, const char *accept);

  printf(GREEN_BOLD_INTENS"STRCSPN:\n"CLEAR);
  if ((my_strcspn = dlsym(handle, "strcspn")) == NULL)
    {
      printf("Can't load strcspn\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  res_strcspn = my_strcspn(strcspn1, strcspn3);
  printf("\t\tstrcspn '%s' in '%s': %lu\n", strcspn3, strcspn1, res_strcspn);
  res_strcspn = my_strcspn(strcspn2, strcspn3);
  printf("\t\tstrcspn '%s' in '%s': %lu\n", strcspn3, strcspn2, res_strcspn);
  res_strcspn = my_strcspn(strcspn2, strcspn4);
  printf("\t\tstrcspn '%s' in '%s': %lu\n", strcspn4, strcspn2, res_strcspn);
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  res_strcspn = strcspn(strcspn1, strcspn3);
  printf("\t\tstrcspn '%s' in '%s': %lu\n", strcspn3, strcspn1, res_strcspn);
  res_strcspn = strcspn(strcspn2, strcspn3);
  printf("\t\tstrcspn '%s' in '%s': %lu\n", strcspn3, strcspn2, res_strcspn);
  res_strcspn = strcspn(strcspn2, strcspn4);
  printf("\t\tstrcspn '%s' in '%s': %lu\n", strcspn4, strcspn2, res_strcspn);
}

void	my_write_test(void *handle)
{
  size_t (*my_write)(int fd, const void *buf, size_t count);

  printf(GREEN_BOLD_INTENS"WRITE:\n"CLEAR);
  if ((my_write = dlsym(handle, "write")) == NULL)
    {
      printf("Can't load write\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\twrite 3 bytes of 'abac' in output => %d bytes writed\n",
	 my_write(1, "abac", 3));
  printf("\t\twrite 4 bytes of 'abac' in output => %d bytes writed\n",
	 my_write(1, "abac", 4));
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\twrite 3 bytes of 'abac' in output => %d bytes writed\n",
	 write(1, "abac", 3));
  printf("\t\twrite 4 bytes of 'abac' in output => %d bytes writed\n",
	 write(1, "abac", 4));
}

void	my_read_test(void *handle)
{
  size_t (*my_read)(int fd, const void *buf, size_t count);
  char buf[10] = {0};
  size_t out;

  printf(GREEN_BOLD_INTENS"READ:\n"CLEAR);
  if ((my_read = dlsym(handle, "read")) == NULL)
    {
      printf("Can't load read\n");
      return ;
    }
  printf(RED_BOLD_INTENS"\tASM\n"CLEAR);
  printf("\t\tRead in input:\n");
  out = my_read(0, buf, 4);
  buf[4] = 0;
  printf("\t\tRead for 4 bytes the input: res => %s in %lu byte\n",
	 buf, out);
  printf(RED_BOLD_INTENS"\tEXPECTED\n"CLEAR);
  printf("\t\tRead in input:\n");
  out = my_read(0, buf, 4);
  buf[4] = 0;
  printf("\t\tRead for 4 bytes the input: res => %s in %lu byte\n",
	 buf, out);
}

int main(int ac, char **av)
{
  void *handle;

  printf(GREEN_BOLD_INTENS"ASM TEST\n"CLEAR);
  if ((handle = dlopen("./libasm.so", RTLD_LAZY)) == NULL)
    {
      printf("Can't open lib\n");
      return (0);
    }
  my_strlen_test(handle);
  my_strchr_test(handle);
  my_strcmp_test(handle);
  my_strncmp_test(handle);
  my_strcasecmp_test(handle);
  my_memset_test(handle);
  my_rindex_test(handle);
  my_memcpy_test(handle);
  my_strstr_test(handle);
  my_memmove_test(handle);
  my_strpbrk_test(handle);
  my_strcspn_test(handle);
  my_write_test(handle);
  my_read_test(handle);
  dlclose(handle);
}
