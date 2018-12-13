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
#include <cctype>
using namespace std;

struct HuffmanNode;

struct HuffmanNode* new_node(int character, int freq) {
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

struct HuffmanNode* combine(HuffmanNode *a, HuffmanNode *b) {
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
    return character_vector;
}

std::vector<std::tuple<int, int>> create_sorted_list(std::vector<int> freq_list) {
    
}
