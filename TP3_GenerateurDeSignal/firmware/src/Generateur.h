#ifndef Generateur_h
#define Generateur_h

// TP3 MenuGen 2016
// C. HUBER  03.02.2016
// Fichier Generateur.h
// Prototypes des fonctions du g�n�rateur  de signal

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "DefMenuGen.h"


//extern const uint16_t tableauCourbeSinus[100]; //A ne pas d�clarer dans le .h pour ce projet car seulement utiliser dans Generateur.c et pas diff�rents fichiers. 

// Initialisation du  g�n�rateur
void  GENSIG_Initialize(S_ParamGen *pParam);


// Mise � jour de la periode d'�chantillonage
void  GENSIG_UpdatePeriode(S_ParamGen *pParam);


// Mise � jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam);

// A appeler dans int Timer3
void  GENSIG_Execute(void);


#endif