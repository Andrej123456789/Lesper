#include "util.hpp"

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