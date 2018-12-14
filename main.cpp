#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include "encoding.h"
using namespace std;

int main() {
    string filename = "E:\\Programming\\CLion\\HuffmanEncoding\\file_WAP.txt";
    string filename_out = "E:\\Programming\\CLion\\HuffmanEncoding\\file_WAP_out.txt";
    huffman_encode(filename, filename_out);
    exit(0);
}