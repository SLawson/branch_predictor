#include <stdint.h>

class path_history {
	
	public:
		path_history();
		uint16_t get_history();
		void update(bool result);
		void revert_update();
	
	private:
		uint16_t history;
		uint16_t old_msb;
		
};
