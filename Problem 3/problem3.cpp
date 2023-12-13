#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

// 定义学生记录类型
struct Student {
    char num[6];   // 学号
    int grade;      // 成绩
};

// 定义二叉排序树节点值的类型为学生记录类型
typedef Student ElemType;

// 定义二叉排序树的节点类型
struct BSTNode {
    ElemType data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const ElemType& d) : data(d), left(nullptr), right(nullptr) {}
};

// 插入节点到二叉排序树
BSTNode* insert(BSTNode* root, const ElemType& value) {
    if (root == nullptr) {
        return new BSTNode(value);
    }

    if (value.grade < root->data.grade) {
        root->left = insert(root->left, value);
    } else if (value.grade > root->data.grade) {
        root->right = insert(root->right, value);
    }

    return root;
}

// 中序遍历二叉排序树
void inorderTraversal(BSTNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "学号: " << root->data.num << " 成绩: " << root->data.grade << endl;
        inorderTraversal(root->right);
    }
}

// 求二叉排序树深度
int treeDepth(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = treeDepth(root->left);
    int rightDepth = treeDepth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

// 求二叉排序树的节点数
int nodeCount(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }

    return nodeCount(root->left) + nodeCount(root->right) + 1;
}

// 求二叉排序树的叶子节点数
int leafCount(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }

    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

    return leafCount(root->left) + leafCount(root->right);
}

// 从文件读取学生记录建立二叉排序树
BSTNode* buildBSTFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "无法打开文件：" << filename << endl;
        exit(EXIT_FAILURE);
    }

    BSTNode* root = nullptr;
    ElemType student;

    while (inFile >> student.num >> student.grade) {
        root = insert(root, student);
    }

    inFile.close();
    return root;
}

// 广义表形式输出二叉排序树
void printBSTasList(BSTNode* root) {
    if (root == nullptr) {
        cout << "()";
        return;
    }

    cout << "(";
    cout << root->data.num << " " << root->data.grade << " ";
    printBSTasList(root->left);
    cout << " ";
    printBSTasList(root->right);
    cout << ")";
}

int main() {
    BSTNode* root = nullptr;

    // 从键盘输入一组学生记录建立二叉排序树
    cout << "请输入学生记录，学号和成绩，以0 0结束：" << endl;
    ElemType student;
    while (cin >> student.num >> student.grade && (student.num[0] != '0' || student.grade != 0)) {
        root = insert(root, student);
    }

    // 中序遍历二叉排序树
    cout << "中序遍历结果：" << endl;
    inorderTraversal(root);

    // 求二叉排序树深度
    cout << "二叉排序树深度：" << treeDepth(root) << endl;

    // 求二叉排序树的节点数和叶子节点数
    cout << "二叉排序树节点数：" << nodeCount(root) << endl;
    cout << "二叉排序树叶子节点数：" << leafCount(root) << endl;

    // 向二叉排序树插入一条学生记录
    ElemType newStudent;
    cout << "请输入要插入的学生记录（学号 成绩）：" << endl;
    cin >> newStudent.num >> newStudent.grade;
    root = insert(root, newStudent);

    // 从文件中读取学生记录建立二叉排序树
    root = buildBSTFromFile("students.txt");

    // 广义表形式输出二叉排序树
    cout << "二叉排序树的广义表形式：" << endl;
    printBSTasList(root);

    return 0;
}
