#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int main(){
	vector<int> st(9),goal(9);

	for (int i = 0; i < 9; ++i)
		cin>>st[i];

	for (int i = 0; i < 9; ++i)
		cin>>goal[i];

	map<int,int> pos;

	for(int i = 0; i < 9; ++i)
		pos[goal[i]]=i;

	int invcount=0;


	for (int i = 0; i < 9; ++i)
	{
		for (int j = i+1; j < 9; ++j)
		{
			if(pos[st[j]] < pos[st[i]])
				invcount++;
		}
	}

	cout<<"Inversions : "<<invcount<<endl;

	int pos1=pos[0],pos2,mdist;
	for(int i = 0; i < 9; ++i)
		if(st[i]==0)
		{
			pos2=i;
			break;
		}

	mdist = abs(pos1/3 - pos2/3) + abs(pos1%3 - pos2%3);

	cout<<"Manhattan distance between blank :" <<mdist<<endl;

	if((mdist&1)^(invcount&1)){
		cout<<"Hence not reachable \n";
	}
	else
		cout<<"Hence reachable \n";

}