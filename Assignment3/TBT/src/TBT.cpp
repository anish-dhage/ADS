//============================================================================
// Name        : TBT.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <queue>
using namespace std;

class TBST;

class Node
{
	int data;
	Node* left;
	Node* right;
	bool lbit;
	bool rbit;

public:
	Node()
	{
		data = 0;
		left = NULL;
		right = NULL;
		lbit = 0;
		rbit = 0;
	}
	friend class TBST;
};

class TBST{

	Node *root;
	Node *head;
public:
	TBST(){
		root = NULL;
		head = new Node;
		head->data = -1;
		head->left = root;
		head->lbit = 1;
		head->right = head;
	}
	void create();
	void preorder();
	void inorder();
};

void TBST::create(){
	Node *curr;
	Node *new1 = new Node;
	cout<<"Enter the data : ";
	cin>>new1->data;
	cout<<endl;

	if(root == NULL){
		root = new1;
		root->left = head;
		root->right = head;
	}

	else{
		curr = root;
		while(1)
		{
			if(new1->data < curr->data && curr->lbit == 0){
				cout<<"left\n";
				new1->right = curr;
				new1->left = curr->left;
				curr->left = new1;
				curr->lbit = 1;
				break;
			}
			else if(new1->data > curr->data && curr->rbit == 0){
				cout<<"right\n";
				new1->left = curr;
				new1->right = curr->right;
				curr->right = new1;
				curr->rbit = 1;
				break;
			}

			else if(new1->data < curr->data && curr->lbit == 1)
			{
				cout<<"left\n";
				curr = curr->left;
			}
			else if(new1->data > curr->data && curr->rbit == 1)
			{
				cout<<"right\n";
				curr = curr->right;
			}
			else
			{
				cout<<"Duplicate Data! Try Again\n";
				return;
			}
		}
	}
}

void TBST::preorder(){
	Node *curr;
	curr = root;
	bool flag = 0;
	while(curr != head){
		if(flag == 0){
			cout<<curr->data<<"\t";
		}
		if(flag == 0 && curr->lbit == 1){
			curr = curr->left;
			flag = 0;
		}
		else if(curr->rbit == 1){
			curr = curr->right;
			flag = 0;
		}
		else {
			curr = curr->right;
			flag = 1;
		}
	}
}

void TBST::inorder(){
	Node *curr;
	curr = root;
	bool flag = 0;
	while(curr != head){
		if(flag == 0 && curr->lbit == 1){
			curr = curr->left;
			flag = 0;
		}
		else if(curr->rbit == 1){
			cout<<curr->data<<"\t";
			curr = curr->right;
			flag = 0;
		}
		else if(curr->rbit == 0){
			cout<<curr->data<<"\t";
			curr = curr->right;
			flag = 1;
		}
	}
}

int main(){
	TBST A;
	int ch = 0;
	while (ch != 4){
		cout<<"\nEnter your Choice : \n1.Insert\n2.Preorder\n3.Inorder\n4.Exit\n";
		cin>>ch;
		switch(ch){

		case 1: A.create();
				break;

		case 2: A.preorder();
				break;

		case 3:	A.inorder();
				break;

		case 4: break;

		default:cout<<"\nTry Again!\n";
				break;

		}
	}
	return 0;
}

