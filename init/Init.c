/*---------------------------------------------------------------------------*-
   IRQInit();
  -----------------------------------------------------------------------------
   Descriptif: Initialisation des interruption externe 
   Entrée    : --
   Sortie    : --
-*---------------------------------------------------------------------------*/
void IRQInit(void)
{
// Interruption externe 0 --------------------------------------------------
   EX0 = 0;                 // Inhibe l'interruption INT0 

   IT0 = 1;                 // Interruption actif sur transition. 
   IT01CF = IT01CF & 0xF0;  // Clear bit de configuration INT0  
   
                            //     +----- Etat haut ou transition montante  
                            //     |+++-- INT0 sur bit 3 du port 0 
                            //     |||| 
   IT01CF = IT01CF | 0x0B;  // xxxx1011 
   
   IE0 = 0;              // Délais pour garantir le positionnement du flag IE
   IE0 = 0;              // 
   IE0 = 0;              // Efface une interruption résiduelle

// Interruption externe 1 --------------------------------------------------
   EX1 = 0;                 // Inhibe l'interruption INT1 

   IT1 = 1;                 // Interruption actif sur transition. 
   IT01CF = IT01CF & 0xF0;  // Clear bit de configuration INT1  
   
                            // +----- Etat haut ou transition montante  
                            // |+++-- INT1 sur bit 3 du port 0 
                            // |||| 
   IT01CF = IT01CF | 0xB0;  // 1011xxxx 
   
   IE1 = 0;              // Délais pour garantir le positionnement du flag IE
   IE1 = 0;              // 
   IE1 = 0;              // Efface une interruption résiduelle
}// IRQInit

/*---------------------------------------------------------------------------*-
   PCAInit ()
  -----------------------------------------------------------------------------
   Descriptif: Initialisation du mode de fonctionnement du PCA
                  - PCA0 en mode PWM 8 bits
                  - clock PCA = 12 MHz (SYSCLK/4)
                      --> fout = 12 MHZ / 256 = 46.9 KHz
                  - Interruptions PCA0 bloquées

   Entrée    : --                           
   Sortie    : --
-*---------------------------------------------------------------------------*/
void PCAInit ()
{

   CR = 0;              // bloque le fonctionnement du PCA

   // choix du mode de fonctionnement du compteur du PCA  ---------------------
   PCA0MD  &= ~0x8E; //  0xxx/000X     Reset les bits utilisés

                     //   +------------- mode Idle
                     //   |               0 : bloqué
                     //   |               1 : autorisé
                     //   |    000 ----- SYSCLK/12
                     //   |    001 ----- SYSCLK/4
                     //   |    010 ----- débordement du Timer 0
                     //   |    011 ----- flanc montant sur l'entrée ECI
                     //   |    100 ----- SYSCLK
                     //   |    101 ----- clock externe/8
                     //   |    |||
   PCA0MD |= 0x02;   //   0xxx/001x  

   
   // choix du mode de fonctionnement du module PCA0  -------------------------
                        //    +----------  définition PMW  
                        //    |               0 :  8 bits
                        //    |               1 : 16 bits
                        //    |+---------  comparateur PCA
                        //    ||              0 : bloqué
                        //    ||              1 : autorisé
                        //    ||+--------  mode capture positive
                        //    |||             0 : bloqué
                        //    |||             1 : autorisé
                        //    |||+--------  mode capture négative
                        //    ||||            0 : bloqué
                        //    ||||            1 : autorisé
                        //    |||| +-----  mode math    
                        //    |||| |          0 : bloqué
                        //    |||| |          1 : autorisé
                        //    |||| |+----  mode bascule   
                        //    |||| ||         0 : bloqué
                        //    |||| ||         1 : autorisé
                        //    |||| ||+---  mode PMW       
                        //    |||| |||        0 : bloqué
                        //    |||| |||        1 : autorisé
                        //    |||| |||+--- interruptions 
                        //    |||| ||||       0 : bloqués
                        //    |||| ||||       1 : autorisés
                        //    |||| ||||
   PCA0CPM0 = 0x42;     //    0100/0010   // mode PWM 8 bit autorisé

   // calcul de la valeur de pré-chargement en mode 8 bits --------------------
   // %PMW = ((256 - PCA0CPH)/256) * 100
   //   --> PCA0CPH = 256 - ((%PWM/100) * 256)
   // exemple avec 28 % --> PCA0CPH = 256 - (28/100)*256 = 184,32 --> 0xB8
   
   PCA0CPL0  = 0xB8;    // valeur de départ de la consigne PMW = 28 %
   PCA0CPH0  = 0xB8;    // consigne PMW = 28 %

} // PCAInit ------------------------------------------------------------------


/*---------------------------------------------------------------------------*-
   TimerInit();
  -----------------------------------------------------------------------------
   Descriptif: Initialisation du timer 0 et 1
   Entrée    : --
   Sortie    : --
-*---------------------------------------------------------------------------*/
void Timer1Init(void)
{
   TR1=0;
   ET1=0;
   TMOD &= 0xF0;
                  
                  // ++++------- Non utilisé.
                  // |||| +----- GATE ? 
                  // |||| |+---- Choix de l'entrée du timer
                  // |||| ||         (0 : incrémentation par le clock système)
                  // |||| ||         (1 : incrémentation externe (T0) )
                  // |||| ||++-- choix du mode :
                  // |||| ||||       (00 : compteur 13 bits)
                  // |||| ||||       (01 : compteur 16 bits)
                  // |||| ||||       (10 : compteur  8 bits auto reload)
   TMOD |= 0x01;  // 0000 0001 

                     // ++++ +----- Non utilisé.
                     // |||| |+---- Choix du clock
                     // |||| ||     0 : clock système divisé
                     // |||| ||     1 : Clock système
                     // |||| ||++-- choix du diviseur du clock pour timer:
                     // |||| ||||       (00 : clock système / 12)
                     // |||| ||||       (01 : clock système / 4 )
                     // |||| ||||       (10 : clock système / 48)
   CKCON |= 0x02;    // 0000 0010 

/*   

//------------- TIMER 0 ---------------
//------------ Mode 16 bit ------------

//  TH0=(CAPA_COMPT_16BITS-N_INTERVALLE)/256;
//  TL0=(CAPA_COMPT_16BITS-N_INTERVALLE)%256;

//------ Mode 8 bit auto reload -------

 TH0=CAPA_COMPT_8BITS-N_INTERVALLE;
 TL0=CAPA_COMPT_8BITS-N_INTERVALLE;

//--- Autorise interruption timer 0 ---
   TR0=1;
   ET0=1;
   TF0=0; //Mets a 0 l'interruption
//-------------------------------------

//*/

// /*

//------------- TIMER 1 ---------------
//------------ Mode 16 bit ------------

  TH1=(CAPA_COMPT_16BITS-N_INTERVALLE)/256;
  TL1=(CAPA_COMPT_16BITS-N_INTERVALLE)%256;

//------ Mode 8 bit auto reload -------

// TH1=CAPA_COMPT_8BITS-N_INTERVALLE;
// TL1=CAPA_COMPT_8BITS-N_INTERVALLE;

//--- Autorise interruption timer 1 ---
   //TR1=1;
   //ET1=1;
   TF1=0; //Mets a 0 l'interruption
//-------------------------------------

// */
}