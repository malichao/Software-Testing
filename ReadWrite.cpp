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

void process(string inputName,string outputName,string ILPOutputName){
	using namespace std;
	//Reading the input
	try{
		cout<<"Opening \""<<inputName<<"\"\n";
		ifstream inputFile(inputName,std::ifstream::in);

		//Must set these bits to enable exception
		//set the badbit for IO R/W error,not failbit!
		//badbit:	Read/writing error on i/o operation
		//failbit:	Logical error on i/o operation
		inputFile.exceptions(ifstream::badbit);

		cout<<"Reducing test cases..\n";
		//Read the test cases from file and convert them to bool vector
		vector<vector<bool> > testCases;
		while(!inputFile.eof()){
			string temp;
			getline(inputFile,temp);
			istringstream in(temp);
			int size=temp.length();
			bool value;
			vector<bool> row;
			int count=0;
			while(in>>value){
				row.push_back(value);
				count++;
			}
			if(!row.empty())
				testCases.push_back(row);
		}
		vector<vector<bool> > testCasesCopy(testCases);
		//Do the test reduction using Greedy algorithm
		vector<bool> reducedCases;
		vector<bool> coverage;
		Greedy g;
		size_t caseNum=g.getCount(testCasesCopy);
		cout<<"\nTest cases number = "<<caseNum<<endl;
		cout<<"Code Statement number = "<<testCases[0].size()<<endl;
		cout<<"Coverage = "<<g.getCoverage(testCases,coverage)*100<<"%\n";
		g.reduce(testCases,reducedCases);

		//Print the result
		cout<<"Test Coverage Vector:\n";
		for(auto c:coverage)	cout<<c<<" ";

		cout<<"\n\nReduction result:\n";
		cout<<"Cases reduced = "<<caseNum-g.getCount(reducedCases)<<endl;
		for(auto r:reducedCases)	cout<<r<<" ";
		cout<<endl;

		//Save the result into the file
		if(outputName.length()){
			cout<<"\nOpening \""<<outputName<<"\"\n";
			ofstream outputFile(outputName,ofstream::out);
			outputFile.exceptions(ifstream::badbit);
			outputFile<<"#Test Reduction Using Greedy Algorithm\n";
			for(auto r:reducedCases)
				outputFile<<r<<endl;
			cout<<"Result was saved to \""<<outputName<<"\"\n";
		}

		//Convert the test cases to ILP model and then use lp_solve program to
		//solve the ILP.
		if(ILPOutputName.length()){
			cout<<"Opening \""<<ILPOutputName<<"\"\n";
			ofstream out(ILPOutputName,ofstream::out);
			out.exceptions(ifstream::badbit);

			//State the objective,e.g., min t1 + t2 + t3 + t4;
			out<<"min: t1";
			for(size_t i=1;i<testCases.size();i++)
				out<<" + t"<<i+1;
			out<<";\n";

			//State the constraints,e.g.,1*x1 + 0*x2 + 0*x3 + 0*x4 >=1;
			for(size_t j=0;j<testCases[0].size();j++){
				if(testCases[0][j])
					out<<"1*t1";
				else
					out<<"0*t1";
				for(size_t i=1;i<testCases.size();i++){
					if(testCases[i][j])
						out<<" + 1*t"<<i+1;
					else
						out<<" + 0*t"<<i+1;
				}
				if(coverage[j])
					out<<" >=1;\n";
				else
					out<<" >=0;\n";
			}
			cout<<"ILP model was saved to \""<<ILPOutputName<<"\"\n";
		}
	}catch(exception& e){
		std::cerr<<e.what()<<endl;
	}
}

int main(int argc,char** argv){
/*
	if(2==argc){
		process(argv[1], string(argv[1])+"-greedy", string(argv[1])+"-ilp");
	}
	else if (4 == argc)
		process(argv[1], argv[2], argv[3]);
	else
		throw std::invalid_argument("Argument number mismatched");
*/

	char input[]="Debug/jstorm-masterMatrx";
	char output[]="Debug/jstorm-masterMatrx-greedy";
	char ilp[]="Debug/jstorm-masterMatrx-ilp";
	cout<<input<<endl;
	process(input,output,ilp);

}
