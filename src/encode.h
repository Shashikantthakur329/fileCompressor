
#ifndef ENCODE_H
#define ENCODE_H
#include <string>
#include <map>
class Node{
    public:
    std::string c;
    int occurence;
    Node *left, *right;
    Node();
    Node(std::string c, int cnt);
    Node(std::string c, int o, Node* left, Node* right);
};

namespace huffmanEncoding{
    std::map<std::string,std::string> getHuffmanTable(std::string s);
    std::string encode(std::string s);
    void trav(Node* root, std::string s, std::map<std::string, std::string>&mp);
    std::map<std::string,int> calc_frequency(std::string s);
}
#endif
