#include "util.hpp"

std::string Eval::Parentheses(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators)
{
    throw "Not implemented";
}

std::string Eval::Operators(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators)
{
    throw "Not implemented";
}

std::string Eval::Numbers(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators)
{
    std::vector<std::size_t> pos;
    std::vector<int> num;
    std::size_t temp;

    for (std::size_t i = 0; i < expr.size(); i++)
    {
        temp = expr.find("+");
        if (temp != std::string::npos)
        {
            pos.push_back(temp);
        }

        temp = expr.find("-");
        if (temp != std::string::npos)
        {
            pos.push_back(temp);
        }

        else
        {
            throw "Error: No operators found";
        }
    }
    pos.pop_back();
    pos.push_back(expr.length());

    num.push_back(stoi(expr.substr(0, pos[0])));
    num.push_back(stoi(expr.substr(pos[0] + 1, pos[1])));

    for (std::size_t i = 0; i < num.size(); i+=2)
    {
        switch (expr.at(pos[0]))
        {
            case '+':
                ret = std::to_string(num[i] + num[i + 1]);
                break;

            case '-':
                ret = std::to_string(num[i] - num[i + 1]);
                break;
            
            default:
                break;
        }
    }

    return ret;
}

std::string lower(std::string str)
{
    std::for_each(str.begin(), str.end(), [](char & c) 
    {
        c = ::tolower(c);
    });

    return str;
}

bool containsSomething(std::string str, std::vector<std::string> vec)
{
    for (auto x : vec)
    {
        if (str.find(x) != std::string::npos)
        {
            return true;
        }
    }

    return false;
}

bool containsSpecificOperators(std::string str, int id)
{
    if (id == 0) /* (+, -) */
    {
        if (str.find("+") || str.find("-") && !str.find("*") && !str.find("/"))
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    else if (id == 1) /* (*, /) */
    {
        if (!str.find("*") || !str.find("/")) /* idk why != works */
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    else
    {
        throw "Invalid id!";
        return false;
    }
}

bool evaluateTokens(std::vector<std::string> tokens, int i, std::string str, int substr)
{
    std::string temp = tokens[i] + " " + tokens[i + 1].substr(0, substr);

    if (temp == str)
    {
        return true;
    }

    else
    {
        return false;
    }
}