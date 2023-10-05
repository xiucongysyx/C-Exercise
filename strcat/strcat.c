#include <stdio.h>

int strcmp(const char *s1, const char *s2) {
  while(*s1++ == *s2++) {
    if(*s1 == '\0') return 0;
  }
  return *s1 - *s2;
}

char *strcpy(char *dst, const char *src) {
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
    return dst;
}

size_t strlen(const char *s) {
    size_t n = 0;
    while (*s != '\0') {
        s++;
        n++;
    }
    return n;
}

char *strcat(char *dst, const char *src) {
    dst = dst + strlen(dst);
    return strcpy(dst, src);
}

int main() {
    char dest[100] = "Hello, ";
    const char *src = "World!";
	const char *src_bk = "World!";
    const char *add = "Goodbye!";
    
    printf("原始目标字符串: %s\n", dest);
    printf("等待复制字符串: %s\n", src);

    // 使用 strcpy 复制字符串
    strcpy(dest, src);
    printf("复制后的字符串: %s\n", dest);
    printf("待增加的字符串: %s\n", add);

    // 使用 strcat 追加字符串
    strcat(dest, add);
    printf("追加后的字符串: %s\n", dest);

	printf("比较相同字符串: %d\n", strcmp(src, src_bk));
	printf("比较不同字符串: %d\n", strcmp(dest, src));
	
    return 0;
}

