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

    num.push_back(0);
    pos.push_back(0);
    for (std::size_t i = 0; i < expr.length(); i++)
    {
        if (containsSomething(expr.substr(i, 1), numbers))
        {
            temp = i;
            while (containsSomething(expr.substr(temp, 1), numbers))
            {
                temp++;
            }
            pos.push_back(temp);
            num.push_back(std::stoi(expr.substr(i, temp - i)));
        }
    }

    for (std::size_t i = 1; i < num.size(); i++)
    {
        if (num[i] > 9)
        {
            std::vector<int>::iterator a = num.begin();
            a += i * 2;
            num.erase(a);

            std::vector<std::size_t>::iterator b = pos.begin();
            b += i * 2;
            pos.erase(b);
        }
    }

    std::vector<int>::iterator c = num.begin();
    num.erase(c);
    std::vector<std::size_t>::iterator d = pos.begin();
    pos.erase(d);
    
    int number = num[0];
    for (std::size_t i = 0; i < pos.size() - 1; i++)
    {
        switch (expr.at(pos[i]))
        {
            case '+':
                number += num[i + 1];
                break;

            case '-':
                number -= num[i + 1];
                break;
            
            default:
                break;
        }
    }
    
    this->ret = std::to_string(number);
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