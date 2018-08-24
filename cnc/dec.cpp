#include"StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>



#include <windows.h>
#include "dec.h"
#include "link.h" 
#include "intp.h"

extern PATH_BLOCK        pathBlock; //data for intp
extern PATH_BLOCK        *pathBlockPtr;

bool              pathBlockValid = false;

//************************************************
//
//************************************************

int decMain(DECODER_DATA *dataPtr)
{
	

	// local variables


   bool      mainLoop;

   // design of a state machine
   decoderData.state = INIT;
// init decoderDataPtr
   decoderDataPtr = &decoderData;


   mainLoop = true;
   while( mainLoop ) // decoder main loop
   {
     //   switch (decoderData.state)  // for example
     switch (decoderDataPtr->state)
     {
     case INIT:
//	   init();  // for example
	   init(decoderDataPtr);
	   break;
     case READY:  // GET STRING FROM KEY BOARD
	   ready(decoderDataPtr);
	   break;
     case RUN:
	   run(decoderDataPtr);
	   break;
     case END_LINE:
	   endOfLine(decoderDataPtr);
	   break;
     case END_M30:
	   endM30(decoderDataPtr);
	   mainLoop = false;
	   break;
     case ERR:
	   err(decoderDataPtr);
	   break;

     }  //switch()

	 // change loop to false to end while if necessary

   } // while()
   system("pause");

   return 1;
} // main()



//************************************************
//
//************************************************
void init(DECODER_DATA *dataPtr)
{
	int   i;

    char    *bytePtr = (char *)dataPtr;

	// delete all memory 
	for (i=0; i < sizeof(DECODER_DATA); i++)
	{
	  *bytePtr = 0; // ++ to next byte
	}
/*
	for (i=0; i < 80; i++)
      dataPtr->buffer[i] = 0;	
*/
	dataPtr->asciiPtr = dataPtr->buffer;

	dataPtr->state = READY; // unconditional STATE TRANSITION to next state

	return;

} // init()


//************************************************
//
//************************************************
void ready(DECODER_DATA *dataPtr)
{
	

	// actions
	if (dataPtr->fileOk == true)
	{
		if(dataPtr->filePtr == NULL)
		{
			dataPtr->filePtr = fopen(decoderDataPtr->fileName ,"r");
		}
			if(dataPtr->filePtr == NULL)
			{
				err(decoderDataPtr);
			}
			else
			{	
				decoderDataPtr->cyclestart = false;
				fgets(dataPtr->buffer,sizeof(dataPtr->buffer),dataPtr->filePtr);
				intpDataPtr->vState = V_INCRE;
				dataPtr->state = RUN;
			}
	
	}
    

//    Sleep(2000);

	return;


} // ready()


//************************************************
//
//************************************************
void run(DECODER_DATA *dataPtr)
{
	int   count;
    bool  lineLoop;

	// pass all spaces for string in bufefr[]
	// before: in buffer: "N 100   G01 G  91 X 20.3 Y-20.92 F10  "
	// after pass space: "N100G01G91X20.3Y-20.92F10"


//  using function
	dataPtr->asciiPtr = dataPtr->buffer;
    count = passSpace(dataPtr->buffer);

	dataPtr->asciiPtr = dataPtr->buffer;  // REWIND asciiPtr

	lineLoop = true;
	while(lineLoop)
	{
	  switch(*dataPtr->asciiPtr)
	  {
	  case 'N':
		  dataPtr->nInput = true;
		  nFunction(dataPtr);
		  break;
	  case 'G':
		  gFunction(dataPtr);
		  break;
	  case 'F':
		  dataPtr->fInput = true;
		  fFunction(dataPtr);
		  break;
	  case 'X':
	  case 'Y':
	  case 'Z':
		  xyzFunction(dataPtr);
		  break;
	  case 'M':
		  if (mFunction(dataPtr) == 30)
		  {
		     lineLoop = false;
			 dataPtr->state = END_M30;
		  }
		  else
			 dataPtr->state = ERR;
		  break;
	  case '\0':
	      dataPtr->state = END_LINE;
		  lineLoop = false;
		  break;	
	  default:
		  dataPtr->state = ERR;
		  lineLoop = false;
		  break;
	  }


	} // while(lineLoop)

	return;

} // run()


//************************************************
//
//************************************************
void endOfLine(DECODER_DATA *dataPtr)
{
  if (pathBlockValid == false)
  {
    // output TO FILE DECODED DATA
   if (dataPtr->filePtr == NULL)
   {// open file for write
     dataPtr->filePtr = fopen("decData.txt","r");
   }

   //!!LEI save all decoded data to file
 

   if (dataPtr->nInput)
   {
	   printf( "block number  %d\n ",dataPtr->blockNr );
	   pathBlockPtr->blockNumber = dataPtr->blockNr;
       dataPtr->nInput = false;
   }
   if (dataPtr->g01Input)
   {
      printf( "linear motion\n",dataPtr->blockCommand );
	  pathBlockPtr->blockCommand = G01;
       dataPtr->g01Input = false;
   }
   if (dataPtr->g91g90input)
   {
		if(dataPtr-> rel = true)
		{
		printf("absolute coordinate input\n",dataPtr->rel );
		pathBlockPtr->rel =  dataPtr->rel;
		}
		else
		{
		printf( "relative coordinate input\n",dataPtr->rel );
		pathBlockPtr->rel =  dataPtr->rel;
		}
	   dataPtr->g91g90input = false;
	   dataPtr->rel = false;
   }
   if (dataPtr->xyzInput[0])
   {
	   printf( "x coordinate  %f\n ",dataPtr->xyzCoordinate[0] );
	   pathBlockPtr->xyzCoordinate[0] = dataPtr->xyzCoordinate[0];
       dataPtr->xyzInput[0] = false;
   }
    if (dataPtr->xyzInput[1])
   {
	   printf( "Y coordinate  %f\n ",dataPtr->xyzCoordinate[1] );
	   pathBlockPtr->xyzCoordinate[1] = dataPtr->xyzCoordinate[1];
       dataPtr->xyzInput[1] = false;
   }
	 if (dataPtr->xyzInput[2])
   {
	   printf( "z coordinate  %f\n ",dataPtr->xyzCoordinate[2] );
	   pathBlockPtr->xyzCoordinate[2] = dataPtr->xyzCoordinate[2];
       dataPtr->xyzInput[2] = false;
   }
    if (dataPtr->fInput)
   {
	   printf( "feed %fmm/s\n",dataPtr->feed );
	   pathBlockPtr->feed = dataPtr->feed;
       dataPtr->fInput = false;
   }
	pathBlockValid = true;

  }
  else
  {
   dataPtr->state = READY;
   
  }
   

   // !!LEI change decoder state and ready for next line

   return;

} // endOfLine()

//************************************************
//
//************************************************
void endM30(DECODER_DATA *dataPtr)
{
	

// output TO FILE DECODED DATA
   if (dataPtr->filePtr!= NULL)
   {// open file for write
     fclose(dataPtr->filePtr);
   }

   printf("end of NC input decoding!\n ");


	return;

} // endM30()






//************************************************
//
//************************************************
void err(DECODER_DATA *dataPtr)
{
	

    printf("input error! do again! \n");
	dataPtr->state = READY; 

	return;

} // err()




//************************************************
//
//************************************************
void nFunction(DECODER_DATA *dataPtr)
{
	

	dataPtr->asciiPtr++;  // N123

	dataPtr->blockNr = atoi(dataPtr->asciiPtr);  //DECODING
	  // STRING"123"converts to integer 123
	// pass digit
	
	for (;*dataPtr->asciiPtr >= '0' && *dataPtr->asciiPtr <= '9';)
	{
	   dataPtr->asciiPtr++;
	}
	return;

} // nFunction()



//************************************************
//
//************************************************
void xyzFunction(DECODER_DATA *dataPtr)
{

    
	if (*dataPtr->asciiPtr == 'X')  // example X12.345Y-10.2
	{	
		dataPtr->xyzInput[0] = true;
	    dataPtr->asciiPtr++;  // 12.345Y-10.2
		dataPtr->xyzCoordinate[0] = atof(dataPtr->asciiPtr);  //DECODING
	}
	if ( *dataPtr->asciiPtr == '+' || *dataPtr->asciiPtr == '-' )
	{
	   dataPtr->asciiPtr++;
	}
	
	for (;*dataPtr->asciiPtr >= '0' && *dataPtr->asciiPtr <= '9';)
	{
	   dataPtr->asciiPtr++;
	}
	if ( *dataPtr->asciiPtr == '.')
	{
	   dataPtr->asciiPtr++;
	}
	
	for (;*dataPtr->asciiPtr >= '0' && *dataPtr->asciiPtr <= '9';)
	{
	   dataPtr->asciiPtr++;
	}
                   //asciiPtr points at string of Y-10.2 
	return;

} // xyzFunction()



//************************************************
//
//************************************************
void fFunction(DECODER_DATA *dataPtr)
{

    
	dataPtr->fInput = true;
	dataPtr->asciiPtr++;  // G01  ??
	dataPtr->feed = atof(dataPtr->asciiPtr);  //DECODING


	
	for (;*dataPtr->asciiPtr >= '0' && *dataPtr->asciiPtr <= '9';)
	{
	   dataPtr->asciiPtr++;
	}
	if ( *dataPtr->asciiPtr == '.')
	{
	   dataPtr->asciiPtr++;
	}
	
	for (;*dataPtr->asciiPtr >= '0' && *dataPtr->asciiPtr <= '9';)
	{
	   dataPtr->asciiPtr++;
	}
	
//!!LEI pass real format followig the F code


	return;

} // fFunction()



//************************************************
//
//************************************************
void gFunction(DECODER_DATA *dataPtr)
{
	int   i;

	dataPtr->asciiPtr++;  // G01  ??
	i = atoi(dataPtr->asciiPtr);  //DECODING

	for (;*dataPtr->asciiPtr >= '0' && *dataPtr->asciiPtr <= '9';)
	{
	   dataPtr->asciiPtr++;
	}

	//!! LEI pass digit following the G code
	switch(i)
	{
	case 0:
	case 1:
		dataPtr->g01Input = true;
		dataPtr->blockCommand = i;
		break;
	case 90:
		dataPtr->g91g90input = true;
		break;
	case 91:
		dataPtr->g91g90input = true;
		dataPtr->rel = true;
		break;

	
	}


	return;

} // gFunction()


//************************************************
//
//************************************************
int mFunction(DECODER_DATA *dataPtr)
{
	int   i;

	dataPtr->asciiPtr++;  // N123
	i = atoi(dataPtr->asciiPtr);  //DECODING 30
    if (i == 30) // M30

	   return i;
	else return -1;

} // mFunction()


//************************************************
// input a char array name for char processing
//************************************************
/*
int  passSpace(char charArray[])

{
	char *bufferPtr = charArray;
    int  counter = 0;

	for (int i = 0; charArray[i] != '\0'; i++ )
	{
		while (charArray[i] == ' ')
		{
			i++;
		    counter++;
		}
		*bufferPtr = charArray[i];
		bufferPtr++;
		// i++;
	}
	*bufferPtr = '\0';
  
	return counter;

} // passSpace()
*/

int  passSpace(char *charPtr)
{
	char *bufferPtr = charPtr;
    int  counter = 0;

	for (int i = 0; *charPtr != '\0'; i++ )
	{
		while (*charPtr == ' ')
		{
			charPtr++;
		    counter++;
		}
		*bufferPtr = *charPtr;
		bufferPtr++;
		charPtr++;
	}
	*bufferPtr = '\0';
  
	return counter;

} // passSpace()

/*
abs() for integer
fabs() for real number

*/