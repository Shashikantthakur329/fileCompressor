#include "encode.cpp"
#include "decode.cpp"

int main(int argc, char** argv)
{
    std::string filename = "testDir/img.webp";
    huffmanEncoding::encodeFile("/home/toor/cpp/huffman_encoding/src/"+filename);

    std::cout<<std::endl<<"decoded file: "<<std::endl;
    std::string out = "/home/toor/cpp/huffman_encoding/src/"+filename+".bin";
    huffmanEncoding::decodeFile(out);
}

