#include<stdio.h>
strcmp (const char *s1, const char *s2)
{
    while(*s1++ == *s2++) {
        if(*s1 == '\0') return 0;
    }
    printf("s1 = %c  s2 = %c a-b = %d s1-s2 = %d\n", *(s1-1), *(s2-1), 'a' - 'b', *(s1-1) - *(s2-1));
    return *(s1-1) - *(s2-1);
}

char *s[] = {
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	", World!\n",
	"Hello, World!\n",
	"#####"
};

char str1[] = "Hello";
char str[20];

void check(int i) {
	if(i == 0) {
	printf("strcmp correct\n"); 
	return;
	}
	else {
	printf("strcmp value = %d\n", i); 
	return;
	}
}

int main()
{
	check(strcmp(s[0], s[2]) == 0);
	check(strcmp(s[0], s[1]) < 0);
	check(strcmp(s[0] + 1, s[1] + 1) < 0);
	check(strcmp(s[0] + 2, s[1] + 2) < 0);
	check(strcmp(s[0] + 3, s[1] + 3) < 0);

	return 0;
}
