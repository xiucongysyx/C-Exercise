#include<stdio.h>
typedef unsigned long long int op_t;
typedef unsigned long int	uintptr_t;
int
strcmp (const char *p1, const char *p2)
{
  /* Handle the unaligned bytes of p1 first.  */
  /* op_t 是一个长长整型的类型，是64位无符号整数。 */
  /* uintptr_t 是一个长整形的类型，是64位无符号整数。 */
  uintptr_t n = -(uintptr_t)p1 % sizeof(op_t);
  for (int i = 0; i < n; ++i)
    {
      unsigned char c1 = *p1++;
      unsigned char c2 = *p2++;
      int diff = c1 - c2;
      if (c1 == '\0' || diff != 0)
	return diff;
    }

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  const op_t *x1 = (const op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % sizeof(op_t);
  return ofs == 0
    ? 1000
    : 0;
}

int main()
{
	char *str1 = "abcdefgh";
	char *str2 = "abcdefgh";
	int *str3 = (char *)str2;
printf("%d\n",	strcmp(str1, (char *)str3));
	return 0;
}
