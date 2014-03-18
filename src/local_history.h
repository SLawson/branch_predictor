//******************************************************************************
// local_history.h
//
//  Created on: March 17, 2014
//      Author: Scott Lawson 
//     Project: Branch Predictor
// Description: Class interface for local_history class
//******************************************************************************

#include <stdint.h>
#include "tester.h"

class local_history {
	
	public:
		local_history(): history(0){};
		uint16_t get_history();
		void update(bool result);
	
	private:
		uint16_t history;
		
};

