#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "util.hpp"

static std::vector<std::string> tokens;
static std::vector<std::string> num_stack;
static std::vector<std::string> numbers = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static std::vector<std::string> operators = {"+", "-", "*", "/", "%"};
static std::vector<std::string> parentheses = {"(", ")"};

struct keywords
{
    std::string print = "PRINT";
};

std::string open_file(std::string filename);
void lex(std::string filecontents, struct keywords* k);
std::string evalExpression(std::string expr);
void print(std::string str);
void parse();
void run(std::string path);