#include <stdio.h>
#include <stdlib.h>

#define ORDER 3   // B-Tree of order 3 (max 2 keys)

typedef struct BTreeNode {
    int keys[ORDER];     
    int childCount;      
    struct BTreeNode *child[ORDER+1];
    int leaf;           
} Node;

Node* createNode(int leaf) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->childCount = 0;
    n->leaf = leaf;
    for(int i=0;i<ORDER+1;i++)
        n->child[i] = NULL;
    return n;
}

void traverse(Node* root) {
    if(root == NULL) return;
    int i;
    for(i = 0; i < root->childCount; i++) {
        if(root->leaf == 0)
            traverse(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    if(root->leaf == 0)
        traverse(root->child[i]);
}

Node* splitChild(Node* parent, int i, Node* child) {
    Node* newChild = createNode(child->leaf);
    newChild->childCount = 1;

    newChild->keys[0] = child->keys[1];
    
    if(child->leaf == 0) {
        newChild->child[0] = child->child[2];
        newChild->child[1] = child->child[3];
    }

    child->childCount = 1;
    
    for(int j = parent->childCount; j >= i+1; j--)
        parent->child[j+1] = parent->child[j];
    parent->child[i+1] = newChild;

    for(int j = parent->childCount - 1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];
    parent->keys[i] = child->keys[1];
    parent->childCount += 1;
    
    return parent;
}

Node* insertNonFull(Node* root, int key) {
    int i = root->childCount - 1;

    if(root->leaf == 1) {
        while(i >= 0 && key < root->keys[i]) {
            root->keys[i+1] = root->keys[i];
            i--;
        }
        root->keys[i+1] = key;
        root->childCount += 1;
        return root;
    }
    else {
        while(i >= 0 && key < root->keys[i])
            i--;
        i++;

        if(root->child[i]->childCount == ORDER-1) {
            root = splitChild(root, i, root->child[i]);
            if(key > root->keys[i])
                i++;
        }
        root->child[i] = insertNonFull(root->child[i], key);
        return root;
    }
}

Node* insert(Node* root, int key) {
    if(root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->childCount = 1;
        return root;
    }

    if(root->childCount == ORDER-1) {
        Node* newRoot = createNode(0);
        newRoot->child[0] = root;
        newRoot = splitChild(newRoot, 0, root);

        int i = 0;
        if(key > newRoot->keys[0])
            i++;
        newRoot->child[i] = insertNonFull(newRoot->child[i], key);
        return newRoot;
    }
    else {
        return insertNonFull(root, key);
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while(1) {
        printf("\n--- B-Tree Menu ---\n");
        printf("1. Insert\n");
        printf("2. Display (Traverse)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Inserted.\n");
                break;

            case 2:
                printf("B-Tree elements: ");
                traverse(root);
                printf("\n");
                break;

            case 3:
                exit(0);
            
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
