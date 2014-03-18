//******************************************************************************
// predictor.cc
//
//  Created on: March 1, 2014
//      Author: Scott Lawson 
//     Project: Branch Predictor
// Description: Function definitions for PREDICTOR class
//******************************************************************************



#include "predictor.h"
#define DEBUG


// Retrieve a prediction from tables if branch is conditional
bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os)
{
  bool prediction = false;
	
  if (!(br->is_conditional) || br->is_call || br-> is_return)
    prediction = true;

  else
    prediction = make_decision(br);

  return prediction;   // true for taken, false for not taken
}



// This function performs the tournament algorithm
bool PREDICTOR::make_decision(const branch_record_c* br){

  bool prediction = false;

  // Get path history 
  uint p_history = path_h.get_history();

  // Use choice predictor to decide whether to use the global or local history prediction
  if (choice.get_prediction(p_history)){ // True is defined to mean "use global"
    prediction = global.get_prediction(p_history);
  }

  else{ // False means "use local"

    #ifdef LHISTORY
    prediction = local.get_prediction(local_h[br->instruction_addr & 0x3FF].get_history());
    #else
    prediction = local.get_prediction(br->instruction_addr);
    #endif // ifndef LHISTORY
    
  }

  return prediction;
}



// Update the predictor after a prediction has been made
void PREDICTOR::update_predictor(const branch_record_c* br, const op_state_c* os, bool taken)
{

  // Retrieve the original path history
  uint p_history = path_h.get_history();

  // Retrieve the most recent prediction results

  #ifdef LHISTORY
  uint16_t local_index = local_h[br->instruction_addr & 0x3FF].get_history();
  bool local_last = local.get_prediction(local_index);
  #else
  bool local_last = local.get_prediction(br->instruction_addr);
  #endif // ifdef LHISTORY

  bool global_last = global.get_prediction(p_history);
  
  // Update choice predictor if the predictions were not the same
  if (local_last != global_last){
    if (local_last == taken){
      // False from the choice predictor is defined to mean "use local prediction", so we
      // drive the saturated counter toward zero when the local is correct but global is not
      choice.update_prediction(p_history, false);
    }
    else{
      // True from the choice predictor is defined to mean "use global prediction" so we
      // drive the saturated counter upwards towards its limit when the global is correct
      // but the local is not
      choice.update_prediction(p_history, true);
    }
  }

  // Update local and global prediction tables

  #ifdef LHISTORY
  local.update_prediction(local_index, taken);
  local_h[br->instruction_addr & 0x3FF].update(taken);
  #else
  local.update_prediction(br->instruction_addr, taken);
  #endif // ifdef LHISTORY

  global.update_prediction(path_h.get_history(), taken);

  // Update path history
  path_h.update(taken);

  return;
}

