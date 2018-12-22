//
// Created by Alberto on 12/16/2018.
//

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "decoding.h"
#include "encoding.h"
using namespace std;

vector<int> parse_header(string header_string) {
    vector<int> freq_vector(256);
    istringstream iss(header_string);
    vector<string> header_vector{istream_iterator<string>{iss}, istream_iterator<string>{}};
    for (int i = 0; i < header_vector.size(); i+=2) {
        freq_vector[stoi(header_vector[i])] += stoi(header_vector[i+1]);
    }
    return freq_vector;
}

vector<string> file_string(string filename) {
    ifstream file_in;
    vector<string> file_vector(2);
    file_in.open(filename.c_str());
    string line;
    int index = 0;
    while (getline(file_in, line)) {
        file_vector[index] = line;
        index++;
    }
    return file_vector;
}

void huffman_decode(string file_in, string file_out) {
    ifstream input_file;
    try {
        input_file.open(file_in.c_str());
    } catch (std::exception &ex) {
        std::cout << "File does not exist" << endl;
    }
    ofstream output_file;
    output_file.open(file_out.c_str());
    if (!empty_file(input_file)) {
        vector<string> file_vector = file_string(file_in);
        if (file_vector[1] != "") {
            string code = file_vector[1];
            vector<int> character_vector = parse_header(file_vector[0]);
            HuffmanNode *root = create_huff_tree(character_vector);
            HuffmanNode *current_node = root;
            for (int i = 0; i < code.length(); i++) {
                if (code[i] == 48) {
                    current_node = current_node->left;
                } else {
                    current_node = current_node->right;
                }
                if (current_node->left == nullptr and current_node->right == nullptr) {
                    output_file << (char)current_node->character;
                    current_node = root;
                }
            }
        } else if (file_vector[1] == "") {
            istringstream iss(file_vector[0]);
            vector<string> header_vector{istream_iterator<string>{iss}, istream_iterator<string>{}};
            int character_value = stoi(header_vector[0]);
            for (int i = 0; i < stoi(header_vector[1]); i++) {
                output_file << (char)character_value;
            }
        }
    }
    input_file.close();
    output_file.close();
}
