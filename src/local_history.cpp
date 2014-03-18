//******************************************************************************
// local_history.cpp
//
//  Created on: March 17, 2014
//      Author: Scott Lawson 
//     Project: Branch Predictor
// Description: Function definitions for local_history class
//******************************************************************************

#include "local_history.h"

//Returns the twelve bits of path history
uint16_t local_history::get_history() {
	#ifdef DEBUG
		printf("\tThe local history is: %x\n", history);
	#endif
	
	return history;
}

//Speculatively update the path history
void local_history::update(bool result) {
	
	history = ((history << 0x1) | result);
	history = (history & 0x03FF);
	
	#ifdef DEBUG
		printf("\tThe new local history is: %x\n", history);
	#endif
}

