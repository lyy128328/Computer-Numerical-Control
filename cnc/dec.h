#ifndef DEC_H
#define DEC_H

#include"StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>



#include <windows.h>



enum DECODER_STATE {INIT, READY, RUN, END_LINE, END_M30, ERR}; //enumeration ¦CÁ|

/*
       N digits
	   G  01, 04, 90, 91
	   XYZ real
	   F  real
	   M30

	   G04 X2000      // WAIT 2000 ms


*/

struct DECODER_DATA   // data struct declaration«Å§i
{                     // no memory reserved!!!
   enum DECODER_STATE   state;

   char         buffer[80];
   char         *asciiPtr;
   FILE         *filePtr;
   char			fileName[100];
   
   double		xyzNow[3];

   int          blockNr;        // for N...
   bool         nInput;
   int          blockCommand;   // for  G01,G04
   bool         g01Input;  
   bool         g04Input;

   double       feed;           // F
   bool         fInput;

   double       dwellTime;        // G04 X...
   double       xyzCoordinate[3]; // XYZ
   bool         xyzInput[3];
   bool         rel;             // G91: true, G90: false
   bool         g91g90input;
   bool         m30Input;

   bool         inputPlease;

   bool			fileOk;
   bool			cyclestart;

}; 


int decMain(DECODER_DATA *dataPtr);
void init(DECODER_DATA *dataPtr);
void ready(DECODER_DATA *dataPtr);
void run(DECODER_DATA *dataPtr);

void endM30(DECODER_DATA *dataPtr);

void nFunction(DECODER_DATA *dataPtr);
void gFunction(DECODER_DATA *dataPtr);
int  mFunction(DECODER_DATA *dataPtr);
void fFunction(DECODER_DATA *dataPtr);
void xyzFunction(DECODER_DATA *dataPtr);
void endOfLine(DECODER_DATA *dataPtr);
void endM30(DECODER_DATA *dataPtr);
void err(DECODER_DATA *dataPtr);
int  passSpace(char *charPtr);


// global variable definition

DECODER_DATA      decoderData;  // memory reserved!!!
DECODER_DATA      *decoderDataPtr;

#endif