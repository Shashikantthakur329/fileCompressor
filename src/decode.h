#ifndef INCLUDE_DECODE
#define INCLUDE_DECODE

#include <bits/stdc++.h>
// Function to deserialize a map from a binary file
namespace huffmanEncoding{
    // template<typename K, typename V>
    void deserialize_map(const std::string& file_name);

    void decodeFile(std::string &file_name);
}
// #include "./decode.cpp"
#endif