#include "util.hpp"

Eval::Eval(std::string expr, std::vector<std::string> parentheses, std::vector<std::string> numbers, std::vector<std::string> operators)
{
    if (containsSomething(expr, parentheses) && containsSpecificOperators(expr, 1) && containsSomething(expr, numbers))
    {
        Parentheses(expr, numbers, operators);
    }

    else if (containsSpecificOperators(expr, 1) && containsSomething(expr, numbers))
    {
        Operators(expr, numbers, operators);
    }

    else if (containsSomething(expr, numbers))
    {
        Numbers(expr, numbers);
    }

    else
    {
        ret = 0;
        error_state = true;
    }
}

Eval::~Eval()
{
    ret = 0;
    error_state = 1;
}

void Eval::Parentheses(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators)
{
    throw "Not implemented";
}

void Eval::Operators(std::string expr, std::vector<std::string> numbers, std::vector<std::string> operators)
{
    std::map<std::size_t, std::string> data;
    std::vector<float> num;
    std::size_t temp;
    bool contains_additon_and_subtraction = false;
    bool multiple_or_division = false;
    int muls_and_divs = 0;
    float number;

    num.push_back(0);
    for (std::size_t i = 0; i < expr.length(); i++)
    {
        if (containsSomething(expr.substr(i, 1), numbers))
        {
            temp = i;
            while (containsSomething(expr.substr(temp, 1), numbers))
            {
                temp++;
            }

            data.insert
            (
                {
                    temp,
                    expr.substr(temp, temp - i)
                }
            );
            num.push_back(std::stof(expr.substr(i, temp - i)));
        }
    }
    data.erase(std::prev(data.end()));

    for (auto x : data)
    {
        if (x.second == "*" || x.second == "/")
        {
            multiple_or_division = true;
            muls_and_divs++;
        }

        if (x.second == "+" || x.second == "-")
        {
            contains_additon_and_subtraction = true;
        }
    }

    for (std::size_t i = 1; i < num.size(); i++)
    {
        if (num[i] > 9)
        {
            std::vector<float>::iterator a = num.begin();
            a += i * 2;
            num.erase(a);
        }
    }
    std::vector<float>::iterator b = num.begin();
    num.erase(b);

    if (!multiple_or_division && contains_additon_and_subtraction)
    {
        for (auto pos : data)
        {
            switch (expr.at(pos.first))
            {
                case '+':
                    number += std::stof(pos.second);
                    break;

                case '-':
                    number -= std::stof(pos.second);
                    break;
                
                default:
                    break;
            }
        }
    }

    else if (multiple_or_division && !contains_additon_and_subtraction)
    {
        number = num[0];
        for (auto pos : data)
        {
            switch (expr.at(pos.first))
            {
                case '*':
                    number *= std::stof(pos.second);
                    break;

                case '/':
                    number /= std::stof(pos.second);
                    break;
                
                default:
                    break;
            }
        }
    }

    else
    {
        int add_sub_pos, mul_div_pos;
        std::size_t one, two, result;
        std::string temp1, temp2;
        for (auto pos : data)
        {
            if (pos.second == "*" || pos.second == "/")
            {
                mul_div_pos = pos.first;
                switch (expr.at(mul_div_pos))
                {
                    case '*':
                        temp1 = expr.at(mul_div_pos - 1);
                        temp2 = expr.at(mul_div_pos + 1);
                        number = std::stof(temp1) * std::stof(temp2);
                        break;

                    case '/':
                        temp1 = expr.at(mul_div_pos - 1);
                        temp2 = expr.at(mul_div_pos + 1);
                        number = std::stof(temp1) / std::stof(temp2);
                        break;
                    
                    default:
                        break;
                }
                muls_and_divs--;
            }

            else
            {
                if (muls_and_divs == 0)
                {
                    
                }
            }
        }

        for (auto pos : data)
        {
            if (muls_and_divs == 0)
            {
                if (pos.second == "+" || pos.second == "-")
                {
                    add_sub_pos = pos.first;
                    switch (expr.at(add_sub_pos))
                    {
                        case '+':
                            temp1 = expr.at(add_sub_pos - 1);
                            number = std::stof(temp1) + number;
                            break;

                        case '-':
                            temp1 = expr.at(add_sub_pos - 1);
                            temp2 = expr.at(add_sub_pos + 1);
                            number = std::stof(temp1) - number;
                            break;
                        
                        default:
                            break;
                    }
                }
            }
        }
    }

    this->ret = number;
}

void Eval::Numbers(std::string expr, std::vector<std::string> numbers)
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
    
    float number = num[0];
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
    
    (number >= 0) ? this->error_state = true : this->ret = number;
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
        if (str.find("*") || str.find("/")) /* idk why == now works */
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