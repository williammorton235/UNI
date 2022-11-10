#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

//Place for the BST functions from Exercise 1.

/*typedef struct Node{
    int value;
    struct Node* right;
    struct Node* left;
}Node;*/

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

Node* removeNode(Node *root, int value){
    if (value < root->data){
        root->right = removeNode(root->right, value);
    }
    else if (value > root->data){
        root->left = removeNode(root->left, value);
    }
    if (value == root->data) {
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if (root->left == NULL){
            Node *right = root->right;
            free(root);
            return right;
        }
        else if (root->right == NULL){
            Node *left = root->left;
            free(root);
            return left;
        }
        else{
            Node *temp = root->right;
            Node *last = NULL;
            Node *left = root->left;
            while (temp->left != NULL){
                last = temp;
                temp = temp->left;
            }
            if (temp->right != NULL){
                last->left = temp->right;
            }
            else if (left != NULL && left->left == NULL){
                temp->left = left;
                free(root);
                return temp;
            }
            else{
                temp->left = root->left;
                temp->right = root->right;
                last->left = NULL;
                last->right = NULL;
            }
            free(root);
            return temp;
        }
    }
    return root;
}

void displaySubtree(Node * N){
    if (N != NULL){
        displaySubtree(N->right);
        printf("%d\n", N->data);
        displaySubtree(N->left);
    }
}

int numberLeaves(Node *N){
    if (N == NULL){
        return 0;
    }
    else if (N->left == NULL && N->right == NULL){
        return 1;
    }
    else{
        return numberLeaves(N->left) + numberLeaves(N->right);
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

/*Node* freeSubtree(Node *N){
    if (N == NULL){
        return NULL;
    }
    Node *temp = N;
    while (temp->data != value){
        if (value > temp->data){
            temp = temp->left;
        }
        else if (value < temp->data){
            temp = temp->right;
        }
        if (temp == NULL){
            return root;
        }
    }
    if (temp->left == NULL && temp->right == NULL){
        printf("**1*%d***", temp->data);
        return removeNode(N, temp->data);
    }
    else{
        if (temp->left != NULL){
        freeSubtree(N, temp->left->data);
        }
        if (temp->right != NULL){
            freeSubtree(N, temp->right->data);
        }
        
        return removeNode(N, temp->data);
    }
}*/

int nodeDepth (Node * root, Node *N){
    int count = 0;
    if (N == NULL){
    	return -1;
    }
    while (root != NULL){
        if (N->data > root->data){
            root = root->left;
            count ++;
        }
        else if (N->data < root->data){
            root = root->right;
            count ++;
        }
        else{
            return count;
        }
    }
    return -1;
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
	//freeSubtree(root);
	root = makeSubtree(NULL, nodeList, 0, count);
	return root;
}
