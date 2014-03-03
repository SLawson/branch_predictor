//******************************************************************************
// tester.cpp
//
//  Created on: Mar 1, 2014
//      Author: Rob Gaskell
//******************************************************************************

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#include "../framework/predictor.h"

#define DEBUG

bool Parse_traceline(string traceline, branch_record_c & BR);

int main(int argc, char * argv[]) {

PREDICTOR BranchPredictor;
branch_record_c BranchRecord;


int ProgramCounter;
bool Prediction;
bool Taken;

bool MPrediction = false;

string traceline;
string filename("test/default.ascii");
ifstream tracefile;

	//Read filename argument if present
	if(argc == 2)
		filename.assign(argv[1]);
	else if(argc > 2)
		cout <<"Too many arguments\n";

	//Open File
	tracefile.open(filename.c_str());

	//Read file while file has data
	while(getline(tracefile, traceline)) {

		//Read trace file and display fields
		Taken = Parse_traceline(traceline, BranchRecord);

		//Run Predictor
		Prediction = BranchPredictor.get_prediction(&BranchRecord, NULL);
		BranchPredictor.update_predictor(&BranchRecord, NULL, Taken);

		//Test that the Prediction was correct
		assert(Prediction == MPrediction);

		//Display Prediction Results
		cout <<" Prediction: " <<Prediction <<endl;
		cout <<"      Taken: " <<Taken <<endl;
	}

	cin.get();
	return 0;
}

bool Parse_traceline(string traceline, branch_record_c & BR) {

bool Taken;
int length;
char * temp;

	//Display line read from trace file
	cout <<traceline <<endl;

	//Read Taken character
	if(traceline[0] == '1')
		Taken = true;
	else
		Taken = false;

	//Read PC from trace file
	length = traceline.length();
	temp = new char[length];
	for(int i = 2; i < length; ++i)
		temp[i-2] = traceline[i];

	BR.instruction_addr = strtol(temp, NULL, 16);	//Convert hex to integer

	//Display hex PC address
	cout <<"Branch Addr: " <<temp <<endl;

	delete [] temp;

	return Taken; //Return taken/not taken value
}
