#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

//Place for the BST functions from Exercise 1.


Node *addNode(Node *root, int data){
    //allocate memory
    Node* new = (Node*)malloc(sizeof(struct Node));
    //add data
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    Node *temp = root;
    Node *prev = NULL;
    if (root == NULL){
        return new;
    }
    while (temp != NULL){
        if (data < temp->data){
            prev = temp;
            temp = temp->right;
        }
        else if (data > temp->data){
            prev = temp;
            temp = temp->left;
        }
        else{
            free(new);
            return NULL;
        }
    }
    if (data < prev->data){
        prev->right = new;
    }
    else if (data > prev->data){
        prev->left = new;
    }
    return root;
}

Node* removeNode(Node* root, int data)
{
  // Ensure root isn't null.
  if (root == NULL) {
    return NULL;
  }
  
  if (data > root->data) {  // Value is in the left sub-tree.
    root->left = removeNode(root->left, data);
  } else if (data < root->data) { // Value is in the right sub-tree.
    root->right = removeNode(root->right, data);
  } else { // Found the correct node with value
    // Check the three cases - no child, 1 child, 2 child...
    // No Children
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }
    // 1 child (on the right)
    else if (root->left == NULL) {
      Node *temp = root; // save current node
      root = root->right;
      free(temp);
    }
    // 1 child (on the left)
    else if (root->right == NULL) {
      Node *temp = root; // save current node
      root = root->left;
      free(temp);
    }
    // Two children
    else {
      // find minimal value of right sub tree
      Node *temp = root->left; 
      while(temp->right != NULL) {
        temp = temp->right;
      }
      root->data = temp->data; // duplicate the node
      root->left = removeNode(root->left, root->data); // delete the duplicate node
    }
  }
  return root; // parent node can update reference
}

void displaySubtree(Node * N){
    if (N != NULL){
        displaySubtree(N->right);
        printf("%d\n", N->data);
        displaySubtree(N->left);
    }
}

int countAndTotal(Node *N, int *count, int *total){
	if (N != NULL){
        	countAndTotal(N->right, count, total);
	*total += N->data;
        (*count) ++;
        countAndTotal(N->left, count, total);
    }
}

int countNodes(Node *N){
	int count = 0;
	int total = 0;
	countAndTotal(N, &count, &total);
	return count;
}

Node* freeSubtree(Node *N) {
  if (N == NULL)
    return NULL;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
}

void inOrderTraversal(Node* N, int *nodeList, int *index){
	if (N != NULL){
        inOrderTraversal(N->right, nodeList, index);
        nodeList[(*index)++] = N->data;
        inOrderTraversal(N->left, nodeList, index);
    }
}

float avgSubtree(Node *N){
	int count = 0;
	int total = 0;
	countAndTotal(N, &count, &total);
	if (count == 0){
		return -1;
	}
	return (float)total / count;
}

Node* makeSubtree(Node *root, int *nodeList, int l, int r){
	 if (l < r) {
        int middle = l + (r - l) / 2;
		root = addNode(root, nodeList[middle]);
        makeSubtree(root, nodeList, l, middle);
        makeSubtree(root, nodeList, middle + 1, r);
        }
    return root;
}

// This functions converts an unbalanced BST to a balanced BST
Node* balanceTree(Node* root){
	int count = countNodes(root);
	int nodeList[countNodes(root)];
	int index = 0;
	inOrderTraversal(root, nodeList, &index);
	root = makeSubtree(NULL, nodeList, 0, count);
	return root;
}
