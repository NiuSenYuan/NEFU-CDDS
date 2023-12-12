#include <iostream>
#include <stack>
#include <queue>
#include <cstring> 
#include <iomanip>
using namespace std;
// 定义学生记录类型
struct Student {
    char num[6];  // 学号
    int grade;    // 成绩
};

// 定义二叉排序树节点值的类型为学生记录类型
typedef Student ElemType;

// 定义二叉排序树的节点类型
struct BSTNode {
    ElemType data;
    struct BSTNode *left;
    struct BSTNode *rchild;
};

// 函数声明
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
        std::cout << "\nBinary Search Tree Operations:" << std::endl;
        std::cout << "1. Insert a student record" << std::endl;
        std::cout << "2. Inorder traversal" << std::endl;
        std::cout << "3. Calculate tree depth" << std::endl;
        std::cout << "4. Count total nodes" << std::endl;
        std::cout << "5. Count leaf nodes" << std::endl;
        std::cout << "6. Search for a student record" << std::endl;
        std::cout << "7. Remove a student record" << std::endl;
        std::cout << "8. Print tree as list (generalized list)" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Student newStudent;
                std::cout << "Enter student number (5 characters): ";
                std::cin >> newStudent.num;
                std::cout << "Enter student grade: ";
                std::cin >> newStudent.grade;
                root = insert(root, newStudent);
                break;
            }
            case 2: {
                std::cout << "Inorder Traversal:" << std::endl;
                inorderTraversal(root);
                std::cout << std::endl;
                break;
            }
            case 3: {
                std::cout << "Tree Depth: " << depth(root) << std::endl;
                break;
            }
            case 4: {
                std::cout << "Total Nodes: " << countNodes(root) << std::endl;
                break;
            }
            case 5: {
                std::cout << "Leaf Nodes: " << countLeaves(root) << std::endl;
                break;
            }
            case 6: {
                char searchNum[6];
                std::cout << "Enter student number to search: ";
                std::cin >> searchNum;
                if (search(root, searchNum)) {
                    std::cout << "Student record found." << std::endl;
                } else {
                    std::cout << "Student record not found." << std::endl;
                }
                break;
            }
            case 7: {
                char removeNum[6];
                std::cout << "Enter student number to remove: ";
                std::cin >> removeNum;
                root = remove(root, removeNum);
                break;
            }
            case 8: {
                std::cout << "Binary Search Tree as Generalized List:" << std::endl;
                printTreeAsList(root);
                std::cout << std::endl;
                break;
            }
            case 9: {
                std::cout << "Exiting program." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            }
        }
    } while (choice != 9);

    return 0;
}

// 插入节点
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

// 中序遍历
void inorderTraversal(BSTNode *root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        std::cout << "Student Number: " << root->data.num << ", Grade: " << root->data.grade << std::endl;
        inorderTraversal(root->rchild);
    }
}

// 计算树的深度
int depth(BSTNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->rchild);
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

// 计算树的总节点数
int countNodes(BSTNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return countNodes(root->left) + countNodes(root->rchild) + 1;
    }
}

// 计算树的叶子节点数
int countLeaves(BSTNode *root) {
    if (root == nullptr) {
        return 0;
    } else if (root->left == nullptr && root->rchild == nullptr) {
        return 1;
    } else {
        return countLeaves(root->left) + countLeaves(root->rchild);
    }
}

// 查找学生记录
bool search(BSTNode *root, const char *num) {
    if (root == nullptr) {
        return false;
    } else if (std::strcmp(root->data.num, num) == 0) {
        return true;
    } else if (std::strcmp(num, root->data.num) < 0) {
        return search(root->left, num);
    } else {
        return search(root->rchild, num);
    }
}

// 删除学生记录
BSTNode *remove(BSTNode *root, const char *num) {
    if (root == nullptr) {
        return nullptr;
    } else if (std::strcmp(num, root->data.num) < 0) {
        root->left = remove(root->left, num);
    } else if (std::strcmp(num, root->data.num) > 0) {
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

// 广义表形式打印树
void printTreeAsList(BSTNode *root) {
    if (root == nullptr) {
        std::cout << "@";
    } else {
        std::cout << "(";
        std::cout << root->data.num << "," << root->data.grade;
        if (root->left != nullptr || root->rchild != nullptr) {
            std::cout << ",";
            printTreeAsList(root->left);
            std::cout << ",";
            printTreeAsList(root->rchild);
        }
        std::cout << ")";
    }
}
