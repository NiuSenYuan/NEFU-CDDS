#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

struct Student {
    char num[6];
    int grade;
};

typedef Student ElemType;

struct BSTNode {
    ElemType data;
    BSTNode *left;
    BSTNode *rchild;
};

BSTNode *insert(BSTNode *root, const ElemType &student);
void inorderTraversal(BSTNode *root);
int depth(BSTNode *root);
int countNodes(BSTNode *root);
int countLeaves(BSTNode *root);
bool search(BSTNode *root, const char *num);
BSTNode *remove(BSTNode *root, const char *num);
void printTreeAsList(BSTNode *root);

int main() {
    BSTNode *root = nullptr;
    int choice;

    do {
        cout << "\nBinary Search Tree Operations:" << endl;
        cout << "1. Insert a student record" << endl;
        cout << "2. Inorder traversal" << endl;
        cout << "3. Calculate tree depth" << endl;
        cout << "4. Count total nodes" << endl;
        cout << "5. Count leaf nodes" << endl;
        cout << "6. Search for a student record" << endl;
        cout << "7. Remove a student record" << endl;
        cout << "8. Print tree as list (generalized list)" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student newStudent;
                cout << "Enter student number (5 characters): ";
                cin >> newStudent.num;
                cout << "Enter student grade: ";
                cin >> newStudent.grade;
                root = insert(root, newStudent);
                break;
            }
            case 2: {
                cout << "Inorder Traversal:" << endl;
                inorderTraversal(root);
                cout << endl;
                break;
            }
            case 3: {
                cout << "Tree Depth: " << depth(root) << endl;
                break;
            }
            case 4: {
                cout << "Total Nodes: " << countNodes(root) << endl;
                break;
            }
            case 5: {
                cout << "Leaf Nodes: " << countLeaves(root) << endl;
                break;
            }
            case 6: {
                char searchNum[6];
                cout << "Enter student number to search: ";
                cin >> searchNum;
                if (search(root, searchNum)) {
                    cout << "Student record found." << endl;
                } else {
                    cout << "Student record not found." << endl;
                }
                break;
            }
            case 7: {
                char removeNum[6];
                cout << "Enter student number to remove: ";
                cin >> removeNum;
                root = remove(root, removeNum);
                break;
            }
            case 8: {
                cout << "Binary Search Tree as Generalized List:" << endl;
                printTreeAsList(root);
                cout << endl;
                break;
            }
            case 9: {
                cout << "Exiting program." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << endl;
            }
        }
    } while (choice != 9);

    return 0;
}

BSTNode *insert(BSTNode *root, const ElemType &student) {
    if (root == nullptr) {
        root = new BSTNode;
        root->data = student;
        root->left = root->rchild = nullptr;
    } else if (student.grade < root->data.grade) {
        root->left = insert(root->left, student);
    } else {
        root->rchild = insert(root->rchild, student);
    }
    return root;
}

void inorderTraversal(BSTNode *root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "Student Number: " << root->data.num << ", Grade: " << root->data.grade << endl;
        inorderTraversal(root->rchild);
    }
}

int depth(BSTNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->rchild);
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

int countNodes(BSTNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return countNodes(root->left) + countNodes(root->rchild) + 1;
    }
}

int countLeaves(BSTNode *root) {
    if (root == nullptr) {
        return 0;
    } else if (root->left == nullptr && root->rchild == nullptr) {
        return 1;
    } else {
        return countLeaves(root->left) + countLeaves(root->rchild);
    }
}

bool search(BSTNode *root, const char *num) {
    if (root == nullptr) {
        return false;
    } else if (strcmp(root->data.num, num) == 0) {
        return true;
    } else if (strcmp(num, root->data.num) < 0) {
        return search(root->left, num);
    } else {
        return search(root->rchild, num);
    }
}

BSTNode *remove(BSTNode *root, const char *num) {
    if (root == nullptr) {
        return nullptr;
    } else if (strcmp(num, root->data.num) < 0) {
        root->left = remove(root->left, num);
    } else if (strcmp(num, root->data.num) > 0) {
        root->rchild = remove(root->rchild, num);
    } else {
        if (root->left == nullptr) {
            BSTNode *temp = root->rchild;
            delete root;
            return temp;
        } else if (root->rchild == nullptr) {
            BSTNode *temp = root->left;
            delete root;
            return temp;
        }

        BSTNode *temp = root->rchild;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->rchild = remove(root->rchild, temp->data.num);
    }

    return root;
}

void printTreeAsList(BSTNode *root) {
    if (root == nullptr) {
        cout << "@";
    } else {
        cout << "(";
        cout << root->data.num << "," << root->data.grade;
        if (root->left != nullptr || root->rchild != nullptr) {
            cout << ",";
            printTreeAsList(root->left);
            cout << ",";
            printTreeAsList(root->rchild);
        }
        cout << ")";
    }
}
