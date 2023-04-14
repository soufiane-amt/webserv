#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <zlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];

    // Open the input file in binary mode
    std::ifstream input_file(filename.c_str(), std::ios::binary);
    if (!input_file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    // Create a buffer to hold the compressed data
    const int buffer_size = 1024;
    unsigned char buffer[buffer_size];

    // Initialize the zlib stream for decompression
    z_stream stream;
    std::memset(&stream, 0, sizeof(stream));
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;
    inflateInit2(&stream, 16+MAX_WBITS);

    // Decompress the data in chunks
    std::string output_data;
    int bytes_read = 0;
    while (input_file.read(reinterpret_cast<char*>(buffer), buffer_size)) {
        stream.next_in = buffer;
        stream.avail_in = input_file.gcount();

        // Decompress the input buffer
        do {
            stream.avail_out = buffer_size;
            stream.next_out = buffer;
            inflate(&stream, Z_NO_FLUSH);
            bytes_read = buffer_size - stream.avail_out;

            // Append the decompressed data to the output string
            output_data.append(reinterpret_cast<char*>(buffer), bytes_read);
        } while (stream.avail_out == 0);
    }

    // Finalize the zlib stream
    inflateEnd(&stream);

    // Print the decompressed data
    std::cout << output_data << std::endl;

    return 0;
}

