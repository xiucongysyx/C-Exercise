#include <stdio.h>
int main( void )
{
    int integer;
    char string[81];
        
    /* Read each word as a string. */
    printf( "Enter a sentence of four words with scanf: " );
    for( integer = 0; integer < 4; integer++ )
    {
        scanf( "%s", string );
        printf( "%d = %s\n",integer, string );
    }
                 
    /* You must flush the input buffer before using gets. */
    //fflush( stdin );
    printf( "Enter the same sentence with gets: " );
    scanf( "%s", string );
    printf( "%s\n", string );
    return 0;
}
