// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du g�n�rateur
// Traitement cyclique � 10 ms



#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h"
#include "Mc32DriverLcd.h"
#include "app.h"
#include "GesPec12.h"
#include <math.h>

const char MenuFormes[4][21] = {"Sinus", "Triangle", "DentDeScie", "Carre"};

// Initialisation du menu et des param�tres
void MENU_Initialize(S_ParamGen *pParam)
{
    pParam->Amplitude = 0;
    pParam->Forme = SignalSinus;
    pParam->Frequence = 20;
    pParam->Magic = 0x12345678;
    pParam->Offset = 0;
}


// Execution du menu, appel cyclique depuis l'application
void MENU_Execute(S_ParamGen *pParam)
{
    static MENU_STATE menuStat = SEL_FORME; 
    static MENU_STATE oldMenuStat = SET_FORME;
    static S_ParamGen tempData;
    static uint8_t i = 0;
    
    if(!i)
    {
        AfficheMenu(pParam);
        CopieStructS_ParamGen(&tempData, pParam);
        i++;
    }
    
    if(menuStat % 2)
    {
        if(Pec12IsOK())
        {
            menuStat --;
        }
        else if(Pec12IsPlus())
        {
            switch(menuStat)
            {
                case SET_FORME:
                    if(tempData.Forme < SignalCarre)
                    {
                        tempData.Forme++;
                    }
                    else
                    {
                        tempData.Forme = SignalCarre;
                    }
                    break;
                    
                case SET_FREQU:
                    if(tempData.Frequence < FREQU_MAX)
                    {
                        tempData.Frequence += FREQU_MIN;
                    }
                    else
                    {
                        tempData.Frequence = FREQU_MIN;
                    }
                    break;
                    
                case SET_AMPL:
                    if(tempData.Amplitude < AMPL_MAX)
                    {
                        tempData.Amplitude += PAS_AMPL;
                    }
                    else
                    {
                        tempData.Amplitude = AMPL_MIN;
                    }
                    break;
                    
                case SET_OFFSET:
                    if(tempData.Offset < OFFSET_MAX)
                    {
                        tempData.Offset += PAS_OFFSET;
                    }
                    else
                    {
                        tempData.Offset = OFFSET_MAX;
                    }
                    break;
                
                default:
                    break;
            }
        }
        else if(Pec12IsMinus())
        {
            switch(menuStat)
            {
                case SET_FORME:
                    if(tempData.Forme > SignalSinus)
                    {
                        tempData.Forme--;
                    }
                    else
                    {
                        tempData.Forme = SignalSinus;
                    }
                    break;
                    
                case SET_FREQU:
                    if(tempData.Frequence > FREQU_MIN)
                    {
                        tempData.Frequence -= FREQU_MIN;
                    }
                    else
                    {
                        tempData.Frequence = FREQU_MAX;
                    }
                    break;
                    
                case SET_AMPL:
                    if(tempData.Amplitude > AMPL_MIN)
                    {
                        tempData.Amplitude -= PAS_AMPL;
                    }
                    else
                    {
                        tempData.Amplitude = AMPL_MAX;
                    }
                    break;
                    
                case SET_OFFSET:
                    if(tempData.Offset > OFFSET_MIN)
                    {
                        tempData.Offset -= PAS_OFFSET;
                    }
                    else
                    {
                        tempData.Offset = OFFSET_MIN;
                    }
                    break;
                    
                default:
                    break;
            }
        }
    }
    else
    {
        if(Pec12IsOK())
        {
            menuStat ++;
        }
        else if(Pec12IsPlus())
        {
            menuStat += 2;
            if(menuStat >= SAVE)
            {
                menuStat = SEL_FORME;
            }
        }
        else if(Pec12IsMinus())
        {
            menuStat -= 2;
            if(menuStat > SAVE)
            {
                menuStat = SEL_OFFSET;
            }
        }
    }
    
    // Enlever l'ast�rix
    if((abs(oldMenuStat - menuStat)) >= 2)
    {
        lcd_gotoxy(1,1); 
        printf_lcd(" ");
        lcd_gotoxy(1,2); 
        printf_lcd(" ");
        lcd_gotoxy(1,3); 
        printf_lcd(" ");
        lcd_gotoxy(1,4); 
        printf_lcd(" ");
    }
    // Sauvegarde de l'�tat du menu
    oldMenuStat = menuStat;
    
    switch(menuStat)
    {
        case SEL_FORME:
            lcd_gotoxy(1,1); 
            printf_lcd("*");
//            if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SET_FORME:
            lcd_gotoxy(1,1); 
            printf_lcd("?");
            lcd_gotoxy(10,1);
            printf_lcd("%10s", MenuFormes[tempData.Forme]);
//            if(Pec12IsOK())
//            {
//                menuStat = SEL_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SEL_FREQU:
            lcd_gotoxy(1,2); 
            printf_lcd("*");
//            if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SET_FREQU:
            lcd_gotoxy(1,2); 
            printf_lcd("?");
            lcd_gotoxy(15,2);
            printf_lcd("%4d", tempData.Frequence);
            //if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SEL_AMPL:
            lcd_gotoxy(1,3); 
            printf_lcd("*");
//            if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SET_AMPL:
            lcd_gotoxy(1,3); 
            printf_lcd("?");
            lcd_gotoxy(14,3);
            printf_lcd("%5d", tempData.Amplitude);
//            if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SEL_OFFSET:
            lcd_gotoxy(1,4); 
            printf_lcd("*");
//            if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SET_OFFSET:
            lcd_gotoxy(1,4); 
            printf_lcd("?");
            lcd_gotoxy(16,4);
            printf_lcd("%5d", tempData.Offset);
//            if(Pec12IsOK())
//            {
//                menuStat = SET_FORME;
//            }
//            else if(Pec12IsPlus())
//            {
//                menuStat = SEL_OFFSET;
//            }
//            else if(Pec12IsMinus())
//            {
//                menuStat = SEL_FREQU;
//            }
            break;
        case SAVE:
            
            break;
        default:
            break;
    }  
        
    Pec12ClearOK();
    Pec12ClearPlus();
    Pec12ClearMinus();
}

//-------------------------------
// Fonction d'affichage du menu
// Auteur: JAR, MPT
// Date: 08.03.2024
// Entr�es: -
// Sortie: -
//-------------------------------
void AfficheMenu(S_ParamGen *pParam)
{
    lcd_gotoxy(2,1); 
    printf_lcd("Forme = %10s  ", MenuFormes[pParam->Forme]);
    lcd_gotoxy(2,2); 
    printf_lcd("Freq [Hz] =  %4d   ", pParam->Frequence);
    lcd_gotoxy(2,3); 
    printf_lcd("Ampl [mV] = %5d   ", pParam->Amplitude);
    lcd_gotoxy(2,4); 
    printf_lcd("Offset [Hz] = %5d ", pParam->Offset);
}

//-------------------------------
// Fonction de copie d'une structure de type 
// Le deuxi�me param�tre va �tre copi� dans le premier
// Auteur: JAR, MPT
// Date: 08.03.2024
// Entr�es: -
// Sortie: -
//-------------------------------
void CopieStructS_ParamGen(S_ParamGen *pParam1, S_ParamGen *pParam2)
{
    pParam1->Amplitude = pParam2->Amplitude;
    pParam1->Forme = pParam2->Forme;
    pParam1->Frequence = pParam2->Frequence;
    pParam1->Offset = pParam2->Offset;
}

