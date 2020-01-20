/*---------------------------------------------------------------------------*-
   CalculErreur ()
  -----------------------------------------------------------------------------
   Descriptif: Calcul l'erreur en % entre 2 valeurs positives et plafonne le 
               résultat à +- 100 

   formule : erreur [%] = ((mesure - consigne) / consigne) * 100

   Remarque 1 : calcul impossible si la consigne vaut 0 --> division par 0 !!
                le résultat sera :
                     0 si la mesure = 0
                     +100 si la mesure est > 0

   Remarque 2 : calcul pour les valeurs max  :
                  consigne = 1 et mesure = 255 --> résultat =  25'400 %
                  consigne = 255 et mesure = 0 --> résultat =    -100 %
               
   Entrée    : valConsigne, la valeur de consigne                      (0..255) 
               valMesure, la valeur mesurée                            (0..255) 
   Sortie    : l'erreur calculée                                   (-100..+100)
-*---------------------------------------------------------------------------*/
char CalculErreur (unsigned char valConsigne, unsigned char valMesure)
{
   int resultat;

   if (valConsigne == 0)  // cas de la consigne = 0 
   {
      if  (valMesure == 0)    // même valeur donc pas d'erreur
      {
         resultat = 0;
      }
      else  // erreur infinie --> résultat plafoné à +100
      {
         resultat = 100;
      }
   }
   else  // autres cas : consigne <> 0
   {
      resultat = ((((int)valMesure-valConsigne) * 100) / valConsigne);
      
      if (resultat > 100)  // test de débordement
      {
         resultat = 100;      // fixe la valeur plafond
      }
   }

   return (resultat);

} // CalculErreur -------------------------------------------------------------