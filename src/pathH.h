#include <stdint.h>
#include "tester.h"

class path_history {
	
	public:
		path_history();
		uint16_t get_history();
		void update(bool result);
	
	private:
		uint16_t history;
		
};
