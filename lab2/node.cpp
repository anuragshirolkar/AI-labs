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
	int h1(node &);
	int h2(node &);
};


graph::graph() {
	int temp[3][3] = {
		{6,4,7},
		{5,0,8},
		{1,2,3}
		//{5,6,7},
		//{4,8,0},
		//{3,2,1}
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) start.state[i][j] = temp[i][j];
	int temp1[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,0}
		//{1,2,3},
		//{8,4,0},
		//{7,6,5}
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

int graph::h1(node & n) {
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
		return count;
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
}


int graph::h2(node & n) {
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
				x2[start.state[i][j]] = i;
				y2[start.state[i][j]] = j;
			}
		}
		for (int i = 1; i < 9; i++) count += abs(x1[i]-x2[i]) + abs(y1[i]-y2[i]);
		return count;
	}
	if (type == 1) {
		int x1[9], y1[9], x2[9], y2[9];
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (n.state[i][j] == 0) ;//count += abs(2-i) + abs(2-j);
				x1[n.state[i][j]] = i;
				y1[n.state[i][j]] = j;
				x2[start.state[i][j]] = i;
				y2[start.state[i][j]] = j;
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
				x2[start.state[i][j]] = i;
				y2[start.state[i][j]] = j;
			}
		}
		for (int i = 1; i < 9; i++) {
			if (x1[i] != x2[i]) count++;
			if (y1[i] != y2[i]) count++;
		};
		return count;
	}
}
