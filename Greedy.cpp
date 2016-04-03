/*
 * Greedy.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: Lichao
 */
#include <vector>
#include <numeric>
using namespace std;

class Greedy{
public:
	void reduce(vector<vector<bool> > tests,vector<bool> &result);
private:
	size_t findMaxRow(const vector<vector<bool> > &tests,const vector<bool> &selected);
	void addTo(const vector<bool> &src,vector<bool> &trg);
	void clearTo(const vector<bool> &src,vector<bool> &trg);
	void clearTo(const vector<bool> &src,vector<vector<bool> > &trg);

};

size_t Greedy::findMaxRow(const vector<vector<bool> > &tests,const vector<bool> &selected){
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

void Greedy::addTo(const vector<bool> &src,vector<bool> &trg){
	for(size_t i=0;i<src.size();i++)
		trg[i]=trg[i]|src[i];
}

void Greedy::clearTo(const vector<bool> &src,vector<bool> &trg){
	for(size_t i=0;i<src.size();i++)
		trg[i]=trg[i]&(!src[i]);
}

void Greedy::clearTo(const vector<bool> &src,vector<vector<bool> > &trg){
	for(auto &t:trg)
		clearTo(src,t);
}

void Greedy::reduce(vector<vector<bool> > tests,vector<bool> &selected){

	selected.resize(tests.size(),false);

	vector<bool> target(tests[0].size(),false);
	for(auto &t:tests)
		addTo(t,target);

	size_t i=findMaxRow(tests,selected);
	vector<bool> tested(tests[0].size());
	tested=tests[i];
	selected[i]=true;
	clearTo(tested,tests);

	while(tested!=target){
		size_t j=findMaxRow(tests,selected);
		addTo(tests[j],tested);
		selected[j]=true;
		clearTo(tested,tests);
	}
}


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
