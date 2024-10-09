#include "serialize.h"
#include <iostream>
#include <fstream>
#include <string>

template<typename K, typename V>
void serialize(std::map<K,V>&mp, std::string filename)
{
    std::ofstream out_stream(filename, std::ios::binary);
    if(!out_stream){
        std::cerr<<"Unable to open file" << " " << filename << std::endl;
        return;
    }
    
    size_t sz = mp.size();
    out_stream.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    
    for(auto &it: mp){
        out_stream.write(reinterpret_cast<const char*>(&it.first), sizeof(it.first));
        out_stream.write(reinterpret_cast<const char*>(&it.second), sizeof(it.second));
    }
    out_stream.close();
    return;
}

template<typename K, typename V>
void derialize(std::map<K,V>mp, std::string filename)
{
    std::ifstream out_stream(filename, std::ios::binary);
    if(!out_stream){
        std::cerr<<"Unable to open file" << " " << filename << std::endl;
        return;
    }
    
    size_t sz = mp.size();
    out_stream.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    
    for(int i = 0; i < sz; i++){
        K key;
        V value;
        out_stream.read(reinterpret_cast<char*>(&key), sizeof(key));
        out_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
        // std::cout<<key<<" "<<value<<" "<<std::endl;
        mp[key] = value;
    }

    out_stream.close();
    return;
}

int main()
{
    std::map<std::string,int>mp;
    mp["a"] = 7;
    mp["c"] = 2;
    mp["b"] = 3;
    mp["y"] = 4;
    
    serialize(mp,std::string("./out.txt"));

    std::map<std::string, int>mp1;

    derialize(mp1, std::string("./out.txt"));
    // for(auto &it: mp1){
    //     std::cout<<it.first<<" "<<it.second<<std::endl;
    // }
    
}

