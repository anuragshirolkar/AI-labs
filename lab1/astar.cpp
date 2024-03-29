#include <iostream>
#include <set>
#include <tr1/unordered_map>
#include "lists.cpp"
using namespace std;


struct astar {
	open_list ol;
	closed_list cl;
	graph g;

	vector<node> search();
};

vector<node> astar::search() {
	if (!g.start.is_reachable(g.goal)) {
		return vector<node>();
	}
	ol.insert(g.start, node(), 0, g.h(g.start));
	while (!ol.empty()) {
		open_list_member current = ol.getmin();
		vector<pair<node, int> > next = g.next(current.current);
		for (int i = 0; i < next.size(); i++) {
			node to_add = next[i].first;
			int length = next[i].second;
			if (ol.exists(to_add)) {
				ol.update(to_add, current, length, g.h(to_add));
			}
			else if(cl.exists(to_add)) {
				if (cl.need_update(to_add, current, length, g.h(to_add))) {
					cout << "error : node moved from closed list to open list" << endl;
					cl.erase(to_add);
					ol.insert(to_add, current.current, current.gval + length, current.gval+length+g.h(to_add));
				}
			}
			else {
				ol.insert(to_add, current.current, current.gval+length, current.gval+length+g.h(to_add));
			}
		}
		ol.erase(current);
		cl.insert(current);
		if (current.current == g.goal) break;
	}
	return cl.getpath(g.start, g.goal);
}

int main(void)
{
	astar a;
	int ans = a.search().size();
	if (ans == 0) cout << "Tumse na ho payega (Goal not reachable)" << endl;
	else {
		cout << "Distance from start to goal node : " << ans-1 << endl;
	}
	return 0;
}
