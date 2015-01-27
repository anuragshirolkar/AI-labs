#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;
/**
 * structure to denote state of the problem
 */
struct node {
	int state[3][3];

	void print();
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
	for (int i = 0; i < 9; ++i)	{
		for (int j = i+1; j < 9; ++j){
			if(pos[st[j]] < pos[st[i]])
				invcount++;
		}
	}
	int pos1=pos[0],pos2,mdist;
	for(int i = 0; i < 9; ++i)
		if(st[i]==0) {
			pos2=i;
			break;
		}
	mdist = abs(pos1/3 - pos2/3) + abs(pos1%3 - pos2%3);
	if((mdist&1)^(invcount&1)){
		return false;
	}
	else return true;
}


bool operator<(const node &a, const node &b) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a.state[i][j] != b.state[i][j]) return a.state[i][j] < b.state[i][j];
		}
	}
	return false;
}

bool operator==(const node &a, const node &b) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a.state[i][j] != b.state[i][j]) return false;
		}
	}
	return true;
}

struct KeyHasher
{
  std::size_t operator()(const node& k) const
  {
	  int count = 0;
	  for (int i = 0; i < 3; i++) {
		  for (int j = 0; j < 3; j++) {
			  count = count * 10 + k.state[i][j];
		  }
	  }
		return count % 10000000;
  }
};

void node::print() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) cout << state[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

/**
 * structure to denote the problem as a graph
 */
struct graph {
	node start, goal;

	graph();

	vector<pair<node, int> > next(node &);
	int h(node &);
};


graph::graph() {
	cout << "Enter state of the start node:" << endl;
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cin >> start.state[i][j];
	cout << "Enter state of the goal node:" << endl;
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cin >> goal.state[i][j];
}

vector<pair<node, int> > graph::next(node &n) {
	vector<pair<node, int> > v;
	node a, b, c, d;
	int i0, j0;
	for (int i= 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			a.state[i][j] = n.state[i][j];
			b.state[i][j] = n.state[i][j];
			c.state[i][j] = n.state[i][j];
			d.state[i][j] = n.state[i][j];
			if (n.state[i][j] == 0) {
				i0 = i;
				j0 = j;
			}
		}
	}
	if (i0 + 1 < 3) {
		a.state[i0][j0] = a.state[1+i0][j0];
		a.state[i0+1][j0] = 0;
		v.push_back(pair<node, int> (a, 1));
	}
	if (i0 - 1 >= 0) {
		b.state[i0][j0] = b.state[i0-1][j0];
		b.state[i0-1][j0] = 0;
		v.push_back(pair<node, int> (b, 1));
	}
	if (j0 - 1 >= 0) {
		d.state[i0][j0] = d.state[i0][j0-1];
		d.state[i0][j0-1] = 0;
		v.push_back(pair<node, int> (d, 1));
	}
	if (j0 + 1 < 3) {
		c.state[i0][j0] = c.state[i0][j0+1];
		c.state[i0][j0+1] = 0;
		v.push_back(pair<node, int> (c, 1));
	}
	return v;
}

int graph::h(node & n) {
	int type = 2;
	if (type == 0) return 0;
	if (type == 2) {
		int x1[9], y1[9], x2[9], y2[9];
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (n.state[i][j] == 0) ;//count += abs(2-i) + abs(2-j);
				x1[n.state[i][j]] = i;
				y1[n.state[i][j]] = j;
				x2[goal.state[i][j]] = i;
				y2[goal.state[i][j]] = j;
			}
		}
		for (int i = 1; i < 9; i++) count += abs(x1[i]-x2[i]) + abs(y1[i]-y2[i]);
		return 1.2*count;
	}
	if (type == 1) {
		int x1[9], y1[9], x2[9], y2[9];
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (n.state[i][j] == 0) ;//count += abs(2-i) + abs(2-j);
				x1[n.state[i][j]] = i;
				y1[n.state[i][j]] = j;
				x2[goal.state[i][j]] = i;
				y2[goal.state[i][j]] = j;
			}
		}
		for (int i = 1; i < 9; i++) if (abs(x1[i]-x2[i]) || abs(y1[i]-y2[i])) count++;
		return count;
	}
	if (type == 3) {
		int x1[9], y1[9], x2[9], y2[9];
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (n.state[i][j] == 0) ;//count += abs(2-i) + abs(2-j);
				x1[n.state[i][j]] = i;
				y1[n.state[i][j]] = j;
				x2[goal.state[i][j]] = i;
				y2[goal.state[i][j]] = j;
			}
		}
		for (int i = 1; i < 9; i++) {
			if (x1[i] != x2[i]) count++;
			if (y1[i] != y2[i]) count++;
		};
		return count;
	}
	if (type == 4) {
		int x1[9], y1[9], x2[9], y2[9];
		int count = 0;
		int key = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (n.state[i][j] == 0) ;//count += abs(2-i) + abs(2-j);
				x1[n.state[i][j]] = i;
				y1[n.state[i][j]] = j;
				x2[goal.state[i][j]] = i;
				y2[goal.state[i][j]] = j;
				key = key*10 + n.state[i][j];
			}
		}
		for (int i = 1; i < 9; i++) {
			if(key%2) count += abs(x1[i]-x2[i]);
			else count += abs(y1[i]-y2[i]);
		}
		return count;
	}
}

