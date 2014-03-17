//******************************************************************************
// Path History
//
//  Created on: Mar 1, 2014
//      Author: Jordan Fluth
//******************************************************************************

#include "pathH.h"
#include "tester.h"

//Constructor function used to initial private variables
path_history::path_history() {
	
	history = 0;
}

//Returns the twelve bits of path history
uint16_t path_history::get_history() {
	#ifdef DEBUG
		printf("\tThe path history is: %x\n", history);
	#endif
	
	return history;
}

//Speculatively update the path history
void path_history::update(bool result) {
	
	history = ((history << 0x1) | result);
	history = (history & 0x0FFF);
	
	#ifdef DEBUG
		printf("\tThe new path history is: %x\n", history);
	#endif
}
