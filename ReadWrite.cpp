/******************************************************************************
 Author		: Lichao Ma
 Date  		: Apr 15,2016
 Version	: v0.1
 Description:
	-v0.1	A IO function for reading test cases and writing results.
 *****************************************************************************/
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include "Greedy.cpp"

void process(char *inputName,char *outputName,char *ILPOutputName){
	using namespace std;
	//Reading the input
	try{
		ifstream inputFile(inputName,std::ifstream::in);

		//Must set these bits to enable exception
		inputFile.exceptions(ifstream::failbit);

		vector<vector<bool> > testCases;
		while(inputFile.good()){
			string temp;
			getline(inputFile,temp);
			istringstream in(temp);
			bool value;
			vector<bool> row;
			while(in>>value)
				row.push_back(value);
			testCases.push_back(row);
		}

		vector<bool> reducedCases;

		Greedy g;
		g.reduce(testCases,reducedCases);

		cout<<"Test reduction completed.\n";
		for(auto r:reducedCases)
			cout<<r<<",";
		cout<<endl;

		if(strlen(outputName)){
			ofstream outputFile(outputName,ofstream::out);
			outputFile.exceptions(ifstream::failbit);

			for(auto r:reducedCases)
				outputFile<<r<<endl;
			cout<<"Result was saved to \""<<outputName<<"\"\n";
		}
	}catch(exception& e){
		std::cerr<<"Error Occurred when reading/writing files!\n\t"<<e.what()<<endl;
	}
}

int main(int argc,char** argv){
	if (4 == argc)
		process(argv[1], argv[2], argv[3]);
	else
		throw std::invalid_argument("Argument number mismatched");
}
