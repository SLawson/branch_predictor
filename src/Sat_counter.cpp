/************************************************************
Class: Saturation counter for branch predictor
By: Brett Dunscomb
Date: 3/1/2014
Description:


************************************************************/


#include "Sat_counter.h"
#include <math.h>
#include "tester.h"

//Constructor function to initialize private variables
Sat_counter::Sat_counter(int bits)
{
    value = (pow(2, bits))/2;
	counter_bits = bits; //stores the current bit value
    limit = ((1 << bits) -1);

}

//This shifts to the MSB depending on the limit set by Sat_counter. This will return a bool  
bool Sat_counter::get_result()
{
	return (bool) (value >> (counter_bits - 1));//Shift so MSB is the second bit
}

//This function updates the count it either increments if count_up is true and then
//counts down if count_up is false.
void Sat_counter::update_count(bool count_up)
{
    if(count_up)
    {
        if(value < limit)//Increment the count unless value is larger then the limit
        ++value;//Increment the count
    }
    else
    {
        if(value > 0)//Decrement the count unless it equals zero
        --value;//Decrement the count
    }

	assert(value < limit);
	assert(value >=0);
}

