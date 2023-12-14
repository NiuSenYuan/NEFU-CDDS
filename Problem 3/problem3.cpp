#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
#include <fstream>
#include <string>
#include <algorithm>
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
    BSTNode(const ElemType& d)
	{
		data=d;		
		left=nullptr;
		right=nullptr;
	}
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
// 在二叉排序树中查询学生记录
void searchNode(BSTNode* root, const char* targetNum,bool& flag) {
	if(root == nullptr)return;
    if (strcmp(targetNum, root->data.num) == 0) {
        cout<<"该学生成绩为："<<root->data.grade<<endl;
        flag=true;
        return;
    }
    searchNode(root->left, targetNum,flag);
 	searchNode(root->right, targetNum,flag);
}
// 在二叉排序树中找到最小节点
BSTNode* findMin(BSTNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// 在二叉排序树中删除节点
BSTNode* deleteNode(BSTNode* root, const char* targetNum) {
    if (root == nullptr) {
        return nullptr;
    }

    if (strcmp(targetNum, root->data.num) < 0) {
        root->left = deleteNode(root->left, targetNum);
    } else if (strcmp(targetNum, root->data.num) > 0) {
        root->right = deleteNode(root->right, targetNum);
    } else {
        // 找到待删除节点

        if (root->left == nullptr) {
            // 有右子节点或是叶子节点的情况
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            // 有左子节点的情况
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        // 有两个子节点的情况
        BSTNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.num);
    }
    return root;
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
    cout<<"广义表输出二叉排序树："<<endl;
	printBSTasList(root);
    // 求二叉排序树深度
    cout << "二叉排序树深度：" << treeDepth(root) << endl;

    // 求二叉排序树的节点数和叶子节点数
    cout << "二叉排序树节点数：" << nodeCount(root) << endl;
    cout << "二叉排序树叶子节点数：" << leafCount(root) << endl;

    // 向二叉排序树插入一条学生记录
    ElemType newStudent;
    cout << "请输入要插入的学生记录（学号 成绩）：" << endl;
    cin >> newStudent.num >> newStudent.grade;
    root=insert(root, newStudent);
    cout << "中序遍历结果：" << endl;
    inorderTraversal(root);
	//向二叉排序树查询一条学生记录
	bool flag=false;
	cout<<"请输入要查询的学生学号："<<endl;
	cin >> newStudent.num;
	searchNode(root,newStudent.num,flag);
	if(!flag)cout<<"该学生不存在！"<<endl;
	cout<<"请输入要删除的学生学号："<<endl;
	cin >> newStudent.num;
    // 广义表形式输出二叉排序树
    cout << "二叉排序树的广义表形式：" << endl;
    printBSTasList(root);

    return 0;
}
/*
1000 99
1001 98
1002 97
1003 96
1004 95
1005 94
0 0
*/
