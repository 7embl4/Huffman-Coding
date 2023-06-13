#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

struct node {
	char ch;
	int freq;
	node *left, *right;
};

// function of making node
node* makeNode(char ch, int freq, node* left, node* right) {
	node* newNode = new node();

	newNode->ch = ch;
	newNode->freq = freq;
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

struct comp {
	bool operator()(node* a, node* b) {
		return a->freq > b->freq;
	}
};

// encode function
void encode(node* root, string str, map<char, string>& huffmanCode) {
	if (root == nullptr)
		return;

	if (!root->left && !root->right)
		huffmanCode[root->ch] = str;

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// decode function
void decode(node* root, int& index, string str) {
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

int main() {
	
	string str;
	getline(cin, str);

	// extract chars and their number from the string
	map<char, int> tokens;
	for (auto s : str) {
		tokens[s]++;
	}

	// making priority queue of nodes
	priority_queue<node*, vector<node*>, comp> pq;
	for (auto pair : tokens) {
		pq.push(makeNode(pair.first, pair.second, nullptr, nullptr));
	}
	
	while (pq.size() != 1) {

		node* l = pq.top(); pq.pop();
		node* r = pq.top(); pq.pop();

		int sum = l->freq + r->freq;
		pq.push(makeNode('\0', sum, l, r));
	}

	// creating Huffman code 
	node* root = pq.top();
	map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	string code;

	cout << "The Huffman code is: " << endl;
	for (auto pair : huffmanCode) {
		cout << pair.first << ' ' << pair.second << endl;
	}

	for (auto letter : str) {
		code += huffmanCode[letter];
	}
	cout << "Encoded string: " << code << endl;

	// decoding Huffman code
	int index = -1;
	cout << "Decoded string: ";
	while (index < ((int)code.size() - 1)) {
		decode(root, index, code);
	}

	return 0;
}