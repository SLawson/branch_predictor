//******************************************************************************
// Path History
//
//  Created on: Mar 1, 2014
//      Author: Jordan Fluth
//******************************************************************************

#include "pathH.h"


//Constructor function used to initial private variables
path_history::path_history() {
	
	old_msb = 0;
	history = 0;
}

//Returns the twelve bits of path history
uint16_t path_history::get_history() {
	#ifdef DEBUG
		cout << "The path history is: " << history << '\n';
	#endif
	
	return history;
}

//Speculatively update the path history
void path_history::update(bool result) {
	
	old_msb = (history & 0x800);
	history = ((history << 0x1) | result);
	history = (history & 0x0FFF);
	
	#ifdef DEBUG
		cout << "The new path history is: " << history << '\n';
	#endif
}

//If the speculative update was wrong we must revert
void path_history::revert_update() {

	history  = ((history >> 0x1) + old_msb);
}


