
// Function to deserialize a map from a binary file
template<typename K, typename V>
void deserialize_map(std::map<K, V>& map_data) {
    std::ifstream in(file_name, std::ios::binary);
    
    if (!in) {
        throw std::runtime_error("Unable to open file for reading");
    }
    
    size_t map_size;
    in.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));  // Read map size
    
    map<std::string, std::string>
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
            
            map_data[key] = value;
        }

        in.close();
    }
}





