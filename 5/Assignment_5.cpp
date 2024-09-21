#include <iostream>
#include <queue>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Insert a node in BST
Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    } else {
        cout << "Item " << data << " already present in the tree.\n";
    }
    return root;
}

// Search a node in BST
bool searchNode(Node* root, int key) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == key) {
        return true;
    }

    if (key < root->data) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

// Get the minimum value node in the right subtree
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a node from BST
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with one or no children
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder Traversal (Left, Root, Right)
void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

// Preorder Traversal (Root, Left, Right)
void preorderTraversal(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder Traversal (Left, Right, Root)
void postorderTraversal(Node* root) {
    if (root == nullptr) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

// Level Order Traversal (Breadth-First)
void levelOrderTraversal(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }

    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        cout << current->data << " ";
        q.pop();

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

// Function to calculate the height (depth) of the tree
int treeHeight(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return 1 + max(leftHeight, rightHeight);
}

// Function to create the mirror of the tree
Node* mirrorTree(Node* root) {
    if (root == nullptr) return nullptr;
    Node* mirror = createNode(root->data);
    mirror->left = mirrorTree(root->right);
    mirror->right = mirrorTree(root->left);
    return mirror;
}

// Function to create a copy of the tree
Node* copyTree(Node* root) {
    if (root == nullptr) return nullptr;
    Node* newRoot = createNode(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

int main() {
    Node* root = nullptr;
    int value;
    char more;
    cout << endl << "Do you want to insert a node?(y/n):";
    cin >> more;
    if(more == 'y'){
        cout << endl << "Enter value to Insert: ";
        cin >> value;
        root = insertNode(root, value);
    }
    cout << endl << "Do you want to insert a node?(y/n):";
    cin >> more;
    while(more == 'y'){
        cout << endl << "Enter value to Insert: ";
        cin >> value;
        insertNode(root, value);
        cout << endl << "Do you want to insert a node?(y/n):";
        cin >> more;
    }

    cout << "Inorder Traversal: ";
    inorderTraversal(root);
    cout << "\n";

    cout << "Preorder Traversal: ";
    preorderTraversal(root);
    cout << "\n";

    cout << "Postorder Traversal: ";
    postorderTraversal(root);
    cout << "\n";

    cout << "Level Order Traversal: ";
    levelOrderTraversal(root);
    cout << "\n";

    cout << "Search 40: " << (searchNode(root, 40) ? "Found" : "Not Found") << "\n";

    root = deleteNode(root, 70);
    cout << "Inorder after deletion of 70: ";
    inorderTraversal(root);
    cout << "\n";

    return 0;
}
