#include "util.hpp"

Eval::Eval(std::string expr, std::vector<std::string> parentheses, std::vector<std::string> numbers)
{
    if (containsSomething(expr, parentheses) && containsSpecificOperators(expr, 1) && containsSomething(expr, numbers))
    {
        ret = Parentheses(expr, numbers);
    }

    else if (containsSpecificOperators(expr, 1) && containsSomething(expr, numbers))
    {
        ret = Operators(expr, numbers);
    }

    else if (containsSomething(expr, numbers))
    {
        ret = Numbers(expr, numbers);
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
}

float Eval::Parentheses(std::string expr, std::vector<std::string> numbers)
{
    std::map<std::size_t, std::string> data;
    std::vector<float> num;
    std::size_t temp;
    bool contains_additon_and_subtraction = false;
    bool multiple_or_division = false;
    bool contains_parentheses = false;
    int muls_and_divs = 0;
    int parentheses = 0;
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

    for (auto y : data)
    {
        int temp_pos;
        std::string temp;
        if (y.second == ")")
        {
            temp_pos = y.first;
            size_t found = expr.find("(");
            if (found != std::string::npos)
            {
                temp = expr.at(found);
                auto data_pos = end(data);
                data.insert
                (
                    {
                        found,
                        temp
                    }
                );
            }
        }
    }

    for (auto x : data)
    {
        if (x.second == "(" || x.second == ")")
        {
            contains_parentheses = true;
            parentheses++;
        }

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

    if (!contains_parentheses && !multiple_or_division && contains_additon_and_subtraction)
    {
        return Numbers(expr, numbers);
    }

    else if (multiple_or_division && !contains_parentheses && !contains_additon_and_subtraction)
    {
        return Operators(expr, numbers);
    }

    else if (multiple_or_division && contains_additon_and_subtraction && !contains_parentheses)
    {
        return Operators(expr, numbers);
    }

    else
    {
        std::vector<int> left, right;
        std::vector<float> numbers_in_parantheses;
        std::string temp;
        float temp_num;
        for (auto pos : data)
        {
            if (pos.second == "(")
            {
                left.push_back(pos.first);
            }

            else if (pos.second == ")")
            {
                right.push_back(pos.first);
            }
        }

        temp = expr.substr(left[0], right[0] - left[0]);
        std::string::iterator it = temp.begin();
        temp.erase(it);

        number = Operators(temp, numbers);

        std::cout << expr << std::endl;

        // check if there is a expr before the parentheses
        if (left[0] > 0)
        {
            temp = expr.substr(0, left[0]);
            temp += std::to_string(static_cast<int>(number));
            number = Operators(temp, numbers);
        }

        else
        {
            std::cout << "TODO\n";
        }
    }

    return number;
}

float Eval::Operators(std::string expr, std::vector<std::string> numbers)
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
        number = Numbers(expr, numbers);
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

    return number;
}

float Eval::Numbers(std::string expr, std::vector<std::string> numbers)
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
    
    return number;
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