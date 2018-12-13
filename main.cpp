#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include "encoding.h"
using namespace std;

int main() {
    string filename = "E:\\Programming\\CLion\\HuffmanEncoding\\file1.txt";
    vector<int> c_list = cnt_freq(filename);
    for (int i = 0; i < 256; i++) {
        if (c_list[i] != 0) {
            cout << c_list[i] << " ";
        }
    }
    exit(0);
}