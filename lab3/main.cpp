#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <iomanip>
#include <string>
using namespace std;


struct node {
	int valid;
	char val;
	set<node> children;

	node(){};
	node (string);
	pair<string, string> split(string);
	void print();
};

bool operator<(const node a, const node b) {
	if (a.valid == 1 && b.valid == 0) return true;
	if (a.valid == 0 && b.valid == 1) return false;
	if (a.valid == 1 && b.valid == 1) return a.val < b.val;
	set<node> :: iterator it2 = b.children.begin();
	set<node> :: iterator it1 = a.children.begin();
	for (; ; it1++, it2++) {
		if (it1 == a.children.end() && it2 == b.children.end()) return false;
		if (it2 == b.children.end()) return false;
		if (it1 == a.children.end()) return true;
		node a1 = *(it1);
		node b1 = *(it2);
		if (a1 < b1) return true;
		if (b1 < a1) return false;
	}
	return false;
}

pair<string, string> node::split(string s) {
	if (s.size() == 1) return pair<string, string> (s, "");
	if (s.size() < 4) return pair<string, string> ("","");
	string s1 = "";
	int i;
	if (s[1] == '-' && s[2] == '>') {
		s1 += s[0];
		i = 3;
	}
	else if (s[0] == '(') {
		int count = 0;
		for (i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				count++;
				s1 += '(';
			}
			else if (s[i] == ')' && count == 1) {
				s1 += ')';
				break;
			}
			else if (s[i] == ')') {
				s1 += ')';
				count--;
			}
			else {
				s1 += s[i];
			}
		}
		if (s1[s1.size()-1] != ')') {
			return pair<string, string>("","");
		}
		if (i == s.size()-1) {
			return split(s.substr(1,s.size()-2));
		}
		if (s[i+1] != '-' || s[i+2] != '>') {
			return pair<string, string> ("","");
		}
		i+=3;
	}
	if(i == s.size()-1) {
		string temp = "";
		temp += s[i];
		return pair<string, string>(s1, temp);
	}
	return pair<string, string> (s1, s.substr(i, s.size()-i));
}

// Constructor
node::node(string s) {
	if (s.size() == 1) {
		valid = 1;
		val = s[0];
		return;
	}
	valid = 0;
	pair<string, string> p;
	while (true) {
		if (s == "F") return;
		if (s.size() == 1) {
			children.insert(node(s+"->F"));
			return;
		}
		p = split(s);
		children.insert(node(p.first));
		s = p.second;
	}
	return;
}

void node::print() {
	if (valid == 1) cout << val;
	else {
		cout << "{ ";
		for (set<node> :: iterator it = children.begin(); it != children.end(); it++) {
			if (it != children.begin()) cout << " , ";
			node a = (*it);
			a.print();
		}
		cout << " }";
	}
	return;
}

bool deducible(set<node> a, node b, set<node> a_parent) {
	//if (level == 0) return false;
	set<node> :: iterator it = a.find(b);
	if (it != a.end()) return true;
	
	if (b.valid == 1) {
		string s = "->F";
		s = b.val + s;;
		a.insert(node(s));
	}
	else {
		for (set<node> :: iterator it = b.children.begin(); it != b.children.end(); it++) {
			node n = *(it);
			a.insert(n);
		}
	}
	node x, y;
	x.children = a;
	y.children = a_parent;
	if (!(x < y) && !(y < x)) return false;

	/*
	// printing for debuggin
	cout << endl << "On the level : " << level << endl;
	cout << "printing set a : " << endl;
	for (set<node> :: iterator it = a.begin(); it != a.end(); it++) {
		node temp = *(it);
		temp.print();
		cout << endl;
	}
	cout << "printing a done" << endl;
	cout << "printing b : ";
	b.print();
	cout << endl;
	*/
	
	int last_count = a.size();
	while(true) {
		set<node> a_new = a;
		for (set<node> :: iterator it = a.begin(); it != a.end(); it++) {
			node current = *(it);
			if (current.valid == 1) continue;
			a_new.erase(current);
			vector<set<node> :: iterator> to_remove;
			for (set<node> :: iterator it1 = current.children.begin(); it1 != current.children.end(); it1++) {
				node new_child = *(it1);
				if (deducible(a_new, new_child, a)) {
					to_remove.push_back(it1);
					a.insert(new_child);
				}
			}
			for (int i = 0; i < to_remove.size(); i++) {
				current.children.erase(to_remove[i]);
			}
			if (current.children.size() == 0) return true;
			a_new.insert(current);
		}
		if (last_count = a.size()) return false;
		last_count = a.size();
	}
}

bool deducible(string s) {
	node n(s);
	pair<string, string> p = n.split(s);
	node a(p.first);
	node b(p.second);
	set<node> st;
	st.insert(a);
	return deducible(st, b, set<node>());
}

int main() {
	string s;
	cin >> s;
	bool is_deducible = deducible(s);
	if (is_deducible) cout << "The expression is provable" << endl;
	else cout << "I could not prove the expression" << endl;
	return 0;
}
