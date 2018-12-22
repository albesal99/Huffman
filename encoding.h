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
std::vector<HuffmanNode*> create_node_list(std::vector<int>);
struct HuffmanNode* create_huff_tree(std::vector<int>);
void create_codes_helper(HuffmanNode*, std::vector<std::string> &, std::string);
std::vector<std::string> create_codes(HuffmanNode*);
static inline void rtrim (std::string &);
std::string create_header(std::vector<int>);
bool empty_file(std::ifstream&);
void huffman_encode(std::string, std::string);

#endif //HUFFMANENCODING_ENCODING_H
