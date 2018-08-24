// LINK.CPP
#include"StdAfx.h"
#include "link.h" 
#include"intp.h"
// create memory for link between dec and intp

PATH_BLOCK        pathBlock; //data for intp
PATH_BLOCK        *pathBlockPtr;



//************************************************
//
//************************************************

int initLink (void)
{
	pathBlockPtr = &pathBlock;

	return 1;

}