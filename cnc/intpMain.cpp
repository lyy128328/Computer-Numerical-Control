#include"StdAfx.h"
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#include <windows.h>






#include "link.h"
#include "intp.h"









int intpMain(INTP_DATA *intpDataPtr)
{
	// local variables
   

   bool      mainLoop;

  

   mainLoop = true;
   while( mainLoop ) // intp main loop
   {
	switch(intpDataPtr->state)
	{
	case INTP_INIT:
		intpInit(intpDataPtr);
		break;
	case INTP_READY:
		intpReady(intpDataPtr);
		break;
	case INTP_RUN:
		intpRun(intpDataPtr);
		break;
	case INTP_ERR:
		intpErr(intpDataPtr);
		break;
	}
   }
	


   return 1;
} // intpMain()



