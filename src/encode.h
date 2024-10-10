#ifndef INCLUDE_ENCODE
#define INCLUDE_ENCODE
#include <iostream>
#include <string>
#include <map>
// #include<
class Node{
public:
    std::string c;
    int occurence;
    Node* left;
    Node* right; 
    Node();
    Node(std::string c, int o);
    Node(std::string c, int o, Node* left, Node* right);
};

namespace huffmanEncoding{
    void trav(Node* root, std::string s, std::map<std::string, std::string>&mp);
    std::map<std::string,int> calc_frequency(std::string s);
    std::map<std::string,std::string> getHuffmanTable(std::string s);
    std::string encode(std::string s,std::string filename);
    bool encodeFile(std::string fileName);
}

#endif