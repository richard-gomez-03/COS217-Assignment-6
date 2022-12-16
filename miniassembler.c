/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   unsigned int leftShift;
   unsigned int finalShift;

   /* truncating end of uiSrc */
   uiSrc>>=uiSrcStartBit;


   /* truncating start of uiSrc */
   leftShift = 32 - uiNumBits;
   uiSrc<<=leftShift;

   /* shift back to start point for dest */
   finalShift = (32 - (uiNumBits + uiDestStartBit));
   uiSrc>>=finalShift;

   /* OR operation to change contents of puiDest in place */ 
   *puiDest |= uiSrc;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;

   /* Base Instruction Code */
   uiInstr = 0x52800000;

   /* register that contents will be stored in */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* immediate value to be stored in register */
   setField(iImmed, 0, &uiInstr, 5, 16);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr;

   /* Base Instruction Code */
   uiInstr = 0x39000000;

   /* Register data is being accessed from */
   setField(uiFromReg, 0, &uiInstr, 0, 5);

   /* Register data is being stored to */
   setField(uiToReg, 0, &uiInstr, 5, 5);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned long uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x14000000;

   /* The displacement between the instructions divided by the number of
      bytes each instruction line takes */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr) / 4;

   /* Setting the displacemnt */
   setField(uiDisp, 0, &uiInstr, 0, 26);

   return uiInstr;
}
