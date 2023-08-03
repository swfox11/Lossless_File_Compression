# Lossless_File_Compression
Uses Huffman Coding algorithm to compress text files in binary files and decompresses the binary file back to the original text file.
The Encoding program takes a text file as input and generates a compressed binary file(along with another binary file "vector_data.bin" which stores the necessary data to regenerate the Huffman tree in future when we will be decoding the text) as output which can be conveniently stored using less space.
The Decoding program takes the compressed binary file as input to generate back the original text file with 0% loss in data (with the help of that "vector_data.bin" file).

