#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
void print_letters(char arg[], int num_letter);

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    int num_arguments = 0;
    for(i = 0; i < argc; i++) {
        num_arguments = strlen(argv[i]);
        print_letters(argv[i], num_arguments);
    }
}

void print_letters(char arg[], int num_letter)
{
    int i = 0;

    for(i = 0; i < num_letter; i++) {
        char ch = arg[i];
        if(isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
