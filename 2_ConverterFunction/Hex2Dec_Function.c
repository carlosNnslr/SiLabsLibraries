/*---------------------------------------------------------------------------*-
   Hex2Dec ()
  -----------------------------------------------------------------------------
   Descriptif: Convert hex value to decimal
   IN        : *array, array to convert                               (0..255)
               sizeArray, array size                                  (0..255)
   OUT       : valDec, value converted to decimal                     (0..2^32)
-*---------------------------------------------------------------------------*/
unsigned long Hex2Dec (unsigned char *array,unsigned char sizeArray)
{
   //Local variable
   #ifndef LOCAL_VARIABLE
    unsigned long valDec = 0;
    unsigned char i;
   #endif
   
    for(i=0;i<sizeArray;i++)
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
} // Hex2Dec ------------------------------------------------------------------