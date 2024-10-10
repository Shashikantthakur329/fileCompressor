#include "encode.h"
// #include "./decode.h"
#include "./serializer/serialize.h"
#include <map>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

// Function to deserialize a map from a binary file
template<typename K, typename V>
void deserialize_map(const std::string& file_name) {
    if(file_name.substr(file_name.size() - 4) != ".bin")
    {
        std::cerr<<"file is not in hf encoded format."<<std::endl;
        exit(0);
    }

    std::ifstream in(file_name, std::ios::binary);
    
    if (!in) {
        throw std::runtime_error("Unable to open file for reading");
    }
    
    size_t map_size;
    in.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));  // Read map size
    
    std::map<K, V> table;
    for (size_t i = 0; i < map_size; ++i) {
        K key;
        V value;

        if constexpr (std::is_same<K, std::string>::value) {
            key = deserialize_string(in);  // Deserialize key (string)
        } else {
            in.read(reinterpret_cast<char*>(&key), sizeof(key));  // Deserialize key (non-string)
        }
        
        if constexpr (std::is_same<V, std::string>::value) {
            value = deserialize_string(in);  // Deserialize value (string)
        } else {
            in.read(reinterpret_cast<char*>(&value), sizeof(value));  // Deserialize value (non-string)
        }

        table[value] = key;
        const char *keyc = key.c_str();

    }

    std::string decoded = "";
    size_t len_data;
    in.read(reinterpret_cast<char*>(&len_data), sizeof(len_data));
    string temp = "";
    for(int i = 0; i < len_data; i++){
        char c;
        in.read(reinterpret_cast<char*>(&c), sizeof(c));
        temp += c;
        
        if(table.find(temp) != table.end()){
            decoded += table[temp];
            temp = "";
        }
        
    }
    std::cout<<decoded<<std::endl;

    in.close();
}

int main() {
    try {
        deserialize_map<std::string, std::string>("./test.txt.bin");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
