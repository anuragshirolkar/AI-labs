#include <iostream>
#include <set>
#include <map>
#include "node.cpp"
using namespace std;

struct open_list_member {
	int fval, gval;
	node current;
	node parent;

	open_list_member(int f, int g, node c, node p);
};

bool operator<(const open_list_member &a, const open_list_member &b) {
	if (a.fval != b.fval) return a.fval < b.fval;
	if (a.gval != b.gval) return a.gval < b.gval;
	return a.current < b.current;
}

open_list_member::open_list_member(int f, int g, node c, node p) {
	fval = f;
	gval = g;
	current = c;
	parent = p;
}

struct astar {
	set<open_list_member> open_list;
	map<node, set<open_list_member>::iterator> open_list_access;
	map<node, pair<node ,int> > closed_list;
	graph g;

	vector<node> search();
};

vector<node> astar::search() {
	open_list.insert(open_list_member(g.h(g.start), 0, g.start, node()));
	open_list_access[open_list.begin()->current] = open_list.begin();
	while(!open_list.empty()) {
		node current = open_list.begin()->current;
		if (current == g.goal) {
			break;
		}
		vector<pair<node, int> > next = g.next(current);
		for (int i = 0; i < next.size(); i++) {
			map<node, set<open_list_member>::iterator>::iterator it = open_list_access.find(next[i].first);
			map<node, pair<node, int> >::iterator it1 = closed_list.find(next[i].first);
			if (it != open_list_access.end()) {
				if (it->second->fval > open_list.begin()->gval+next[i].second+g.h(next[i].first)) {
					open_list.erase(it->second);
					set<open_list_member>::iterator temp = open_list.insert(open_list_member(open_list.begin()->gval+next[i].second+g.h(next[i].first), open_list.begin()->gval+next[i].second, next[i].first, current)).first;
					open_list_access[next[i].first] = temp;
				}
			}
			else if (it1 != closed_list.end()) {
				if (it1->second.second > open_list.begin()->gval+next[i].second+g.h(next[i].first)) {
					set<open_list_member>::iterator temp = open_list.insert(open_list_member(open_list.begin()->gval+next[i].second+g.h(next[i].first), open_list.begin()->gval+next[i].second, next[i].first, current)).first;
					open_list_access[next[i].first] = temp;
					closed_list.erase(it1);
				}
			}
			else {
				set<open_list_member>::iterator temp = open_list.insert(open_list_member(open_list.begin()->gval+next[i].second+g.h(next[i].first), open_list.begin()->gval+next[i].second, next[i].first, current)).first;
				open_list_access[next[i].first] = temp;
			}
		}
		closed_list[current] = pair<node, int> (open_list.begin()->parent, open_list.begin()->fval);
		open_list_access.erase(current);
		open_list.erase(open_list.begin());
	}
	cout << "closed list size: " << closed_list.size() <<" open list size: " << open_list.size() <<  endl;
	if (open_list.empty()) return vector<node>();
	vector<node> ans;
	ans.push_back(g.goal);
	ans.push_back(open_list.begin()->parent);
	g.goal.print();
	while(true) {
		ans[ans.size()-1].print();
		if (ans[ans.size()-1] == g.start) break;
		ans.push_back(closed_list[ans[ans.size()-1]].first);
	}
	return ans;
}

int main(void)
{
	astar a;
	cout << a.search().size() << endl;
	return 0;
}
