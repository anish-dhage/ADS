//============================================================================
// Name        : Binary_Tree.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <queue>
using namespace std;

class BinTree;

class Node
{
	string keyword;
	string meaning;
	Node* left;
	Node* right;

public:
	Node()
	{
		keyword = " ";
		meaning = " ";
		left = NULL;
		right = NULL;
	}
	friend class BinTree;
};

class BinTree
{
	Node* root;

public:
	BinTree(){
		root = NULL;
	}
	int compare(string s1,string s2);
	void insert();
	void display();
	void search();
	void recur_inorder(Node*);
	void delete_node(string del_data);
	int height(Node *rt, int h);

	Node* retroot(){
		return root;
	}

	void operator = (BinTree const &t){
		Node* new1 = new Node;
	    new1->keyword = t.root->keyword;
	    new1->meaning = t.root->meaning;
	    root = new1;
	    queue <Node*> q1,q2;
	    q1.push(t.root);
	    q2.push(root);
	    Node *copy,*org;
        while(!q2.empty())
        {
        	Node *n1 = new Node;
            Node *n2 = new Node;
            org = q1.front();
            q1.pop();
            copy = q2.front();
            q2.pop();
            if(org->left!=NULL)
            {
                n1->keyword = org->left->keyword;
                n1->meaning = org->left->meaning;
                copy->left = n1;
                q1.push(org->left);
                q2.push(copy->left);
            }
            if(org->right!=NULL)
            {
            	n2->keyword = org->right->keyword;
            	n2->meaning = org->right->meaning;
                copy->right = n2;
                q1.push(org->right);
                q2.push(copy->right);
            }
        }

	}

};

void BinTree::recur_inorder(Node* curr){
	if(curr->left!= NULL){
		recur_inorder(curr->left);
	}
	cout<<curr->keyword<<"\t"<<curr->meaning<<endl;
	if(curr->right!= NULL){
		recur_inorder(curr->right);
	}
}

int BinTree::compare(string s1,string s2){
	double i = 0;
	while(i<s1.length()||i<s2.length()){
		if(s1[i] > s2[i]){
			return 1;
		}
		else if(s1[i] < s2[i]){
			return 2;
		}
		else{
			i++;
		}
	}
	return 0;
}

void BinTree::insert()
{
	Node* new1 = new Node;
	cout<<"Enter the keyword : ";
	getline(cin,new1->keyword);
	cout<<"Enter the meaning of "<<new1->keyword<<" : ";
	getline(cin,new1->meaning);

	if (root == NULL)
	{
		root = new1;
	}
	else
	{
		Node *curr;
		Node *temp;
		curr = root;
		while(curr!=NULL)
		{
			temp = curr;
			if(compare(curr->keyword,new1->keyword) == 1)
			{
				cout<<"left\n";
				curr = curr->left;
			}
			else if(compare(curr->keyword,new1->keyword) == 2)
			{
				cout<<"right\n";
				curr = curr->right;
			}
			else
			{
				cout<<"Duplicate Keyword! Try Again\n";
				return;
			}
		}
		if(compare(temp->keyword,new1->keyword) == 1)
		{
			temp->left = new1;
		}
		else if(compare(temp->keyword,new1->keyword) == 2)
		{
			temp->right = new1;
		}
	}
}

void BinTree::display()
{
	if (root == NULL)
	{
		cout<<"\nQueue is Empty!\n";
		return;
	}

	queue <Node*> disq;
	Node *curr ;
	cout<<endl;

	disq.push(root);

	while(!disq.empty())
	{
		curr = disq.front();

		cout<<curr->keyword<<"\t"<<curr->meaning<<endl;

		if(curr->left != NULL)
		{
			disq.push(curr->left);
		}
		if(curr->right != NULL)
		{
			disq.push(curr->right);
		}
		disq.pop();
	}
	cout<<endl;
}

void BinTree::search(){
	Node *curr = root;
	string search_ele;
	cout<<"Enter Keyword to be searched : ";
	getline(cin,search_ele);
	while(curr!=NULL)
	{
		if(curr->keyword == search_ele)
		{
			cout<<"\nFOUND! : "<<curr->keyword<<"\tMeaning : "<<curr->meaning<<endl;
			cout<<"Enter new meaning : ";
			getline(cin,curr->meaning);
			break;
		}
		else if(compare(curr->keyword,search_ele) == 1)
		{
			curr = curr->left;
		}
		else if(compare(curr->keyword,search_ele) == 2)
		{
			curr = curr->right;
		}
		else
		{
			curr = NULL;
		}
	}
}

void BinTree::delete_node(string del_data){
	Node *curr = root;
	Node *prev = NULL;
	while(curr!=NULL)
	{
		if(curr->keyword == del_data)
		{
			break;
		}
		else if(compare(curr->keyword,del_data) == 1)
		{
			prev = curr;
			curr = curr->left;
		}
		else if(compare(curr->keyword,del_data) == 2)
		{
			prev = curr;
			curr = curr->right;
		}
		else
		{
			curr = NULL;
		}
	}
	cout<<curr->keyword<<endl;
	if(curr->left==NULL && curr->right==NULL){
		if(curr ==prev->right && curr != root){
			prev->right = NULL;
		}
		if(curr ==prev->left && curr != root){
			prev->left = NULL;
		}
		curr = NULL;
		delete curr;
		return;
	}

	else if(curr->left!=NULL && curr->right!=NULL){
		cout<<"both node"<<endl;
		Node *minl = curr -> right;
		while(minl->left!=NULL){
			minl = minl->left;
		}
		string temp;
		temp = curr->keyword;
		curr->keyword = minl->keyword;
		minl->keyword = temp;
		temp = curr->meaning;
		curr->meaning = minl->meaning;
		minl->meaning = temp;

		delete_node(minl->keyword);
	}

	else if(curr->left == NULL && curr->right != NULL){
		cout<<"one nodes"<<endl;
		prev->right = curr->right;
		curr->right = NULL;
		curr = NULL;
		delete curr;
		return;
	}

	else if(curr->left != NULL && curr->right == NULL){
		cout<<"one nodes"<<endl;
		prev->left = curr->left;
		curr->left = NULL;
		curr = NULL;
		delete curr;
		return;
	}
}

int BinTree::height(Node *rt, int h){
	Node *rsub;
	Node *lsub;
	int rh ;
	int lh ;
	if(rt->left == NULL && rt->right == NULL){
		return h;
	}
	if(rt->left != NULL){
		lsub = rt->left;
		lh = height(lsub, h+1);
		if(rt->right == NULL){
			return lh;
		}
	}
	if(rt->right != NULL){
		rsub = rt->right;
		rh = height(rsub, h+1);
		if(rt->left == NULL){
			return rh;
		}
	}

	if(lh > rh){
		return lh;
	}
	else{
		return rh;
	}
}

int main()
{
	BinTree A,B;
	string ele_del;
	int ch = 0;
	while (ch != 8){
		cout<<"Enter your Choice : \n1.Insert\n2.Display\n3.Search\n4.Copy\n5.Ascending Descending\n6.Delete\n7.Max Comparisons\n8.Exit\n";
		cin>>ch;
		switch(ch){

		case 1: cin.ignore();
				A.insert();
				break;

		case 2: A.display();
				break;

		case 3:	cin.ignore();
				A.search();
				break;

		case 4: B = A;
				B.display();
				break;

		case 5: A.recur_inorder(A.retroot());
				break;

		case 6: cin.ignore();
				cout<<"Enter Element to be deleted : ";
				getline(cin,ele_del);
				A.delete_node(ele_del);
				break;

		case 7: cout<<"Max Comparisons : "<<A.height(A.retroot(),0)<<endl;
				break;

		case 8: break;

		default:cout<<"\nTry Again!\n";
				break;

		}
	}
	return 0;
}
