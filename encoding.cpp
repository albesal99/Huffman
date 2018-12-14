//
// Created by Alberto on 11/5/2018.
//

#include "encoding.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include "assert.h"
using namespace std;

struct HuffmanNode;

HuffmanNode* new_node(int character, int freq) {
    struct HuffmanNode* HuffmanNode = new(struct HuffmanNode);
    HuffmanNode->character = character;
    HuffmanNode->freq = freq;
    HuffmanNode->left = nullptr;
    HuffmanNode->right = nullptr;

    return HuffmanNode;
}

bool comes_before(HuffmanNode *a, HuffmanNode *b) {
    if (a->freq == b->freq) {
        return a->character < b->character;
    } else {
        return a->freq < b->freq;
    }
}

HuffmanNode* combine(HuffmanNode *a, HuffmanNode *b) {
    struct HuffmanNode *node;
    if (a->freq == b->freq) {
        if (comes_before(a, b)) {
            node = new_node(a->character, a->freq + b->freq);
            node->left = a;
            node->right = b;
        } else {
            node = new_node(b->character, a->freq + b->freq);
            node->left = b;
            node->right = a;
        }
    } else {
        if (comes_before(a, b)) {
            if (b->character < a->character) {
                node = new_node(b->character, a->freq + b->freq);
                node->left = a;
                node->right = b;
            } else {
                node = new_node(a->character, a->freq + b->freq);
                node->left = a;
                node->right = b;
            }
        } else {
            if (a->character < b->character) {
                node = new_node(a->character, a->freq + b->freq);
                node->left = b;
                node->right = a;
            } else {
                node = new_node(b->character, a->freq + b->freq);
                node->left = b;
                node->right = a;
            }
        }
    }
    return node;
}

vector<int> cnt_freq(string filename) {
    vector<int> character_vector(256);
    ifstream file_in;
    char character;
    file_in.open(filename.c_str());
    if (!file_in.is_open()) {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    while (file_in >> noskipws >> character) {
        character_vector[character]++;
    }
    file_in.close();
    return character_vector;
}

vector<tuple<int, int>> create_sorted_list(vector<int> freq_list) {
    vector<tuple<int, int>> sorted_freq_list;
    tuple<int, int> freq_tuple;
    int index_of_char = 0;
    for (int freq = 0; freq < freq_list.size(); freq++) {
        if (freq_list[freq] != 0) {
            freq_tuple = make_tuple(freq_list[freq], index_of_char);
            sorted_freq_list.push_back(freq_tuple);
        }
        index_of_char++;
    }
    if (sorted_freq_list.size() > 1) {
        sort(begin(sorted_freq_list), end(sorted_freq_list));
    }
    return sorted_freq_list;
}

vector<HuffmanNode*> create_node_list(vector<int> freq_list) {
    vector<tuple<int, int>> sorted_freq_list = create_sorted_list(freq_list);
    vector<HuffmanNode*> node_vector;
    if (sorted_freq_list.size() > 0) {
        for (int i = 0; i < sorted_freq_list.size(); i++) {
            HuffmanNode *node = new_node(get<1>(sorted_freq_list.at(i)), get<0>(sorted_freq_list.at(i)));
            node_vector.push_back(node);
        }
    }
    return node_vector;
}

HuffmanNode* create_huff_tree(vector<int> freq_list) {
    vector<HuffmanNode*> freq_vector = create_node_list(freq_list);
    while (freq_vector.size() > 1) {
        HuffmanNode *node_a = freq_vector.front();
        freq_vector.erase(freq_vector.begin());
        HuffmanNode *node_b = freq_vector.front();
        freq_vector.erase(freq_vector.begin());
        HuffmanNode *huffman_node = combine(node_a, node_b);
        if (freq_vector.size() == 0) {
            return huffman_node;
        }
        freq_vector.push_back(huffman_node);
        sort(freq_vector.begin(), freq_vector.end(), [](HuffmanNode* a, HuffmanNode* b) {
            if (a->freq != b->freq) {
                return a->freq < b->freq;
            }
            return a->character < b->character;
        });
    }
}

void create_codes_helper(HuffmanNode* node, vector<string> &code_vector, string current_code) {
    if (node == nullptr) {
        return;
    }
    if (node->left == nullptr and node->right == nullptr) {
        code_vector[node->character] += current_code;
        return;
    }
    create_codes_helper(node->left, code_vector, current_code + "0");
    create_codes_helper(node->right, code_vector, current_code + "1");
}

vector<string> create_codes(HuffmanNode* node) {
    vector<string> code_vector(256);
    string current_code = "";
    create_codes_helper(node, code_vector, current_code);
    return code_vector;
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

string create_header(vector<int> freq_list) {
    string output_string = "";
    for (int index = 0; index < freq_list.size(); index++) {
        if (freq_list[index] != 0) {
            string frequency = to_string(freq_list[index]);
            output_string += to_string(index) + " " + frequency + " ";
        }
    }
    rtrim(output_string);
    return output_string;
}

void huffman_encode(string file_in, string file_out) {
    ifstream input_file;
    try {
        input_file.open(file_in.c_str());
    } catch (std::exception &ex) {
        std::cout << "File does not exist" << endl;
    }
    ofstream output_file;
    output_file.open(file_out.c_str());
    vector<int> character_vector = cnt_freq(file_in);
    HuffmanNode *huffman_tree = create_huff_tree(character_vector);
    vector<string> codes = create_codes(huffman_tree);
    string header = create_header(character_vector);
    int header_space_count = 0;
    for (int i = 0; i < header.length(); i++) {
        if (header[i] == 32) {
            header_space_count++;
        }
    }
    if (header_space_count > 1) {
        header += "\n";
    }
    output_file << header;
    if (!input_file.is_open()) {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    char character;
    while (input_file >> noskipws >> character) {
        output_file << codes[character];
    }
    input_file.close();
    output_file.close();
}
