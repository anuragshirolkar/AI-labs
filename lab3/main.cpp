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

	i+=2;
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
		left = "("+left+")->F";

	if(whole_not_right)
		right = "("+right+")->F";

	if(left.size()==0)
		return create_tree(right);

	if(right.size()==0)
		return create_tree(left);

	node *root = new node;
	root->left = create_tree(left);
	root->right = create_tree(right);

	return root;
}


// Recursice function to print tree
void print_tree(node *root , int dept){
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


// Main
int main(int argc, char const *argv[])
{
	cout<<"Input theorem to be proved : \n";
	string s,s_temp;

	s.erase( remove_if( s.begin(), s.end(), ::isspace ), s.end() );

	cin>>s;

	node *root=create_tree(s),*temp;
	temp = root;

	vector<node*> node_set;

	while(temp!=NULL){
		if(temp->is_op){
			node_set.push_back(temp->left);
			temp = temp->right;
		}
		else if(temp->C == 'F'){
			temp = NULL;
		}
		else{
			s_temp= "~X->F";
			s_temp[1]=temp->C;
			temp = create_tree(s_temp);
		}
	}

	// Node_set is the set of all left subtrees
	

	
	return 0;
}
