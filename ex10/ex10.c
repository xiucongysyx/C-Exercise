#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int j = 0;
    char *states[] = {
        NULL, "Oregon",
        "Washingron", NULL
    };
    int num_states = 4;
    
    argv[0] = states[2];
    // go through each string in argv
    // why am I skipping argv[0]?
    for(i = 0, j = 0; i < argc; i++, j = j+2){
        printf("j = %d and arg %d: %s\n", j, i, argv[i]);
    }

    //let's make our own array of strings
    states[0] = argv[1];
    for(i = 0; i < num_states; i++){
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
