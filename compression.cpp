//
// Created by Alberto on 12/18/2018.
//
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "compression.h"
#include "decoding.h"
using namespace std;

void compress(string file_in, string file_out) {
    ifstream input_file;
    try {
        input_file.open(file_in.c_str());
    } catch (std::exception &ex) {
        std::cout << "File does not exist" << endl;
    }
    vector<string> file_lines = file_string(file_in);
    if (file_lines.size() > 2) {
        exit(0);
    }
    ofstream output_file;
    output_file.open(file_out.c_str());
    output_file << file_lines[0] << "\n";
    unsigned char byte = 0;
    int n_bits = 0;
    for (int i = 0; i < file_lines[1].length(); i++) {
        byte <<= 1;
        n_bits++;
        if (file_lines[1][i] == 49) {
            byte += 1;
        }
        if (n_bits == 8) {
            output_file.put(byte);
            byte = 0;
            n_bits = 0;
        }
    }
    if (n_bits < 8) {
        byte |= n_bits;
        output_file.put(byte);
    } else {
        byte |= 1 << n_bits;
        output_file.put(byte);
    }
    input_file.close();
    output_file.close();
}
