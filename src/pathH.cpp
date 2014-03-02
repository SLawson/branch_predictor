//******************************************************************************
// Path History
//
//  Created on: Mar 1, 2014
//      Author: Jordan Fluth
//******************************************************************************

#include <stdint.h>

class path_history {
	public:
		path_history();
		~path_history();
		uint16_t get_history();
		void update(bool result);
		void revert_update();
	
	private:
		uint16_t history;
		uint16_t old_msb;
		
};

//Constructor function used to initial private variables
path_history::path_history() {
	
	old_msb = 0;
	history = 0;
}

//Returns the twelve bits of path history
uint16_t path_history::get_history() {

	return history;
}

//Speculatively update the path history
void path_history::update(bool result) {
	//there is speculative and actual... need to account to the case 
	//that speculative is wrong...
	
	old_msb = (history & 0x800);
	history = ((history << 0x1) | result);
	history = (history & 0x0FFF);
	
}

//If the speculative update was wrong we must revert
void path_history::revert_update() {

	history  = ((history >> 0x1) + old_msb);
}

//Deconstructor function
path_history::~path_history() {	}

