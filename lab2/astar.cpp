#include <iostream>
#include <set>
#include <tr1/unordered_map>
#include "lists.cpp"
using namespace std;


struct astar {
	open_list ol1, ol2;
	closed_list cl1, cl2;
	graph g;

	vector<node> search();
};

vector<node> astar::search() {
	ol1.insert(g.start, node(), 0, g.h1(g.start));
	ol2.insert(g.goal, node(), 0, g.h2(g.goal));

	node link;
	while (!ol1.empty() && !ol2.empty()) {
		open_list_member current = ol1.getmin();
		vector<pair<node, int> > next = g.next(current.current);
		for (int i = 0; i < next.size(); i++) {
			node to_add = next[i].first;
			int length = next[i].second;
			if (ol1.exists(to_add)) {
				ol1.update(to_add, current, length, g.h1(to_add));
			}
			else if(cl1.exists(to_add)) {
				if (cl1.need_update(to_add, current, length, g.h1(to_add))) {
					cout << "error1" << endl;
					cl1.erase(to_add);
					ol1.insert(to_add, current.current, current.gval + length, current.gval+length+g.h1(to_add));
				}
			}
			else {
				ol1.insert(to_add, current.current, current.gval+length, current.gval+length+g.h1(to_add));
			}
		}
		ol1.erase(current);
		cl1.insert(current);
		if (cl2.exists(current.current)) {
			link = current.current;
			break;
		}

		current = ol2.getmin();
		next = g.next(current.current);
		for (int i = 0; i < next.size(); i++) {
			node to_add = next[i].first;
			int length = next[i].second;
			if (ol2.exists(to_add)) {
				ol2.update(to_add, current, length, g.h2(to_add));
			}
			else if(cl2.exists(to_add)) {
				if (cl2.need_update(to_add, current, length, g.h2(to_add))) {
					cout << "error2" << endl;
					cl2.erase(to_add);
					ol2.insert(to_add, current.current, current.gval + length, current.gval+length+g.h2(to_add));
				}
			}
			else {
				ol2.insert(to_add, current.current, current.gval+length, current.gval+length+g.h2(to_add));
			}
		}
		ol2.erase(current);
		cl2.insert(current);
		if (cl1.exists(current.current)) {
			link = current.current;
			break;
		}
	}
	vector<node> n;
	cout << cl1.getpath(g.start, link).size() + cl2.getpath(g.goal, link).size() - 1 << endl;
	return n;
}

int main(void)
{
	astar a;
	cout << a.search().size() << endl;
	return 0;
}
