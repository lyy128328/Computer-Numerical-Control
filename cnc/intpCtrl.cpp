#include"StdAfx.h"
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>






#include "link.h"
#include "intp.h"


extern PATH_BLOCK *pathBlockPtr;
extern bool       pathBlockValid;


INTP_DATA      intpData;  // memory reserved!!!
INTP_DATA      *intpDataPtr;


//************************************************
//
//************************************************
int intpInit(INTP_DATA *intpDataPtr)
{
	int   i;

    char    *bytePtr = (char *)intpDataPtr;

	// delete all memory 
	for (i=0; i < sizeof(INTP_DATA); i++)
	{
	  *bytePtr = 0; // ++ to next byte
	}

	// ...??? OTHER INIT ACTIONS   ???
	// initialize xyzEnd
	intpDataPtr->xyzEnd[0] = 75;
	intpDataPtr->xyzEnd[1] = 0;
	intpDataPtr->xyzEnd[2] = 0;

	intpDataPtr->cycleTime = 0.03; //30MS

	intpDataPtr->state = INTP_READY;

   return 1;
}  // intpInit()



//************************************************
//
//************************************************
int	intpReady(INTP_DATA *intpDataPtr)
{
	if (pathBlockValid == true)
	{  // new pathBlock comes from DEC!!
	  intpDataPtr->pathBlock = *pathBlockPtr;
	  pathBlockValid = false; // finish hand shaking with DEC
	  intpDataPtr->state = INTP_RUN;
	}

   return 1;
} //intpReady()


//************************************************
//
//************************************************
int intpRun(INTP_DATA *intpDataPtr)
{
	// processing the pathBlock
	// G01: move to new target point
	// G04: wait ..second
	// M30: program end

	// send command to motion card
	// or do the interpolation to calculate the axial coordinates
	// in real time for example 30 ms
	 
	switch(intpDataPtr->pathBlock.blockCommand)
	{
	case 'G01':
		g01function(intpDataPtr);
		break;
	case 'G04':
		g04function(intpDataPtr);
		break;
	case 'M30':
		m30function(intpDataPtr);
		break;
	}



   return 1;
} // intpRun()



//************************************************
//
//************************************************
int intpErr(INTP_DATA *intpDataPtr)
{

   return 1;
} //intpErr()

//************************************************
//
//************************************************
void g01function(INTP_DATA *intpDataPtr)
{
	bool  g01Loop;
	g01Loop = true;
	
	intpData.vState = V_INCRE;
	
	while (g01Loop == true)
	{
		switch(intpDataPtr->vState)
		{
		case V_INCRE:
			v_incre(intpDataPtr);
			break;
		case V_SAME:
			v_same(intpDataPtr);
			break;
		case V_DECRE:
			v_decre(intpDataPtr);
			break;
		case END_G01:
			g01Loop = false;
			break;
		}
	}
	
} // g01function()

//************************************************
//
//************************************************
void v_incre(INTP_DATA *intpDataPtr)
{	

	
	if (pathBlockPtr->rel==true) //relative motion
	{
		// give a start point
		intpDataPtr->xyzStart[0] = intpDataPtr->xyzEnd[0];
		intpDataPtr->xyzStart[1] = intpDataPtr->xyzEnd[1];
		intpDataPtr->xyzStart[2] = intpDataPtr->xyzEnd[2];
		// give an end point
		intpDataPtr->xyzEnd[0] = pathBlockPtr->xyzCoordinate[0] + intpDataPtr->xyzStart[0];
		intpDataPtr->xyzEnd[1] = pathBlockPtr->xyzCoordinate[1] + intpDataPtr->xyzStart[1];
		intpDataPtr->xyzEnd[2] = pathBlockPtr->xyzCoordinate[2] + intpDataPtr->xyzStart[2];
		// call function to count points
		pointIncre(intpDataPtr);
	}
	
	else //absolute motion
	{	

		// give a start point
		intpDataPtr->xyzStart[0] = intpDataPtr->xyzEnd[0];
		intpDataPtr->xyzStart[1] = intpDataPtr->xyzEnd[1];
		intpDataPtr->xyzStart[2] = intpDataPtr->xyzEnd[2];
		// give an end point
		intpDataPtr->xyzEnd[0] = pathBlockPtr->xyzCoordinate[0];
		intpDataPtr->xyzEnd[1] = pathBlockPtr->xyzCoordinate[1];
		intpDataPtr->xyzEnd[2] = pathBlockPtr->xyzCoordinate[2];
		// call function to count points
		pointIncre(intpDataPtr);
	
	}

}

//************************************************
//
//************************************************
void v_same(INTP_DATA *intpDataPtr)
{	
	
	
	// calculate length when v is the same
	intpDataPtr->sameVlength = intpDataPtr->totalLength - 2 * intpDataPtr->momtLength;
	intpDataPtr->sameCycleMax = intpDataPtr->sameVlength / (pathBlockPtr->feed * intpDataPtr->cycleTime);

	if (intpDataPtr->halfTotalLength >= intpDataPtr->increCycleMaxLength)
	{
		intpDataPtr->vNew = pathBlockPtr->feed;
		for (intpDataPtr->sameCycle = 1 ; intpDataPtr->sameCycle <= intpDataPtr->sameCycleMax ; intpDataPtr->sameCycle++)
		{
			
			intpDataPtr->deltaS = pathBlockPtr->feed * intpDataPtr->cycleTime;
			intpDataPtr->momtLength = intpDataPtr->momtLength + intpDataPtr->deltaS;

			intpDataPtr->xyzNew[0] = intpDataPtr->xyzOld[0] + intpDataPtr->deltaS * intpDataPtr->unitVector[0];
			intpDataPtr->xyzNew[1] = intpDataPtr->xyzOld[1] + intpDataPtr->deltaS * intpDataPtr->unitVector[1];
			intpDataPtr->xyzNew[2] = intpDataPtr->xyzOld[2] + intpDataPtr->deltaS * intpDataPtr->unitVector[2];

			intpDataPtr->vOld = intpDataPtr->vNew;
	 
		}
		intpData.vState = V_DECRE;
	}
	else 
	{	
		intpData.vState = V_DECRE;
	}
	
}

//************************************************
//
//************************************************
void v_decre(INTP_DATA *intpDataPtr)
{		
		// v insert only once
	    intpDataPtr->insert = true;
		// calculate vInsert
		intpDataPtr->difference = intpDataPtr->totalLength - (2 * intpDataPtr->increCycleLength + intpDataPtr->sameVlength);
		intpDataPtr->vInsert = intpDataPtr->difference / intpDataPtr->decreCycle;
		// calculate points
			
		for (intpDataPtr->decreCycle = 1 ;  (intpDataPtr->vOld - intpDataPtr->cycleVincre) < 0 ; intpDataPtr->decreCycle++)
		{
			intpDataPtr->vNew = intpDataPtr->vOld - intpDataPtr->cycleVincre;
			if (intpDataPtr->vInsert <= intpDataPtr->vOld && intpDataPtr->vInsert >= intpDataPtr->vNew && intpDataPtr->insert == true)
			{	
				intpDataPtr->vNew = intpDataPtr->vInsert;
				intpDataPtr->deltaS = intpDataPtr->vNew * intpDataPtr->cycleTime;
				intpDataPtr->momtLength = intpDataPtr->momtLength + intpDataPtr->deltaS;

				intpDataPtr->xyzNew[0] = intpDataPtr->xyzOld[0] + intpDataPtr->deltaS * intpDataPtr->unitVector[0];
				intpDataPtr->xyzNew[1] = intpDataPtr->xyzOld[1] + intpDataPtr->deltaS * intpDataPtr->unitVector[1];
				intpDataPtr->xyzNew[2] = intpDataPtr->xyzOld[2] + intpDataPtr->deltaS * intpDataPtr->unitVector[2];
				
				intpDataPtr->insert = false;
			}
			else
			{
				intpDataPtr->deltaS = intpDataPtr->vNew * intpDataPtr->cycleTime;
				intpDataPtr->momtLength = intpDataPtr->momtLength + intpDataPtr->deltaS;

				intpDataPtr->xyzNew[0] = intpDataPtr->xyzOld[0] + intpDataPtr->deltaS * intpDataPtr->unitVector[0];
				intpDataPtr->xyzNew[1] = intpDataPtr->xyzOld[1] + intpDataPtr->deltaS * intpDataPtr->unitVector[1];
				intpDataPtr->xyzNew[2] = intpDataPtr->xyzOld[2] + intpDataPtr->deltaS * intpDataPtr->unitVector[2];

				intpDataPtr->vOld = intpDataPtr->vNew;
			}
		}
			intpDataPtr->xyzAnswer[0] = intpDataPtr->xyzEnd[0];
			intpDataPtr->xyzAnswer[1] = intpDataPtr->xyzEnd[1];
			intpDataPtr->xyzAnswer[2] = intpDataPtr->xyzEnd[2];
			
			intpData.vState = END_G01;
}

//************************************************
//
//************************************************
void g04function(INTP_DATA *intpDataPtr)
{

}
//************************************************
//
//************************************************
void m30function(INTP_DATA *intpDataPtr)
{


}
//************************************************
//
//************************************************
void pointIncre(INTP_DATA *intpDataPtr)
{
		// start to end
		intpDataPtr->startToEnd[0] = intpDataPtr->xyzEnd[0] -  intpDataPtr->xyzStart[0];
		intpDataPtr->startToEnd[1] = intpDataPtr->xyzEnd[1] -  intpDataPtr->xyzStart[1];
		intpDataPtr->startToEnd[2] = intpDataPtr->xyzEnd[2] -  intpDataPtr->xyzStart[2];
		
		// calculate total length and initialize momtLength	
		intpDataPtr->totalLength = sqrt(pow(intpDataPtr->startToEnd[0],2) + pow(intpDataPtr->startToEnd[1],2) + pow(intpDataPtr->startToEnd[2],2));
		intpDataPtr->momtLength = 0;
		intpDataPtr->halfTotalLength = intpDataPtr->totalLength / 2;
								 
		// calculate unitVector
		intpDataPtr->unitVector[0] = intpDataPtr->startToEnd[0] / intpDataPtr->totalLength;
		intpDataPtr->unitVector[1] = intpDataPtr->startToEnd[1] / intpDataPtr->totalLength;
		intpDataPtr->unitVector[2] = intpDataPtr->startToEnd[2] / intpDataPtr->totalLength;

		// calculate velocity
		intpDataPtr->cycleVincre = A * intpDataPtr->cycleTime;
		intpDataPtr->vOld = 0;
		intpDataPtr->increCycleMax = pathBlockPtr->feed / intpDataPtr->cycleVincre;
		
		// calculate CycleMaxLength
		intpDataPtr->increCycleMaxLength = 0;
		for (intpDataPtr->increCycle = 1 ; intpDataPtr->increCycle < intpDataPtr->increCycleMax ; intpDataPtr->increCycle++)
		{
			intpDataPtr->increCycleLength = intpDataPtr->cycleVincre * intpDataPtr->cycleTime * intpDataPtr->increCycle;
			intpDataPtr->increCycleMaxLength = intpDataPtr->increCycleMaxLength + intpDataPtr->increCycleLength;
		}
		
		// calculate points
		if (intpDataPtr->halfTotalLength >= intpDataPtr->increCycleMaxLength)
		{
			for (intpDataPtr->increCycle = 1 ; intpDataPtr->increCycle < intpDataPtr->increCycleMax ; intpDataPtr->increCycle++)
			{
				intpDataPtr->vNew = intpDataPtr->vOld + intpDataPtr->cycleVincre;
				intpDataPtr->deltaS = intpDataPtr->vNew * intpDataPtr->cycleTime;
				intpDataPtr->momtLength = intpDataPtr->momtLength + intpDataPtr->deltaS;

				intpDataPtr->xyzNew[0] = intpDataPtr->xyzOld[0] + intpDataPtr->deltaS * intpDataPtr->unitVector[0];
				intpDataPtr->xyzNew[1] = intpDataPtr->xyzOld[1] + intpDataPtr->deltaS * intpDataPtr->unitVector[1];
				intpDataPtr->xyzNew[2] = intpDataPtr->xyzOld[2] + intpDataPtr->deltaS * intpDataPtr->unitVector[2];

				intpDataPtr->vOld = intpDataPtr->vNew;
			}
			intpData.vState = V_SAME;
		}
		else if (intpDataPtr->halfTotalLength < intpDataPtr->increCycleMaxLength && intpDataPtr->totalLength > (intpDataPtr->cycleTime * intpDataPtr->cycleVincre))
		{
			for (intpDataPtr->increCycle = 1 ; intpDataPtr->momtLength < intpDataPtr->halfTotalLength ; intpDataPtr->increCycle++)
			{
				intpDataPtr->vNew = intpDataPtr->vOld + intpDataPtr->cycleVincre;
				intpDataPtr->deltaS = intpDataPtr->vNew * intpDataPtr->cycleTime;
				intpDataPtr->momtLength = intpDataPtr->momtLength + intpDataPtr->deltaS;

				intpDataPtr->xyzNew[0] = intpDataPtr->xyzOld[0] + intpDataPtr->deltaS * intpDataPtr->unitVector[0];
				intpDataPtr->xyzNew[1] = intpDataPtr->xyzOld[1] + intpDataPtr->deltaS * intpDataPtr->unitVector[1];
				intpDataPtr->xyzNew[2] = intpDataPtr->xyzOld[2] + intpDataPtr->deltaS * intpDataPtr->unitVector[2];

				intpDataPtr->vOld = intpDataPtr->vNew;
			}
			intpData.vState = V_SAME;
		}
		else
		{
			intpDataPtr->xyzAnswer[0] = intpDataPtr->xyzEnd[0];
			intpDataPtr->xyzAnswer[1] = intpDataPtr->xyzEnd[1];
			intpDataPtr->xyzAnswer[2] = intpDataPtr->xyzEnd[2];

			intpData.vState = END_G01;
		
		}
		
		
		

		

		
}