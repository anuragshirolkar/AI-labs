#include <iostream>
#include <cstring>

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

	bool whole_not=false;

	if(s[0]=='~'){
		whole_not=true;
		s=s.substr(1);
	}

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
	
	do{
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

	if(whole_not)
		left = "("+left+")->F";

	if(left.size()==0)
		return create_tree(right);

	if(right.size()==0)
		return create_tree(left);

	node *root = new node;
	root->left = create_tree(left);
	root->right = create_tree(right);

	return root;
}

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
int main(int argc, char const *argv[])
{
	string s;
	cin>>s;

	node *root=create_tree(s);
	print_tree(root,50);
	return 0;
}