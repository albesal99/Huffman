//
// Created by Alberto on 11/5/2018.
//
#include <string>
#include <vector>
#include <tuple>

#ifndef HUFFMANENCODING_ENCODING_H
#define HUFFMANENCODING_ENCODING_H


class encoding {
};
struct HuffmanNode {
    int character;
    int freq;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
};
bool comes_before(HuffmanNode*, HuffmanNode*);
struct HuffmanNode* new_node(int, int);
struct HuffmanNode* combine(HuffmanNode*, HuffmanNode*);
std::vector<int> cnt_freq(std::string filename);
std::vector<std::tuple<int, int>> create_sorted_list(std::vector<int>);
std::vector<HuffmanNode*> create_node_list(std::vector<std::tuple<int, int>>);
struct HuffmanNode* create_huff_tree(std::vector<int>);

#endif //HUFFMANENCODING_ENCODING_H
