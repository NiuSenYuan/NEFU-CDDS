#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};
struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (auto& entry : frequencies) {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }
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
string encodeMessage(const string& message, const unordered_map<char, string>& huffmanCodes) {
    string encodedMessage = "";
    for (char c : message) {
        encodedMessage += huffmanCodes[c];
    }
    return encodedMessage;
}
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

void printHuffmanTree(HuffmanNode* root, int space = 0) {
    if (root == nullptr) {
        return;
    }

    const int spaces = 5;
    space += spaces;

    printHuffmanTree(root->right, space);

    cout << endl;
    for (int i = spaces; i < space; i++) {
        cout << " ";
    }
    cout << root->data << "(" << root->frequency << ")" << endl;

    printHuffmanTree(root->left, space);
}
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

int main() {
    string message = "hello world";
    unordered_map<char, int> frequencies;
    for (char c : message) {
        frequencies[c]++;
    }
    HuffmanNode* huffmanTree = buildHuffmanTree(frequencies);
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);
    cout << "Huffman Tree:" << endl;
    printHuffmanTree(huffmanTree);
    string encodedMessage = encodeMessage(message, huffmanCodes);
    cout << "Encoded Message: " << encodedMessage << endl;
    ofstream outFile("hfmTree.txt");
    storeHuffmanTree(huffmanTree, outFile);
    outFile.close();
    ifstream inFile("hfmTree.txt");
    HuffmanNode* readHuffmanTree = readHuffmanTree(inFile);
    inFile.close();
    string decodedMessage = decodeMessage(readHuffmanTree, encodedMessage);
    cout << "Decoded Message: " << decodedMessage << endl;
    return 0;
}
