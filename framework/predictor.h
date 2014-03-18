//******************************************************************************
// predictor.h
//
//  Created on: March 1, 2014
//      Author: Scott Lawson 
//     Project: Branch Predictor
// Description: Header file for predictor.cc - contains PREDICTOR class
//                interface
//******************************************************************************

#ifndef PREDICTOR_H_SEEN
#define PREDICTOR_H_SEEN

#include <cstddef>
#include <cstring>
#include <inttypes.h>
#include <vector>
#include "op_state.h"   // defines op_state_c (architectural state) class 
#include "tread.h"      // defines branch_record_c class

// Team-generated header files
#include "../src/predictor_table.h" // defines predictor_table class
#include "../src/pathH.h"         // defines path_history class

// Macros
#define LOCAL_CTR_BITS 3
#define LOCAL_TBL_SIZE 1024
#define GLOBAL_CTR_BITS 2
#define GLOBAL_TBL_SIZE 4096
#define CHOICE_CTR_BITS 2
#define CHOICE_TBL_SIZE 4096

/* Uncomment this macro to build with local history table */
// #define LHISTORY

// Include local history information if compiling that version
#ifdef LHISTORY
#include "../src/local_history.h"
#define LOCAL_HIST_SIZE 1024
#endif

class PREDICTOR
{
  public:
    // predictor class uses initialization list for member objects that require arguments
    // for their constructors
    PREDICTOR(): local(LOCAL_CTR_BITS, LOCAL_TBL_SIZE),
                 global(GLOBAL_CTR_BITS, GLOBAL_TBL_SIZE),
                 choice(CHOICE_CTR_BITS, CHOICE_TBL_SIZE) {};
    bool get_prediction(const branch_record_c* br, const op_state_c* os);
    void update_predictor(const branch_record_c* br, const op_state_c* os, bool taken);

  private:
    bool make_decision(const branch_record_c* br);
    predictor_table local;
    predictor_table global;
    predictor_table choice;
    path_history path_h;

    #ifdef LHISTORY
    local_history local_h[LOCAL_HIST_SIZE];
    #endif

};

#endif // PREDICTOR_H_SEEN

