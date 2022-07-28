#pragma once

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>

#include "util.hpp"

static std::vector<std::string> tokens;
static std::vector<std::string> num_stack;
static std::vector<std::string> numbers = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static std::vector<std::string> operators = {"+", "-", "*", "/", "%"};
static std::vector<std::string> parentheses = {"(", ")"};

static std::map<std::string, std::string> symbols;

struct keywords
{
    std::string print = "PRINT";
    std::string variable = "$";
};

std::string open_file(std::string filename);
void lex(std::string filecontents, struct keywords* k);
float evalExpression(std::string expr);
void print(std::string str);
void assign(std::string varname, std::string varvalue);
void parse();
void run(std::string path);