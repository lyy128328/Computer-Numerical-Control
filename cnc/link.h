// link.h

#ifndef LINK_H
#define LINK_H

#include"StdAfx.h"
enum BLOCK_CMD { NULL_CMD=0,  G00, G01, G02, G03, G04,M30_CMD=100}; 

struct PATH_BLOCK 
{
   int         blockNumber;       // N
   BLOCK_CMD    blockCommand;     // G01 or G04 or M30
   double       feed;             // F
   double       dwellTime;        // G04 X...
   double       xyzCoordinate[3]; // XYZ
   bool         xyzInput[3];
   bool         rel;              // G90 or G91
};


int initLink (void);

#endif

