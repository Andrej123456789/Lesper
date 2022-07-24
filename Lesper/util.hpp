#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Eval
{
    public:
        Eval(std::string expr, std::vector<std::string> parentheses, std::vector<std::string> numbers, std::vector<std::string> operators);
        ~Eval();

        std::string ret = "";

    private:
        void Parentheses(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators);
        void Operators(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators);
        void Numbers(std::string expr, std::vector<std::string> numbers);
};

std::string lower(std::string str);
bool containsSomething(std::string str, std::vector<std::string> vec);
bool containsSpecificOperators(std::string str, int id);
bool evaluateTokens(std::vector<std::string> tokens, int i, std::string str, int substr);