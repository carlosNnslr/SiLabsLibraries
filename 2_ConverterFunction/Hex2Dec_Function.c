/*---------------------------------------------------------------------------*-
   Hex2Dec ()
  -----------------------------------------------------------------------------
   Descriptif: Convertir la valeur hex en decimal
   Entrée    : *array, tableau à convertir                             (0..255)
               taille, taille du tableau                               (0..255)
   Sortie    : valDec, valeur converti en decimal                     (0..2^32)
-*---------------------------------------------------------------------------*/
unsigned long Hex2Dec (unsigned char *array,unsigned char taille)
{
    unsigned long valDec = 0;
    unsigned char i;

    for(i=0;i<taille;i++)
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