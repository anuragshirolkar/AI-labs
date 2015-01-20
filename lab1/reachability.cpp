#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
struct node{
	int state[3][3];

	bool is_reachable(node);
};

bool node::is_reachable(node b){
	vector<int> st(9),goal(9);
	for (int i = 0; i < 9; ++i){
		st[i]=state[i/3][i%3];
		goal[i]=b.state[i/3][i%3];
	}

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

	int pos1=pos[0],pos2,mdist;
	for(int i = 0; i < 9; ++i)
		if(st[i]==0)
		{
			pos2=i;
			break;
		}

	mdist = abs(pos1/3 - pos2/3) + abs(pos1%3 - pos2%3);

	if((mdist&1)^(invcount&1)){
		return false;
	}

	else return true;
}

int main(){
	

}