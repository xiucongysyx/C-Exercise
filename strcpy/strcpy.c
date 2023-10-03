#include <stdio.h>

size_t strlen(const char *s) {
    size_t n = 0;
    while (*s != '\0') {
        s++;
        n++;
    }
    return n;
}

char *strcpy(char *dst, const char *src) {
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
    return dst;
}

int main() {
    char dest[100];
    const char *src = "Hello, World!";
    
    char *result = strcpy(dest, src);
    
    printf("复制前的字符串: %s\n", src);
    printf("复制后的字符串: %s\n", dest);
    
    return 0;
}

