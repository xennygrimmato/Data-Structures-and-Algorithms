#include<bits/stdc++.h>
using namespace std;
//Create a node class that consists of data value of the node and two child(left and right);
struct Node
{
	int data;
	struct Node *left, *right;
};
//Create a constructer 
Node* getNode(int val)
{
	Node* temp = new Node;
	temp->data = val;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
//insert a new value in the tree;
Node* insert(Node* root, int val)
{
	//if root is null then create a new node;
	if(!root)
		return getNode(val);
	if(root->data > val)
		root->left = insert(root->left, val);	//if the key value is less root then go for left child of root;
	else
		root->right = insert(root->right, val);	//else go for right child of the root;
	return root;		//return root node;
}
/**
left rotation 			a                       b
					  /   \                   /   \
					 b     c    ------>      d     a
				    / \   / \                     / \
				   d   e f   g                   e   c
				                                    / \
				                                   f   g
**/
Node* leftRotate(Node* root)
{
	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	return temp;
}
/**
right rotation 			a                       c
					  /   \                   /   \
					 b     c    ------>      a     g
				    / \   / \               / \
				   d   e f   g             b   f
				                          / \
				                         d   e
**/
Node* rightRotate(Node* root)
{
	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	return temp;
}
Node* splay(Node* root, int val)
{
	//if root is null or root value is equal to key value then return root;
	if(root == NULL or root->data == val)
		return root;
	if(root->data > val)
	{
		if(root->left == NULL)
			return root;		//if root->left is null then return root;
		if(root->left->data > val)
		{
			//if key value less than root->left data then go for root->left->left;
			root->left->left = splay(root->left->left, val);
			root = rightRotate(root);	//right rotate;			
		}
		else if(root->left->data < val)
		{
			//if key value greater than root->left data then go for root->left->right;
			root->left->right = splay(root->left->right, val);
			if(root->left->right != NULL)
				root->left = leftRotate(root->left);	//if root->left->right is not null then left rotate;
		}
		return (root->left == NULL) ? root : rightRotate(root);	//if root->left is not null then right rotate;
	}
	else
	{
		if(root->right == NULL)
			return root;		//if root->right is null then return root;
		if(root->right->data > val)
		{
			//if key value less than root->right data then go for root->right->left;
			root->right->left = splay(root->right->left, val);
			if(root->right->left != NULL)
				root->right = rightRotate(root->right);		//if root->left->left is not null then right rotate;
		}
		else if(root->right->data < val)
		{
			//if key value greater than root->right data then go for root->right->right;
			root->right->right = splay(root->right->right, val);
			root = leftRotate(root);		//left rotate;
		}
		return (root->right == NULL) ? root : leftRotate(root);	//if root->right is not null then left rotate;
	}
}
//search the key value in the tree;
Node* search(Node* root, int val)
{
	return splay(root, val);	//re-arrange the tree according to key value;
}
//pre-order traversal in the tree;
void preorder(Node* root)
{
	if(!root)
		return;	//if root is null then return;
	cout << root->data << " ";
	preorder(root->left);
	preorder(root->right);
}
int main()
{
	Node* root = NULL;
	root = insert(root, 50);
	root = insert(root, 25);
	root = insert(root, 32);
	root = insert(root, 62);
	root = insert(root, 28);
	root = insert(root, 10);
	root = insert(root, 70);
	//pre-order traversal;
	preorder(root);
	cout << endl;
	//search for a element in the tree;
	root = search(root, 28);
	//pre-order traversal;
	preorder(root);
	cout << endl;
	return 0;
}
