/************************************************************
Class: Saturation counter for branch predictor
By: Brett Dunscomb
Date: 3/1/2014
Description:


************************************************************/


#include "Sat_counter.h"

//Constructor function to initialize private variables
Sat_counter::Sat_counter(int bits)
{
    value = 0;
    if(bits == 2)
    limit = 3;
    else
    limit = 7;
}

//This shifts to the MSB depending on the limit set by Sat_counter. This will return a bool  
bool Sat_counter::get_result()
{
    bool MSB_value;
    if(limit == 3)
	MSB_value = (value >> 1);//Shift so MSB is the second bit
    if(limit == 7)
 	MSB_value = (value >> 2);//Shift so MSB is the third bit
    
    return MSB_value;
}

//This function updates the count it either increments if count_up is true and then
//counts down if count_up is false.
void Sat_counter::update_count(bool count_up)
{
    if(count_up)
    {
        if(value < limit)//Increment the count unless value is larger then the limit
        value++;//Increment the count
    }
    else
    {
        if(value != 0)//Decrement the count unless it equals zero
        value--;//Decrement the count
    }
}

