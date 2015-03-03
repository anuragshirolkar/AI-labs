#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <iomanip>
#include <string>
using namespace std;


/** parser_node struct to hold the structure of the theorem
 For example : (p->q)->((~p->q)->q)

*/
struct parser_node{
	bool is_op;
	char C;				// if is_op is false then this will hold a alphabet
	parser_node *left;
	parser_node *right;
	parser_node(){
		is_op = true;
		left = NULL;
		right = NULL;
	}
};


// Recursive function to create tree
parser_node* create_tree(string &s){

	if(s.size()==1){
		parser_node * root=new parser_node()	;
		root->is_op = false;
		root->C = s[0];
		return root;
	}

	if(s.size()==0){
		return NULL;
	}

	string left = "" , right="";
	int br_count = 0 , i = 0 , l= s.size();

	bool whole_not_right=false;
	bool whole_not_left=false;

	bool is_and=false;
	bool is_or=false;

	if(s[0]=='~'){
		whole_not_left=true;
		i++;
	}

	// Finding left part
	do{
		if(s[i]=='(')
		{
			if(br_count > 0)
				left += s[i];
			br_count++;
		}
		else if(s[i]==')'){
			br_count--;
			if(br_count > 0)
					left += s[i];
		}
		else{
			left += s[i];
		}
		i++;
	}while(br_count>0 && i<l);

	if(s[i]=='^')
		is_and = true;
	else if(s[i]=='v')
		is_or = true;
	else
		i++;
	i++;

	//cout<<is_or<<" "<<is_and<<" "<<s[i-1]<<endl;
	br_count = 0;
	
	if(s[i]=='~'){
		whole_not_right=true;
		i++;
	}	

	// Finding right part
	do{
		if(i>=l) break;
		if(s[i]=='(')
		{
			if(br_count > 0)
				right += s[i];
			br_count++;
		}
		else if(s[i]==')'){
			br_count--;
			if(br_count > 0)
				right += s[i];
		}
		else{
			right += s[i];
		}
		i++;
	}while(br_count>0 && i<l);

	if(whole_not_left)
		left = "(("+left+")->F)";

	if(whole_not_right)
		right = "(("+right+")->F)";

	if(left.size()==0)
		return create_tree(right);

	if(right.size()==0)
		return create_tree(left);

	parser_node *root = new parser_node;
	if(is_or){
		string s1="(("+left+")->F)";
		root->left = create_tree(s1);
		root->right = create_tree(right);
	}
	else if(is_and){
		//cout<<left<<"  :   "<<right<<endl;
		string s1="(("+left+")->(("+right+")->F))";
		//cout<<s1<<"     &&&&\n";
		root->left = create_tree(s1);
		s1 = "F";
		root->right = create_tree(s1);
	}
	else{
		root->left = create_tree(left);
		root->right = create_tree(right);
	}

	return root;
}


// Recursice function to print tree
void print_tree(parser_node *root , int dept=50){
	if(root==NULL)
		return;

	if(root->is_op)
	{
		for(int i=0;i<dept;i++)
			cout<<"-";
		cout<<endl;

		cout<<"Operator -> "<<endl;
		print_tree(root->left , dept-5);
		print_tree(root->right , dept-5);

		for(int i=0;i<dept;i++)
			cout<<"-";
		cout<<endl;
	}
	else{
		cout<<root->C<<endl;
	}
}

string fold_tree(parser_node *root){
	string s="";
	if(root==NULL)
		return s;

	if(root->is_op)
	{
		string s1 = fold_tree(root->left);
		string s2 = fold_tree(root->right);
		s = "("+s1+"->"+s2+")";
		return s;
	}
	else{
		s=" ";
		s[0]=root->C;
		return s;
	}
}

// Recursive function to check if two trees are equal

bool is_equal(parser_node* n1 , parser_node* n2){

	if(n1==NULL && n2==NULL)
		return true;

	if(n1==NULL)
		return false;

	if(n2==NULL)
		return false;

	if(n1->is_op != n2->is_op)
		return false;


	if(n1->is_op)
		return is_equal(n1->left,n2->left) && is_equal(n1->right,n2->right);

	return  (n1->C)==(n2->C);
}


string convert(string s){
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	parser_node *root=create_tree(s);
	//print_tree(root);
	return fold_tree(root);
}

struct node {
	int valid;
	char val;
	set<node> children;

	node(){};
	node (string);
	pair<string, string> split(string);
	void print();
	void print1() const;
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
		//cout<<"Yo: "<<val<<endl;
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

bool deducible(set<node> a, node b, set<node> a_parent, vector<node> &proof) {
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
				if (deducible(a_new, new_child, a, proof)) {
					to_remove.push_back(it1);
					a.insert(new_child);
					proof.push_back(new_child);
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

bool deducible(string s, vector<node> &proof) {
	node n(s);
	pair<string, string> p = n.split(s);
	node a(p.first);
	node b(p.second);
	set<node> st;
	st.insert(a);
	return deducible(st, b, set<node>(), proof);
}

void node::print1() const{
	if(children.empty()){
		cout<<val;
		return;
	}
	cout << "(";
	for (set<node> :: iterator it = children.begin(); it != children.end(); it++) {
		if (it!= children.begin()) cout << " -> ";
		it->print1();
	}
	cout << ")" << endl;
}

int main() {
	vector<node> proof;
	string s;
	getline(cin,s);
	s=convert(s);
	cout<<s<<"\n\n";
	bool is_deducible = deducible(s, proof);
	if (is_deducible) cout << "The expression is provable" << endl;
	else cout << "I could not prove the expression" << endl;
	//for (int i = 0; i < proof.size(); i++) proof[i].print1();
	return 0;
}
