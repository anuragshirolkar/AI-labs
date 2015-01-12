#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
/**
 * structure to denote state of the problem
 */
struct node {
	int state[3][3];

	void print();
};

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
	int temp[3][3] = {
		{3,0,4},
		{6,7,2},
		{5,1,8}
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) start.state[i][j] = temp[i][j];
	int temp1[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) goal.state[i][j] = temp1[i][j];
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
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (n.state[i][j] == 0) count += abs(2-i) + abs(2-j);
			else count += abs(n.state[i][j]/3-2) + abs(n.state[i][j]%3-2);
		}
	}
	return count;
}

