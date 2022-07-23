#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>

class Eval
{
    public:
        std::string Parentheses(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators);
        std::string Operators(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators);
        std::string Numbers(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators);

    private:
        std::string ret = "";
};

std::string lower(std::string str);
bool containsSomething(std::string str, std::vector<std::string> vec);
bool containsSpecificOperators(std::string str, int id);
bool evaluateTokens(std::vector<std::string> tokens, int i, std::string str, int substr);

extern Eval eval;