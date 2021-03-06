//
// Created by njohnson on 6/14/21.
//

#ifndef TEC_FS_HUFFMANCOMPRESSION_H
#define TEC_FS_HUFFMANCOMPRESSION_H
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include "../../../lib/DataStructures/SimplyList.h"
#include "../Objects/Huffman_pair.h"
using namespace std;

class HuffmanCompression {
public:
    struct Node{
        char ch;
        int freq;
        Node *left, *right;
    };
    // Function to allocate a new tree node
    static Node* getNode(char ch, int freq, Node* left, Node* right)
    {
        Node* node = new Node();

        node->ch = ch;
        node->freq = freq;
        node->left = left;
        node->right = right;

        return node;
    }

// Comparison object to be used to order the heap
    struct comp
    {
        bool operator()(Node* l, Node* r)
        {
            // highest priority item has lowest frequency
            return l->freq > r->freq;
        }
    };

// traverse the Huffman Tree and store Huffman Codes
// in a map.
    static void encode(Node* root, const string& str,
                unordered_map<char, string> &huffmanCode)
    {
        if (root == nullptr)
            return;

        // found a leaf node
        if (!root->left && !root->right) {
            huffmanCode[root->ch] = str;
        }

        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);
    }

// traverse the Huffman Tree and decode the encoded string
    static void decode(Node* root, int &index, string str)
    {
        if (root == nullptr) {
            return;
        }

        // found a leaf node
        if (!root->left && !root->right)
        {
            cout << root->ch;
            return;
        }

        index++;

        if (str[index] =='0')
            decode(root->left, index, str);
        else
            decode(root->right, index, str);
    }

// Builds Huffman Tree and decode given input text
    static pair<string,SimplyLinkedList<Huffman_pair*>*> buildHuffmanTree(const string& text)
    {
        // count frequency of appearance of each character
        // and store it in a map
        unordered_map<char, int> freq;
        for (char ch: text) {
            freq[ch]++;
        }

        // Create a priority queue to store live nodes of
        // Huffman tree;
        priority_queue<Node*, vector<Node*>, comp> pq;

        // Create a leaf node for each character and add it
        // to the priority queue.
        for (auto pair: freq) {
            pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
        }

        // do till there is more than one node in the queue
        while (pq.size() != 1)
        {
            // Remove the two nodes of highest priority
            // (lowest frequency) from the queue
            Node *left = pq.top(); pq.pop();
            Node *right = pq.top();	pq.pop();

            // Create a new internal node with these two nodes
            // as children and with frequency equal to the sum
            // of the two nodes' frequencies. Add the new node
            // to the priority queue.
            int sum = left->freq + right->freq;
            pq.push(getNode('\0', sum, left, right));
        }

        // root stores pointer to root of Huffman Tree
        Node* root = pq.top();

        // traverse the Huffman Tree and store Huffman Codes
        // in a map. Also prints them
        unordered_map<char, string> huffmanCode;
        encode(root, "", huffmanCode);

        cout << "Huffman Codes are :\n" << '\n';
        auto huffman_result = new SimplyLinkedList<Huffman_pair*>();

        for (const auto& pair: huffmanCode) {
            cout << pair.first << " " << pair.second << '\n';
            auto new_pair = new Huffman_pair();
            new_pair->setCH(pair.first);
            new_pair->setCode(pair.second);
            huffman_result->append(new_pair);
        }

        cout << "\nOriginal string was :\n" << text << '\n';

        // print encoded string
        string str;
        for (char ch: text) {
            str += huffmanCode[ch];
        }

        cout << "\nEncoded string is :\n" << str << '\n';

        // traverse the Huffman Tree again and this time
        // decode the encoded string
        int index = -1;
        cout << "\nDecoded string is: \n";
        while (index < (int)str.size() - 2) {
            decode(root, index, str);
        }
        pair<string,SimplyLinkedList<Huffman_pair*>*> result;
        result.first = str;
        result.second = huffman_result;

        return result;
    }

    static string Decode_Huffman(string str,SimplyLinkedList<Huffman_pair*>* huffman_list ){

        vector<char> characters;
        vector<string> scripts;
        string result , curr;
        int max_chars = 0;

        for (int i = 0; i < huffman_list->getLen(); ++i) {
            characters.push_back(huffman_list->get(i)->getCH());
            scripts.push_back(huffman_list->get(i)->getCode());
        }

        while(max_chars < str.size()){
            curr.push_back(str[max_chars]);
            if(isChar(scripts,curr)){

                result.push_back(characters[getKey(scripts,curr)]);
                curr.clear();

            }
            max_chars++;
        }
        return result;
    }

    static bool isChar(vector<string> scripts , string key){

        for (int i = 0; i < scripts.size(); ++i) {
            if(scripts[i] == key){
                return true;
            }
        }
    }

    static int getKey(vector<string> scripts , string pos){

        for (int i = 0; i < scripts.size(); ++i) {
            if (scripts[i] == pos) {
                return i;
            }
        }
    }
};


#endif //TEC_FS_HUFFMANCOMPRESSION_H
