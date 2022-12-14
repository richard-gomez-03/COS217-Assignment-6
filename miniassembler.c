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
   unsigned int i;

   /* truncating end of uiSrc */
   uiSrc>>=uiSrcStartBit;

   leftShift = 32 - uiNumBits;

   /* truncating start of uiSrc */
   uiSrc<<=leftShift;

   /* shift back startpoint for dest */
   finalShift = (32 - (uiNumBits + uiDestStartBit));
   uiSrc>>=finalShift;
   
   *puiDest |= uiSrc;

   /* 0000....1000 */
   /* unsigned int testInt = 16; */

   /* 0000....1111 */
   /* unsigned int setter = 31; */

   /* 0000....0110 */
   /* unsigned int srcStart = 1; */

   /* 0000....0|11|0 */
   /* 0000....1|00|0 */
   /* unsigned int destStart = 1; */

   /* unsigned int bitNum = 2; */

   /* 0000....1|11|0 */
   /* setField(setter, srcStart, &testInt, destStart, bitNum); */
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   /* Your code here */
   unsigned int uiInstr;

   uiInstr = 0x52800000;

   setField(uiReg, 0, &uiInstr, 0, 5);

   setField(iImmed, 0, &uiInstr, 5, 15);

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
   /* Your code here */
   unsigned int uiInstr;
   unsigned int uiDisp;

   uiInstr = 0x39000000;

   /* destination */
   setField(uiFromReg, 0, &uiInstr, 0, 5);
   setField(uiFromReg, 0, &uiInstr, 5, 5);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   /* Your code here */
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   return uiInstr;
}
