#include <bits/stdc++.h>
#include "encode.h"
#include "serializer/serialize.h"
#include <map>

Node::Node():c(""), occurence(0), left(nullptr), right(nullptr){}
Node::Node(string c, int cnt):c(c), occurence(cnt),left(nullptr), right(nullptr){}
Node::Node(string c, int o, Node* left, Node* right):c(c), occurence(o),left(left), right(right){}

namespace huffman_decoder{
    void trav(Node* root, string s, map<string, string>&mp){
        if(root == nullptr) return;
        if((root->c).length() == 1){
            mp[root->c] = s;
        }
        // cout<<root->c<<" "<<root->occurence<<endl;
        trav(root->left, s+"0", mp);
        trav(root->right,s+"1", mp);
        
    }

    map<string,int> calc_frequency(string s){
        map<string, int>freq;
        for(char it: s){
            string it1 = "";
            it1 += it;
            freq[it1]++;
        }
        return freq;
    }

    map<string,string> getHuffmanTable(string s)
    {
        map<string,int>freq = calc_frequency(s);
        priority_queue<pair<int,Node*>, vector<pair<int,Node*>>, greater<pair<int,Node*>>>pq;
        for(auto it: freq){
            pq.push({it.second, new Node(it.first, it.second)});
        }

        while(pq.size() > 1)
        {
            Node* left = nullptr;
            Node* right = nullptr;
            int lCnt = 0,rCnt = 0; 
            string lStr = "", rStr = "";
            if(pq.size() > 0){
                left = pq.top().second;
                lCnt = pq.top().first;
                lStr = pq.top().second->c;
                pq.pop();
            }
            if(pq.size() > 0){
                right = pq.top().second;
                rCnt = pq.top().first;
                rStr = pq.top().second->c;
                pq.pop();
            }
            Node* root = new Node(lStr + rStr ,lCnt + rCnt, left, right);
            pq.push({left -> occurence + right->occurence, root});
        }
        Node* root = pq.top().second;
        map<string,string>mp;
        trav(root,"",mp);
        // for(auto &it: mp){
        //     cout<<it.first<<" "<<it.second<<endl;
        // }
        return mp;
    }

    template<typename K, typename V>mp;
    string decode(,std::string filename){
        map<string,string>table = getHuffmanTable(s);
        map<string, string>out_table = serialize(table, filename + ".bin"); 
        string ret = "";
        for(auto it: out_table){
            cout<<it.first<<" "<<it.second<<endl;
        }

        for(auto it: s){
            string it1 = "";
            it1 += it;
            ret += table[it1];
        }
        return ret;
    }

    bool encodeFile(std::string file_name){
        ifstream inp(file_name);
        size_t map_size = mp.size;
        if(!inp.is_open()){
            std::cerr<<"Error opening file!"<<std::endl;
            return 1;
        }
        
        string line;
        string file_content = "";
        while(getline(inp, line)){
            // std::cout<<line;
            file_content += line;
            file_content += "\n";
        }
        // std::cout<<file_content<<std::endl;
        inp.close();

        string encoded_output = "";
        map<string,string>table = getHuffmanTable(file_content);
        
        for(auto it: file_content){
            string it1 = "";
            it1 += it;
            encoded_output += table[it1];
        }
        // std::cout<<encoded_output<<std::endl;

        ofstream file(fileName + ".hf");
        if(!file.is_open()){
            std::cerr<<"Error in creating file!" << std::endl;
            return 1;
        }

        std::cout<<file_content.length() * 8<<std::endl;
        std::cout<<encoded_output.length()<<std::endl;
        std::cout<<100 - (encoded_output.length() * 100 / (file_content.length() * 8))<<"% compression"<<std::endl;
        file<<encoded_output<<std::endl;

        map<string, string>out_table = serialize(table, fileName + ".bin"); 
        for(auto it: out_table){
            cout<<it.first<<" "<<it.second<<endl;
        }
        
        file.close();
        return 0;
    }
}

int main()
{
    huffmanEncoding::encodeFile("./encode.h");

}


The C++ Standard Library A tutorial and reference by Nicolai M. Josuttis

