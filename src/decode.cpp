#include "encode.h"
#include "decode.h"
#include "./serializer/serialize.h"
#include <map>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>


namespace huffmanEncoding{
    void deserialize_map(const std::string& file_name) {
        if(file_name.substr(file_name.size() - 4) != ".bin")
        {
            std::cerr<<"file is not in .bin extension."<<std::endl;
            exit(0);
        }

        std::ifstream in(file_name, std::ios::binary);
        
        if (!in) {
            throw std::runtime_error("Unable to open file for reading");
        }
        
        size_t map_size;
        in.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));  // Read map size
        
        std::map<std::string, std::string> table;
        for (size_t i = 0; i < map_size; ++i) {
            std::string key;
            std::string value;
            key = deserialize_string(in);  // Deserialize key (string)
            value = deserialize_string(in);  // Deserialize value (string)
            table[value] = key;
            // const char *keyc = key.c_str();
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
        in.close();

        ofstream ret(file_name + ".out" ,std::ios::binary);
        if(!ret.is_open()){
            std::cerr<<"Error in opening file ./decoded"<<std::endl; 
        }
        ret<<decoded;
        std::cout<<decoded<<std::endl;
        ret.close();
    }

    void decodeFile(std::string &file_name){        
        // deserialize_map<std::string, std::string>("./test.txt.bin");
        try {
            deserialize_map(file_name);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

// int main() {
//     try {
//         deserialize_map<std::string, std::string>("./test.txt.bin");
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
// }
