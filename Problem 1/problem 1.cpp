#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
// 定义哈夫曼树结点的结构
struct HuffmanNode {
    char data;          //节点数据
    int frequency;      //节点权值
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char d, int freq)
	{
		data=d;
		frequency=freq;
		left=nullptr;
		right=nullptr;
	}
	~HuffmanNode()
	{
		data=0;
		frequency=0;
		left=nullptr;
		right=nullptr;
	}
};
// 用于优先队列的比较函数
struct CompareNodes {
    bool operator()(HuffmanNode* p1, HuffmanNode* p2) {
        return p1->frequency > p2->frequency;
    }
};
// 建立哈夫曼树的函数
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    // 为每个字符创建一个结点并将其加入优先队列
    for (auto& note : frequencies) {
        pq.push(new HuffmanNode(note.first, note.second));
    }
    // 通过组合具有最低频率的结点来建立哈夫曼树
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        HuffmanNode* combined = new HuffmanNode('$', left->frequency + right->frequency);
        combined->left = left;
        combined->right = right;
        pq.push(combined);
    }
    return pq.top();
}
// 生成哈夫曼编码并存储在map中
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }
    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}
// 使用哈夫曼编码对消息进行编码
string encodeMessage(const string& message, const unordered_map<char, string>& huffmanCodes) {
    string encodedMessage = "";
    for (char c : message) {
        encodedMessage += huffmanCodes.at(c);
    }
    return encodedMessage;
}
// 使用哈夫曼树对消息进行解码
string decodeMessage(HuffmanNode* root, const string& encodedMessage) {
    string decodedMessage = "";
    HuffmanNode* current = root;
    for (char bit : encodedMessage) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            decodedMessage += current->data;
            current = root;
        }
    }
    return decodedMessage;
}
// 以树形格式打印哈夫曼树-中序遍历 
void printHuffmanTree(HuffmanNode* root, int space = 0) {
    if (root == nullptr) {
        return;
    }
    int spaces = 5;
    space += spaces;
    printHuffmanTree(root->right, space);
    cout << endl;
    for (int i = spaces; i < space; i++) {
        cout << " ";
    }
    cout << root->data << "(" << root->frequency << ")" << endl;
    printHuffmanTree(root->left, space);
}
// 将哈夫曼树存储到文件
void storeHuffmanTree(HuffmanNode* root, ofstream& outFile) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        outFile << 'L' << root->data;
    } else {
        outFile << 'I';
        storeHuffmanTree(root->left, outFile);
        storeHuffmanTree(root->right, outFile);
    }
}
// 从文件中读取哈夫曼树
HuffmanNode* readHuffmanTree(ifstream& inFile) {
    char type;
    inFile >> type;
    HuffmanNode* root = new HuffmanNode(' ', 0);
    if (type == 'L') {
        inFile >> root->data;
    } else {
        root->left = readHuffmanTree(inFile);
        root->right = readHuffmanTree(inFile);
    }
    return root;
}
int main() 
{
    unordered_map<char, int> frequencies;
    // 输入字符集的大小
    int n;
    cout << "请输入字符集的大小：";
    cin >> n;
    // 输入字符和对应的权值
    cout << "请依次输入字符和对应的权值：" << endl;
    for (int i = 0; i < n; i++) {
        char character;
        int frequency;
        cin >> character >> frequency;
        frequencies[character] = frequency;
    }
    // 构建哈夫曼树
    HuffmanNode* huffmanTree = buildHuffmanTree(frequencies);
    // 生成哈夫曼编码
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);
    // 打印哈夫曼树
    cout << "哈夫曼树：" << endl;
    printHuffmanTree(huffmanTree);
    // 将哈夫曼树存储到文件中
    ofstream treecode("huffmanCodes.txt");
    for(auto it:huffmanCodes) treecode<<it.first<<":"<<it.second<<endl;
    ofstream treeFile("huffmanTree.txt");
    storeHuffmanTree(huffmanTree, treeFile);
    treeFile.close();
    // 读取哈夫曼树
    ifstream inFile("huffmanTree.txt");
    HuffmanNode* readTree = readHuffmanTree(inFile);
    inFile.close();
    // 测试编码和解码
    string message;
    cout << "\n请输入要编码的消息：";
    cin >> message;
    string encodedMessage = encodeMessage(message, huffmanCodes);
    cout << "编码后的消息：" << encodedMessage << endl;
    string decodedMessage = decodeMessage(readTree, encodedMessage);
    cout << "解码后的消息：" << decodedMessage << endl;
    return 0;
}
