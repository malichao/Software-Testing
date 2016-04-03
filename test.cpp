/*
 * test.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: Lichao
 */


#include <iostream>
#include "Greedy.cpp"
using namespace std;

int main(){
	vector<vector<bool> > testCases={
			{ true,  false, true, true,  false, false },
			{ false, true,  true, false, true,  true },
			{ false, false, true, true,  true,  true },
			{ false, false, true, false, true,  false },};

	vector<bool> reducedCases;

	Greedy g;
	g.reduce(testCases,reducedCases);
	for(auto r:reducedCases)
		cout<<r<<",";
}


