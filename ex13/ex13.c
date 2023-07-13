#include <stdio.h>

int main(int argc, char *argv[])
{
//    if(argc !=2){
        printf("You have %d argument.\n", argc);

//        return 1;
//    }

    int i = 0,j = 0;
    char letter;
    for(j = 0; j <= argc; j++){
        for(i = 0, letter = 0; argv[1][i] != '\0'; i++){
            letter = argv[1][i];

            switch(letter) {
                case 'a':
                case 'A':
                    printf("%d_%d: 'A'\n", j, i);
                    break;

                case 'e':
                case 'E':
                    printf("%d_%d: 'E'\n", j, i);
                    break;

                case 'i':
                case 'I':
                    printf("%d_%d: 'I'\n", j, i);
                    break;

                case 'o':
                case 'O':
                    printf("%d_%d: 'O'\n", j, i);
                    break;

                case 'u':
                case 'U':
                    printf("%d_%d: 'U'\n", j, i);
                    break;

                case 'y':
                case 'Y':
                    if(i > 2){
    
                        printf("%d_%d: 'Y'\n", j, i);
                        break;
                    }
    
                default:
                    printf("%d_%d: %c is not a vowel\n", j, i, letter);
            }
        }
    }

    return 0;
}
