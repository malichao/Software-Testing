/******************************************************************************
 Author		: Lichao Ma
 Date  		: Apr 3,2016
 Version	: v0.1
 Description:
	-v0.1	Greedy algorithm for reducing test cases
 *****************************************************************************/

#include <vector>
#include <numeric>
using namespace std;

class Greedy{
public:

double getCoverage(vector<vector<bool> > tests,vector<bool> &coverage){
	if(tests.empty()||tests[0].empty())
		return 0;

	// Init the selected test cases
	coverage.resize(tests[0].size(),false);
	for(auto &t:tests)
		addTo(t,coverage);
	double num=std::accumulate(coverage.begin(),coverage.end(),0);
	return num/coverage.size();
}


// Greedy algorithm to reduce redundant test cases,the reduced cases are
// stored in vector 'selected' .
void reduce(vector<vector<bool> > tests,vector<bool> &selected){
	// Init the selected test cases
	selected.resize(tests.size(),false);

	// Calculate the coverage of the original test cases
	vector<bool> target(tests[0].size(),false);
	for(auto &t:tests)
		addTo(t,target);

	// Init the selected with the maximum coverage first
	size_t i=findMaxRow(tests,selected);
	vector<bool> tested(tests[0].size());
	tested=tests[i];
	selected[i]=true;
	clearTo(tested,tests);

	// Iteratively select the test cases with the maximum additional coverage
	// until the selected test cases cover all original test cases
	while(tested!=target){
		size_t j=findMaxRow(tests,selected);
		addTo(tests[j],tested);
		selected[j]=true;
		clearTo(tested,tests);
	}
}


private:

size_t findMaxRow(	const vector<vector<bool> > &tests,
					const vector<bool> &selected){
	size_t row=0;
	size_t maxNum=0;
	for(size_t i=0;i<tests.size();i++){
		if(!selected[i]){
			size_t num=accumulate(tests[i].begin(),tests[i].end(),true);
			if(num>maxNum){
				row=i;
				maxNum=num;
			}
		}
	}
	return row;
}

void addTo(const vector<bool> &src,vector<bool> &trg){
	for(size_t i=0;i<src.size();i++)
		trg[i]=trg[i]|src[i];
}

void clearTo(const vector<bool> &src,vector<bool> &trg){
	for(size_t i=0;i<src.size();i++)
		trg[i]=trg[i]&(!src[i]);
}

void clearTo(const vector<bool> &src,vector<vector<bool> > &trg){
	for(auto &t:trg)
		clearTo(src,t);
}

};



/*
#include <iostream>
int main(){
	vector<vector<bool> > testCases={
			{ true,  false, true, true,  false, false },
			{ false, true,  true, false, true,  true },
			{ false, false, true, true,  true,  true },
			{ false, false, true, false, true,  false },};

	vector<bool> reducedCases;

	cout<<"Greedy self test\n";

	Greedy g;
	g.reduce(testCases,reducedCases);
	for(auto r:reducedCases)
		cout<<r<<",";
}
*/
