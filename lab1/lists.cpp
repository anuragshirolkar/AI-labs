#include <iostream>
#include <set>
#include <tr1/unordered_map>
#include "node.cpp"

struct open_list_member {
	node current;
	node parent;
	int fval, gval;

	open_list_member(node c, node p, int f, int g);
};

bool operator<(const open_list_member &a, const open_list_member &b) {
	if (a.fval != b.fval) return a.fval < b.fval;
	if (a.gval != b.gval) return a.gval > b.gval;
	return a.current < b.current;
}

open_list_member::open_list_member(node c, node p, int f, int g) {
	fval = f;
	gval = g;
	current = c;
	parent = p;
}

struct open_list {
	set<open_list_member> open_list;
	tr1::unordered_map<node, set<open_list_member>::iterator, KeyHasher> open_list_access;

	void insert(node, node, int, int);
	bool empty();
	open_list_member getmin();
	bool exists(node &);
	void update(node & to_add, open_list_member parent, int length, int heuristic);
	open_list_member first_member();
	void erase(open_list_member);
};

void open_list::insert(node n, node parent, int gval, int fval) {
	open_list_member m(n, parent, fval, gval);
	set<open_list_member>::iterator it = open_list.insert(m).first;
	open_list_access[n] = it;
}

bool open_list::empty() {
	return open_list.empty();
}

open_list_member open_list::getmin() {
	return *(open_list.begin());
}

bool open_list::exists(node & n) {
	tr1::unordered_map<node, set<open_list_member>::iterator >::iterator it = open_list_access.find(n);
	return (it != open_list_access.end());
}

void open_list::update(node & to_add, open_list_member parent, int length, int heuristic) {
	tr1::unordered_map<node, set<open_list_member>::iterator >::iterator it = open_list_access.find(to_add);
	if (it == open_list_access.end()) return;
	set<open_list_member>::iterator it1 = it->second;
	if (it1->fval <= parent.gval+length+heuristic) {
		return;
	}
	open_list.erase(it1);
	open_list_member m(to_add, parent.current, parent.gval+length+heuristic, parent.gval+length);
	open_list_access[to_add] = open_list.insert(m).first;
}

void open_list::erase(open_list_member m) {
	tr1::unordered_map<node, set<open_list_member>::iterator >::iterator it = open_list_access.find(m.current);
	open_list.erase(it->second);
	open_list_access.erase(it);
}


struct closed_list {
	tr1::unordered_map<node, pair<node ,int>, KeyHasher > closed_list;

	bool exists(node &);
	bool need_update(node &, open_list_member & parent, int length, int heuristic);
	void erase(node);
	void insert(open_list_member);
	vector<node> getpath(node &, node &);
};

bool closed_list::exists(node & n) {
	tr1::unordered_map<node, pair<node, int> > ::iterator it = closed_list.find(n);
	return (it != closed_list.end());
}

bool closed_list::need_update(node &n, open_list_member & parent, int length, int heuristic) {
	tr1::unordered_map<node, pair<node, int> > ::iterator it = closed_list.find(n);
	return (it->second.second > parent.gval+length+heuristic);
}

void closed_list::erase(node n){
	tr1::unordered_map<node, pair<node, int> > ::iterator it = closed_list.find(n);
	closed_list.erase(it);
}

void closed_list::insert(open_list_member m) {
	closed_list[m.current] = pair<node, int> (m.parent, m.fval);
}

vector<node> closed_list::getpath(node & start, node & goal) {
	cout << "number of nodes expanded: " << closed_list.size() << endl;
	tr1::unordered_map<node, pair<node, int> > ::iterator it = closed_list.find(goal);
	if (it == closed_list.end()) return vector<node>();
	vector<node> v;
	v.push_back(goal);
	while (!(v.at(v.size()-1) == start)) {
		v.at(v.size()-1).print();
		v.push_back(closed_list[(v.at(v.size()-1))].first);
	}
	start.print();
	return v;
}

