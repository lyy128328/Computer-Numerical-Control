// intp.h
#ifndef INTP_H
#define INTP_H
#include"StdAfx.h"

enum INTP_STATE {INTP_INIT, INTP_READY, INTP_RUN, INTP_ERR}; 
enum INTP_V_STATE {V_INCRE, V_SAME, V_DECRE, END_G01};

#define A 5

#include "link.h"

struct INTP_DATA
{
   INTP_STATE   state;
   INTP_V_STATE vState;


   double       cycleTime;     // 30ms
   double		cycleVincre;   // A * cycleTime
 

   PATH_BLOCK   pathBlock;
   double       xyzStart[3];   // coordinate management
   double       xyzEnd[3];
   double       xyzNew[3];
   double       xyzOld[3];     // backup 
   double		xyzAnswer[3];

   double		startToEnd[3];
  

   double       totalLength;
   double       halfTotalLength;
   double		increCycleMaxLength;
   double		increCycleLength;
   double       momtLength;    // sum length
   double       deltaS;        // delta S in one cycle
   double		sameVlength;
   double		difference;

   int			increCycle;
   int			sameCycle;
   int			decreCycle;

   double		increCycleMax;
   double		sameCycleMax;
   double		decreCycleMax;

   double		vOld;
   double		vNew;
   double		vInsert;
   bool			insert;

   double		unitVector[3];

};


// global variable definition

extern INTP_DATA      intpData;  // memory reserved!!!
extern INTP_DATA     *intpDataPtr;

int intpMain(INTP_DATA *intpDataPtr);
int intpInit(INTP_DATA *intpDataPtr);
int	intpReady(INTP_DATA *intpDataPtr);
int intpRun(INTP_DATA *intpDataPtr);
int intpErr(INTP_DATA *intpDataPtr);
void g01function(INTP_DATA *intpDataPtr);
void g04function(INTP_DATA *intpDataPtr);
void m30function(INTP_DATA *intpDataPtr);
void v_incre(INTP_DATA *intpDataPtr);
void v_same(INTP_DATA *intpDataPtr);
void v_decre(INTP_DATA *intpDataPtr);
void pointIncre(INTP_DATA *intpDataPtr);

#endif