#include "StringConversion.h"

/*---------------------------------------------------------------------------*-
   StrHex2Dec ()
  -----------------------------------------------------------------------------
   Description: Convert a hex string to decimal
   IN         : *strArray, hex string to convert		  (8 hex character max)
                sizeArray, size of the array                           (0..255)
   OUT        : decimal value                                         (0..2^32)
-*---------------------------------------------------------------------------*/
unsigned long StrHex2Dec (char* strArray, unsigned char sizeArray)
{
	//Local variable
	unsigned long valDec = 0;
	unsigned char i;
   
    for (i=0; i<sizeArray; i++)
    {
       if ((array[i] >= 0x30) && (array[i] <= 0x39))
       {
           valDec |= (unsigned long)(array[i] - 0x30)<<(28-(i*4));
       }
       else if((array[i] >= 0x41) && (array[i] <= 0x46))
       {
          valDec |= (unsigned long)(array[i] - 0x37)<<(28-(i*4));
       }
    }
    
    return valDec;
} // StrHex2Dec ------------------------------------------------------------------