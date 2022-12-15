/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Richard Gomez                                              */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void) {
    unsigned long bssAddress;
    unsigned int movInstruction;
    unsigned int adrInstruction;
    unsigned int strbInstruction;
    unsigned int bInstruction;
    int i;

    FILE *psFile;
    psFile = fopen("dataA", "w");

    fprintf(psFile, "Richard Gomez");
    putc('\0', psFile);

    movInstruction = MiniAssembler_mov(0, 'A');
    fwrite(&movInstruction, sizeof(unsigned int), 1, psFile);
    
    adrInstruction = MiniAssembler_adr(1, 0x420044, 0x40086c);
    fwrite(&adrInstruction, sizeof(unsigned int), 1, psFile);

    strbInstruction = MiniAssembler_strb(0, 1);
    fwrite(&strbInstruction, sizeof(unsigned int), 1, psFile);
    
    bInstruction = MiniAssembler_b(0x400874, 0x420072);
    fwrite(&bInstruction, sizeof(unsigned int), 1, psFile);

    for(i = 0; i < 26; i++) {
        putc('\0', psFile);
    }

    bssAddress = 0x420066;
    fwrite(&bssAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}