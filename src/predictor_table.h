//******************************************************************************
// predictor_table.h
//
//  Created on: March 1, 2014
//      Author: Scott Lawson 
//     Project: Branch Predictor
// Description: Header file for predictor_table.cpp - class interface for 
//                predictor_table class
//******************************************************************************

#ifndef _PREDICTOR_TABLE_H_
#define _PREDICTOR_TABLE_H_

// Header Files

#include "Sat_counter.h"

// Typedefs

typedef unsigned int uint;

// Class Interface

class predictor_table{

  public:
    predictor_table(int ctr_bits, int table_size);    // constructor
    bool get_prediction(uint index);                  // retrieve prediction from counter at index
    void update_prediction(uint index, bool result);  // update counter at index
    ~predictor_table();                               // destructor

  private:
    Sat_counter** table;                              // pointer to table
    int table_len;                                    // store size of table for destructor's use
    uint index_mask;                                  // bit mask for indexing into the table

};

#endif

