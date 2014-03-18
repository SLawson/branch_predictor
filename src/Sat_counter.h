/************************************************************
Class: Saturation counter for branch predictor
By: Brett Dunscomb
Date: 3/1/2014
Description:This file initializes our saturation counters.
It also handles the the increments/decrements 
for the saturation counters.

************************************************************/

#include <stdint.h>

using namespace std;

#ifndef SAT_COUNTER_H
#define SAT_COUNTER_H


class Sat_counter
{
    public:
         Sat_counter(int bits);//Constructor

        bool get_result();//gets the result
        
        //This function keeps limits and increments the count.
        void update_count(bool count_up);
    private:
        //Member variables
        uint8_t value;
        uint8_t limit;
		uint8_t counter_bits;

};

#endif // SAT_COUNTER_H
