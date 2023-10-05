#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMSET 1

void *ownmemset(void *dst, int c, size_t len) {
    char *dstp = (char *)dst;
    while(len-- != 0) {
        *dstp++ = c;
    }
    return dst;
}

int ownmemcmp(const void *s1, const void *s2, size_t n) {
    char *s1p = (char *)s1;
    char *s2p = (char *)s2;
    while(n-- != 0) {
        if(*s1p++ != *s2p++) {
            return (*(s1p-1) - *(s2p-1));
        }
    }
    return 0; 
}

int main() {
#ifdef MEMSET
    char *dst1 = (char *)malloc(8);
    int *dst2 = (int *)malloc(5*sizeof(int));
    int *dst3 = (int *)malloc(2*sizeof(int));
    char *dst4 = (char *)malloc(8);
    ownmemset(dst1, 'a', 8);
    dst3 = (int *)dst1;
    char *dst5 = ownmemset(dst3, 'b', 2);
    ownmemset(dst2, 'a', 5);
    printf("dst1 = %s sizeof(*dst1) = %ld\n", dst1, sizeof(*dst1));
    printf("*dst5 = %s\n", dst5);
    printf("*dst2 = %c *(dst2 + 4) = %c sizeof(*dst2) = %ld\n", *dst2, *(dst2+1), sizeof(*dst2));
    dst4 = (char *)dst3;
    printf("*dst3 = %s, *(dst3 + 1) = %s\n",(char *)dst3, (char *)(dst3 + 1));
    return 0;
#elif 
    char *s1 = "aaaa";
    char *s2 = "aaab";
    char *s3 = "#####";
    char s4[20];
    printf("s2 s2 3 = %d\n", ownmemcmp(s1, s2, 3));
    printf("s2 s2 4 = %d\n", ownmemcmp(s1, s2, 4));
    printf("expr = %d s3 = %s, s4 = %s\n", ownmemcmp(ownmemset(s4, '#', 5), s3, 5), s3, s4);
    return 0;
#endif
}
