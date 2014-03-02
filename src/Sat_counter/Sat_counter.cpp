/************************************************************
Class: Saturation counter for branch predictor
By: Brett Dunscomb
Date: 3/1/2014
Description:


************************************************************/


#include "Sat_counter.h"

//Constructor function to initialize private variables
Sat_counter::Sat_counter()
{
    value = 0;
    limit = 0;
}

//Destructor function to clean up private variables;
Sat_counter::~Sat_counter()
{
}

bool Sat_counter::get_result()
{
    //Not sure what to put in here
    //My guess is fetch the result from update_prediction

}

//This is the Saturation counter bits represents the table size
void Sat_counter::Sat_counter(int bits)
{
    //Not sure what to put in here
    //My guess is just to create the data table depending on how many bits


}

//This function updates the count it either increments if count_up is true and then
//counts down if count_up is false.
void Sat_counter::update_count(bool count_up)
{
    /* question The 21264 load hit/miss predictor is the most-significant bit of a 4 bit counter that tracks
    the hit/miss behavior of recent load. The saturating counter decrements by two on cycles when there is a load miss,
    otherwise it increments by one when there is a hit. page 6 second paragraph*/

    if(count_up)
    {
        if(value <= limit)//Increment the count unless value is larger then the limit
        value++;//Increment the count
    }
    else
    {
        if(value <= limit || value != 0)//Decrement the count unless value is larger then the limit
        value--;//Decrement the count
    }
}

