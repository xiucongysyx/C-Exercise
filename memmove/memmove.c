#include <stdio.h>
#include <string.h>
char *mystrncpy(char *dst, const char *src, size_t n) {
  char *dstp = (char *)dst;
  while(n-- != 0) {
    *dstp++ = *src++;
  }
  return dst;
}
int mystrncmp(const char *s1, const char *s2, size_t n) {
  while(n-- != 0) {
    if(*s1 != *s2) return (*s1 - *s2);
    s1++;
    s2++;
  }
  return 0;
}
void *mymemmove(void *dst, const void *src, size_t n) {
  char *dstp = (char *)dst;
  char *srcp = (char *)src;
  if(src > dst || src + n < dst) {
    while(n-- != 0) *dstp++ = *srcp++;
  }
  else {
    while(n-- != 0) *(dstp + n + 1) = *(srcp + 1 + n);
  }
  return dst;
}
void *mymemcpy(void *out, const void *in, size_t n) {
  char *outp = (char *)out;
  char *inp = (char *)in;
  while(n-- != 0) {
    *outp++ = *inp++;
  }
  return out;
}
int main() {
  char src[] = "Hello, World!";
  char dest[20];
  
  // Test strncpy
  printf("dest+5: %c\tdest+6: %c\n", *(dest+5), *(dest+6));
  printf("strncpy: %s\n", (char *)strncpy(dest, src, 5));
  printf("strncpy: %s\n", (char *)dest);

  // Test strncmp
  int result = strncmp("apple", "apples", 5);
  printf("strncmp: %d\n", result);

  // Test memmove
  char buffer1[] = "memmove test";
  char buffer2[20];
  printf("memmove: %s\n", (char *)memmove(buffer2, buffer1, 12));
  printf("memmove: %s\n", (char *)buffer2);

  // Test memcpy
  char source[] = "memcpy test";
  char destination[20];
  
  printf("memcpy: %s\n", (char *)memcpy(destination, source, 11));
  printf("memcpy: %s\n", (char *)destination);

  return 0;
}
