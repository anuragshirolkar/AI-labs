#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
/**
 * structure to denote state of the problem
 */
struct node {
	int cannibals, priests;
	bool boatstate;
	void print();
	bool valid();
	node(){};
	node(int c, int p, bool b) {
		cannibals = c;
		priests = p;
		boatstate = b;
	}
};

bool operator<(const node &a, const node &b) {
	if (a.cannibals != b.cannibals) return a.cannibals < b.cannibals;
	if (a.priests != b.priests) return a.priests < b.priests;
	return false;
}

bool operator==(const node &a, const node &b) {
	if (a.cannibals != b.cannibals || a.priests != b.priests || a.boatstate != b.boatstate) return false;
	return true;
}

struct KeyHasher
{
	std::size_t operator()(const node& k) const
	{
		int count = 0;
		count += k.cannibals;
		count = count*4+k.priests;
		count = count*2+k.boatstate;
		return count;
	}
};

void node::print() {
	cout << "Cannibals: " << cannibals << endl;
	cout << "Priests  : " << priests << endl;
	if (boatstate) cout << "Boat on the left" << endl;
	else cout << "Boat on the right" << endl;
	cout << endl;
}

bool node::valid() {
	if (cannibals < 0 || cannibals > 3 || priests < 0 || priests > 3) return false;
	if ((priests == 3) || (priests == 0)) return true;
	if (cannibals == priests) return true;
	return false;
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
	start.cannibals = 3;
	start.priests = 3;
	start.boatstate = true;
	goal.cannibals = 0;
	goal.priests = 0;
	goal.boatstate = false;
}

vector<pair<node, int> > graph::next(node &n) {
	vector<pair<node, int> > v;
	if (n.boatstate) {
		node a[5];
		a[0] = *(new node(n.cannibals-2, n.priests, !n.boatstate));
		a[1] = *(new node(n.cannibals-1, n.priests, !n.boatstate));
		a[2] = *(new node(n.cannibals-1, n.priests-1, !n.boatstate));
		a[3] = *(new node(n.cannibals, n.priests-1, !n.boatstate));
		a[4] = *(new node(n.cannibals, n.priests-2, !n.boatstate));
		for (int i = 0; i < 5; i++) if(a[i].valid()) v.push_back(pair<node, int>(a[i], 1));
	}
	else {
		node a[5];
		a[0] = *(new node(n.cannibals+2, n.priests, !n.boatstate));
		a[1] = *(new node(n.cannibals+1, n.priests, !n.boatstate));
		a[2] = *(new node(n.cannibals+1, n.priests+1, !n.boatstate));
		a[3] = *(new node(n.cannibals, n.priests+1, !n.boatstate));
		a[4] = *(new node(n.cannibals, n.priests+2, !n.boatstate));
		for (int i = 0; i < 5; i++) if(a[i].valid()) v.push_back(pair<node, int>(a[i], 1));
	}
	return v;
}

int graph::h(node & n) {
	return 0;
}

