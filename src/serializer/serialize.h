#ifndef SERIALIZE_H
#define SERIALIZE_H

//template<typename K, typename V>
//std::map<K,V> serialize(std::map<K,V>&mp, std::string filename);

#include <iostream>
#include <fstream>
#include <map>
#include <string>
// #include "serialize.h"
using namespace std;

// Function to serialize a string
void serialize_string(const std::string& str, std::ofstream& out) {
    size_t length = str.size();
    out.write(reinterpret_cast<const char*>(&length), sizeof(length));  // Write string length
    out.write(str.data(), length);  // Write string characters
}

// Function to deserialize a string
std::string deserialize_string(std::ifstream& in) {
    size_t length;
    in.read(reinterpret_cast<char*>(&length), sizeof(length));  // Read string length
    std::string str(length, ' ');  // Allocate space for the string
    in.read(&str[0], length);  // Read string characters
    return str;
}

// Function to serialize a map to a binary file
template<typename K, typename V>
void serialize_map(const std::map<K, V>& map_data, const std::string& file_name) {
    std::ofstream out(file_name, std::ios::binary);
    
    if (!out) {
        throw std::runtime_error("Unable to open file for writing");
    }
    
    size_t map_size = map_data.size();
    out.write(reinterpret_cast<const char*>(&map_size), sizeof(map_size));  // Write map size
    
    for (const auto& pair : map_data) {
        if constexpr (std::is_same<K, std::string>::value) {
            serialize_string(pair.first, out);  // Serialize key (string)
        } else {
            out.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));  // Serialize key (non-string)
        }

        if constexpr (std::is_same<V, std::string>::value) {
            serialize_string(pair.second, out);  // Serialize value (string)
        } else {
            out.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));  // Serialize value (non-string)
        }
    }

    out.close();
}

// Function to deserialize a map from a binary file
template<typename K, typename V>
void deserialize_map(std::map<K, V>& map_data, const std::string& file_name) {
    std::ifstream in(file_name, std::ios::binary);
    
    if (!in) {
        throw std::runtime_error("Unable to open file for reading");
    }
    
    size_t map_size;
    in.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));  // Read map size
    
    map_data.clear();
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

        map_data[key] = value;
    }

    in.close();
}


template<typename K, typename V>
std::map<K,V> serialize(map<K,V>&mp, std::string filename) {
    // Example map to serialize

    // Serialize the map to a binary file
    serialize_map(mp, filename);
 
    std::map<std::string, std::string> out_map;
    deserialize_map(out_map, filename);

    return out_map;
}


#endif