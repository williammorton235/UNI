#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* right;
    struct Node* left;
}Node;

Node *addNode1(Node *root, int value){
    if (root == NULL){
        //allocate memory
        Node* new = (Node*)malloc(sizeof(Node));
        //add data
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    if (value < root->value){
        root->right = addNode1(root->right, value);
    }
    else if (value > root->value){
        root->left = addNode1(root->left, value);
    }
    return root;
}

Node *addNode(Node *root, int value){
    //allocate memory
    Node* new = (Node*)malloc(sizeof(Node));
    //add data
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    Node *temp = root;
    Node *prev = NULL;
    if (root == NULL){
        return new;
    }
    while (temp != NULL){
        if (value < temp->value){
            prev = temp;
            temp = temp->right;
        }
        else if (value > temp->value){
            prev = temp;
            temp = temp->left;
        }
    }
    if (value < prev->value){
        prev->right = new;
    }
    else if (value > prev->value){
        prev->left = new;
    }
    return new;
}

Node* removeNode(Node *root, int value){

    if (value < root->value){
        root->right = removeNode(root->right, value);
    }
    else if (value > root->value){
        root->left = removeNode(root->left, value);
    }
    if (value == root->value) {
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if (root->left == NULL){
            return root->right;
        }
        else if (root->right == NULL){
            return root->left;
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
                return temp;
            }
            else{
                temp->left = root->left;
                temp->right = root->right;
            }
            return temp;
        }
    }
    return root;
}

void displaySubtree(Node * N){
    if (N != NULL){
        displaySubtree(N->right);
        printf("%d\n", N->value);
        displaySubtree(N->left);
    }
}

int leavesNumber(Node *N){
    if (N == NULL){
        return 0;
    }
    else if (N->left == NULL && N->right == NULL){
        return 1;
    }
    else{
        return leavesNumber(N->left) + leavesNumber(N->right);
    }
}

Node* removeSubtree(Node *root, int value){
    if (root == NULL){
        return NULL;
    }
    Node *temp = root;
    while (temp->value != value){
        if (value > temp->value){
            temp = temp->left;
        }
        else if (value < temp->value){
            temp = temp->right;
        }
        if (temp == NULL){
            return root;
        }
    }
    if (temp->left == NULL && temp->right == NULL){
        printf("**1*%d***", temp->value);
        return removeNode(root, temp->value);
    }
    else{
        if (temp->left != NULL){
        removeSubtree(root, temp->left->value);
        }
        if (temp->right != NULL){
            removeSubtree(root, temp->right->value);
        }
        
        return removeNode(root, temp->value);
    }
    /*else if (temp->left == NULL){
        printf("**2*%d***", temp->value);
        return removeSubtree(root, temp->right->value);
    }
    else if (temp->right == NULL){
        printf("**3*%d***", temp->value);
        return removeSubtree(root, temp->left->value);
    }
    else{
        printf("**4*%d***", temp->value);
        return removeSubtree(root, temp->left->value);
        return removeSubtree(root, temp->right->value);
    }*/
    
}

int nodeDepth (Node * root, Node *N){
    int count = 0;
    while (root != NULL){
        if (N->value > root->value){
            root = root->left;
            count ++;
        }
        else if (N->value < root->value){
            root = root->right;
            count ++;
        }
        else{
            return count;
        }
    }
}

int main(){
    Node* root = addNode1(NULL, 1);
    addNode1(root, 5);
    addNode1(root, 3);
    addNode1(root, 4);
    addNode1(root, 2);
    displaySubtree(root);
    printf("****\n");
    root = removeNode(root, 5);
    displaySubtree(root);
    printf("****\n%d\n", leavesNumber(root));
    printf("%d", nodeDepth(root, root->left->right));
    printf("\n****\n");
    root = removeSubtree(root, 5);
    printf("\n****\n");
    displaySubtree(root);
}
