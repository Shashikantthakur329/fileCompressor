#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

// Structure representing the ZIP local file header
// #pragma pack(push, 1)  // Ensure there is no padding between struct members
struct ZipLocalFileHeader {
    uint32_t signature;           // Signature: 0x04034b50 (little-endian)
    uint16_t version;             // Version needed to extract
    uint16_t flags;               // General purpose bit flags
    uint16_t compressionMethod;   // Compression method
    uint32_t modTime;             // File modification time (MS-DOS format)
    uint32_t modDate;             // File modification date (MS-DOS format)
    uint32_t crc32;               // CRC-32 checksum
    uint32_t compressedSize;      // Compressed size
    uint32_t uncompressedSize;    // Uncompressed size
    uint16_t fileNameLength;      // Length of the file name
    uint16_t extraFieldLength;    // Length of the extra field
};
// #pragma pack(pop)  // Restore original struct padding



int main()
{
    ZipLocalFileHeader header;
    header.signature = 0x78563412;
    header.version = 7;
    header.flags = 0;
    header.compressionMethod = 0;
    header.modTime = 0;
    header.modTime = 0;
    header.crc32 = 0;
    header.compressedSize = 7;
    header.uncompressedSize = 7;
    header.fileNameLength= 7;
    header.extraFieldLength = 7;
    
    ofstream out("./file1.txt", std::ios::binary);
    out.write(reinterpret_cast<char*>(&header), sizeof(header));
    out.close();
    return 0;
}