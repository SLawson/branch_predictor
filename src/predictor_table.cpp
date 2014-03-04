//******************************************************************************
// predictor_table.cpp
//
//  Created on: March 1, 2014
//      Author: Scott Lawson 
//     Project: Branch Predictor
// Description: Function definitions for predictor_table class
//******************************************************************************



#include "predictor_table.h"



// constructor
predictor_table::predictor_table(int ctr_bits, int table_size){

  // array of counter pointers
  table = new Sat_counter* [table_size];

  // The table is being initialized like this because C++ does not allow parameters
  // to be passed to object constructors when they are in an array. This is also
  // why the predictor_table class has a pointer to a table of sat_counter pointers
  // as its data member. We have to iterate over the pointers and manually construct
  // each one to provide it the ctr_bits variable.
  for (int i=0; i<table_size; ++i){
    table[i] = new Sat_counter(ctr_bits);
  }
  
  table_len = table_size;
  
  index_mask = 0;

  // Assuming table_ size is always an integer power of 2. Generate bit mask by 
  // shifting table_size's single set bit and ORing it with index_mask until 
  // table_size is zero.
  while (table_size > 0){
    index_mask = index_mask | table_size;
    table_size = table_size >> 1;
  }

  return;
}



// retrieve prediction from table
bool predictor_table::get_prediction(uint index){

  // The index into the table must be masked because this class is used to index
  // into the local history, which uses the program counter as an index. The PC
  // can be expected to regularly reference memory addresses much larger than this
  // table, so the high order bits (which bits are considered "high order varies 
  // based on the table size) must be masked off.

  // Aliasing is an expected side effect of this action.

  return table[index & index_mask] -> get_result();
}



// updated the counter at the appropriate index
void predictor_table::update_prediction(uint index, bool result){

  table[index & index_mask] -> update_count(result);

  return;
}



// destructor
predictor_table::~predictor_table(){

  // iterate over the counters, deallocating each one
  for (int i=0; i<table_len; ++i){
    delete table[i];
  }

  // Now delete the table of pointers
  delete [] table;

  return;
}



