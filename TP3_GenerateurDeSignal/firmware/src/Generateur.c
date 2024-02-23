// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du g�n�rateur

// Pr�vu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber


#include "Generateur.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "Mc32NVMUtil.h"
#include "Mc32DriverLcd.h"

// T.P. 2016 100 echantillons
#define MAX_ECH 100
#define VAL_MAX 65535
#define VAL_ECH 32767

S_ParamGen valeursParamGem;




// Initialisation du  g�n�rateur
void  GENSIG_Initialize(S_ParamGen *pParam)
{
    //R�cup�ration des donn�es sauvegard�es au d�marrage pr�c�dant
    NVM_ReadBlock(uint32_t valeursParamGem, sizeof(S_ParamGen));
    
    //Test pour v�rifier si 
    if(valeursParamGem->Magic == MAGIC)
    {
        *pParam = valeursParamGem;
    }
    else 
    {
        lcd_gotoxy(1,4);
        printf_lcd("Donnees par defaut");
        
        valeursParamGem->Amplitude = 0;    
        valeursParamGem->Forme = SignalCarre; 
        valeursParamGem->Frequence = 20;
        valeursParamGem->Magic = MAGIC;
        valeursParamGem->Offset = 0;
    }
        GENSIG_UpdatePeriode(&valeursParamGem);
}
  

// Mise � jour de la periode d'�chantillonage
void  GENSIG_UpdatePeriode(S_ParamGen *pParam)
{
}

// Mise � jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam)
{
    switch(valeursParamGem.Forme)
    {
        case SignalSinus:

            break; 
            
        case SignalTriangle:
            
            break ; 
            
            
        case SignalDentDeScie:
            
            break; 
            
            
        case SignalCarre: 
            
            break; 
            
        default:
            break;
        
        
        
    }
   
   
}


// Execution du g�n�rateur
// Fonction appel�e dans Int timer3 (cycle variable variable)

// Version provisoire pour test du DAC � modifier
void  GENSIG_Execute(void)
{
   static uint16_t EchNb = 0;
   const uint16_t Step = 65535 / MAX_ECH;

   SPI_WriteToDac(0, Step * EchNb );      // sur canal 0
   EchNb++;
   EchNb = EchNb % MAX_ECH;
}
