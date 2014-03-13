//******************************************************************************
// tester.cpp
//
//  Created on: Mar 1, 2014
//      Author: Rob Gaskell
//******************************************************************************

#include "tester.h"

#include "../framework/predictor.h"

bool Parse_traceline(string traceline, branch_record_c & BR, bool & MPrediction);

int main(int argc, char * argv[]) {

PREDICTOR BranchPredictor;
branch_record_c BranchRecord;

int tracecount = 0;

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

		if(traceline[0] == '#')
			cout <<traceline <<endl;
		else {
			++tracecount;	//Increment traceline count

			//Read trace file and display fields
			Taken = Parse_traceline(traceline, BranchRecord, MPrediction);

			//Display Branch Details
			printf("\nPC: %x\t Trace line #: %d\n", BranchRecord.instruction_addr, tracecount);
			printf("\tConditional: %x\n", BranchRecord.is_conditional);
			printf("\t   Sub Call: %x\n", BranchRecord.is_call);
			printf("\t Sub Return: %x\n", BranchRecord.is_return);
			printf("\t   Indirect: %x\n", BranchRecord.is_indirect);

			//Run Predictor
			Prediction = BranchPredictor.get_prediction(&BranchRecord, NULL);

			//Test that the Prediction matches expected value
			assert(Prediction == MPrediction);

			BranchPredictor.update_predictor(&BranchRecord, NULL, Taken);

			//Display predictor results
			printf("\n\t      Taken: %d\n", Taken);
			printf("\t Prediction: %d\n", Prediction);
			printf("\tMPrediction: %d\n", MPrediction);
		}
	}
	cout <<"Tester complete- press enter";
	cin.get();
	return 0;
}

bool Parse_traceline(string traceline, branch_record_c & BR, bool & MPrediction) {

bool Taken;
int length;

uint tempMPrediction = 0;
uint tempTaken = 0;
uint tempCond = 0;
uint tempCall = 0;
uint tempReturn = 0;
uint tempIndirect = 0;

	sscanf(traceline.c_str(),"%x%x%x%x%x%x%x%x", &tempMPrediction, &tempTaken, &BR.instruction_addr, &BR.branch_target, &tempCond, &tempCall, &tempReturn, &tempIndirect);

	BR.is_conditional = tempCond; 	//Convert hex to integer
	BR.is_call = tempCall; 			//Convert hex to integer
	BR.is_return = tempReturn; 		//Convert hex to integer
	BR.is_indirect = tempIndirect;	//Convert hex to integer
	MPrediction = tempMPrediction; 	//Convert hex to integer
	Taken = tempTaken;

	return Taken; //Return taken/not taken value
}
