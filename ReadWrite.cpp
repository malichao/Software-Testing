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
using namespace std;


void process(char *inputName,char *outputName){
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
			while(in>>value) row.push_back(value);
		}

		vector<bool> reducedCases;

		Greedy g;
		g.reduce(testCases,reducedCases);

		cout<<"test1\n";
		for(auto r:reducedCases)
			cout<<r<<",";
		cout<<endl;

		if(strlen(outputName)){
			ofstream outputFile(outputName,ofstream::out);
			outputFile.exceptions(ifstream::failbit);
		}
	}catch(exception& e){
		std::cerr<<"Error Occured when reading/writing files!\n\t"<<e.what()<<endl;
	}
}

int main(int argc,char** argv){
	using namespace std;
	try{
		if(3==argc){
				process(argv[1],argv[2]);
			}
		else
			throw std::invalid_argument("Argument number mismatched");
	  }
	  catch (exception& e)
	  {
	    cout << e.what() << '\n';
	  }
}
