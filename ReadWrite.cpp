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
#include "Greedy.cpp"
#include "dirent.h"

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
		if(!inputFile.is_open()){
			cout<<"File could not be opened\n";
			return;
		}

		cout<<"Reducing test cases..\n";
		//Read the test cases from file and convert them to bool vector
		vector<vector<bool> > testCases;
		while(!inputFile.eof()){
			string temp;
			getline(inputFile,temp);
			istringstream in(temp);
			bool value;
			vector<bool> row;
			while(in>>value)
				row.push_back(value);
			if(!row.empty())
				testCases.push_back(row);
		}

		//Check if all the test cases are of the same length
		size_t size=testCases[0].size();
		int i=0;
		for(auto &t:testCases){
			if(t.size()!=size){
				cout<<"Error,Test cases are not different length!\n";
				cout<<"case[0].size()="<<size<<" case["<<i<<"].size="<<t.size()<<endl;
				return;
			}
			i++;
		}

		//Do the test reduction using Greedy algorithm
		vector<bool> reducedCases;
		vector<bool> coverage;
		Greedy g;
		size_t caseNum=g.getCount(testCases);
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
			//outputFile<<"#Test Reduction Using Greedy Algorithm\n";
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

			//Declare all the variables to be integers,otherwise there will be
			//float type result
			out<<"\nint ";
			for(size_t i=1;i<testCases.size();i++)
				out<<"t"<<i<<",";
			out<<"t"<<testCases.size()<<";\n\n";	//Last variable

			cout<<"ILP model was saved to \""<<ILPOutputName<<"\"\n";
		}
	}catch(exception& e){
		std::cerr<<e.what()<<endl;
	}
}

void readFile(int argc,char** argv,vector<string> &files){
	  // check command line arguments
	  if (argc <= 1) {
	    return ;
	  }

	  // print contents of directories listed in command line
	  int i=1;
	  while (i < argc) {
	    DIR *dir;
	    struct dirent *ent;

	    // open directory stream
	    dir = opendir (argv[i]);
	    if (dir != NULL) {

	      // print all the files and directories within directory
	      while ((ent = readdir (dir)) != NULL) {
	    	  files.emplace_back(ent->d_name);
	    	  //printf ("%s\n", ent->d_name);
	      }

	      closedir (dir);
	    } else {
	      // could not open directory
	      perror ("");
	      return;
	    }
	    i++;
	  }
	  for(auto f:files)
		  cout<<f<<endl;
}

int main(int argc,char** argv){
	if(argc<2)
		throw std::invalid_argument("Argument number mismatched");
	string path(argv[1]);
	vector<string> files;
	readFile(argc,argv,files);
	for(size_t i=2;i<files.size();i++){
		if(!files[i].empty()){
			cout<<"\n============================================\n";
			cout<<"Processing "<<files[i]<<endl;
			process(path+files[i], "result/"+files[i]+"-greedy", "result/ilp/"+files[i]+"-ilp");
		}
	}

/*
	char input[]="Debug/test_case1.txt";
	char output[]="Debug/result.txt";
	char ilp[]="Debug/ilp.txt";
	process(input,output,ilp);
*/
}
