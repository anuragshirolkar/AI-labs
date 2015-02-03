#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

/** Node struct to hold the structure of the theorem
 For example : (p->q)->((~p->q)->q)

*/
struct node{
	bool is_op;
	char C;				// if is_op is false then this will hold a alphabet
	node *left;
	node *right;
	node(){
		is_op = true;
		left = NULL;
		right = NULL;
	}
};


// Recursive function to create tree
node* create_tree(string &s){

	if(s.size()==1){
		node * root=new node;
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

	node *root = new node;
	if(is_or){
		root->left = create_tree(left);
		string s1="(F->"+right+")";
		root->right = create_tree(s1);
	}
	else if(is_and){
		string s1="("+left+"->(("+right+")->F))";
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
void print_tree(node *root , int dept=50){
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

string fold_tree(node *root){
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

bool is_equal(node* n1 , node* n2){

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
	s.erase( remove_if( s.begin(), s.end(), ::isspace ), s.end() );
	node *root=create_tree(s);
	return fold_tree;
}

// Main
int main(int argc, char const *argv[])
{
	
	
	return 0;
}
