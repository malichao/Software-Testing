/*
 * test.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: Lichao
 */


#include <iostream>
#include "Greedy.cpp"
using namespace std;

void test1(){
	vector<vector<bool> > testCases={
			{ 1, 0, 1, 1, 0, 0 },
			{ 0, 1, 1, 0, 1, 1 },
			{ 0, 0, 1, 1, 1, 1 },
			{ 0, 0, 1, 0, 1, 0 }, };

	vector<bool> reducedCases;

	Greedy g;
	g.reduce(testCases,reducedCases);

	cout<<"test1\n";
	for(auto r:reducedCases)
		cout<<r<<",";
	cout<<endl;
}

void test2(){
	vector<vector<bool> > testCases={
			{ 1, 0, 1, 0, 0, 0 },
			{ 0, 1, 1, 0, 1, 1 },
			{ 0, 0, 1, 1, 1, 1 },
			{ 0, 0, 1, 0, 1, 0 }, };

	vector<bool> reducedCases;

	Greedy g;
	g.reduce(testCases,reducedCases);

	cout<<"test2\n";
	for(auto r:reducedCases)
		cout<<r<<",";
	cout<<endl;
}


int main(){
	test1();
	test2();
}


