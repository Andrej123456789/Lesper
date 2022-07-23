#include "basic.hpp"

std::string open_file(std::string filename)
{
    std::string ret;

    FILE* file = fopen(filename.c_str(), "r");
    if (file == NULL)
    {
        std::cout << "Error opening file" << std::endl;
        return "";
    }

    char* buffer = new char[256];
    
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        ret += buffer;
    }

    fclose(file);
    delete[] buffer;

    ret += "<EOF>";
    return ret;
}

void lex(std::string filecontents, struct keywords* k)
{
    std::string tok = "";
    int state = 0;
    int isexpr = 0;
    std::string str = "";
    std::string expr = "";
    std::string n = "";
    std::string temp;
    auto content = std::list<char> {};

    for (auto x : filecontents)
    {
        content.push_back(x);
    }

    for (auto y : content)
    {
        tok += y;

        if (tok == " ")
        {
            if (state == 0)
            {
                tok = "";
            }

            else
            {
                tok = " ";
                str += tok;
            }
        }

        else if (tok == "\n" || tok == "<EOF>")
        {
            if (expr != "" && isexpr == 1)
            {
                temp = "EXPR:" + expr;
                tokens.push_back(temp);
                temp = "";
                expr = "";
            }

            else if (expr != "" && isexpr == 0)
            {
                temp = "NUM:" + expr;
                tokens.push_back(temp);
                temp = "";
                expr = "";
            }
            tok = "";
        }

        else if (tok == k->print || tok == lower(k->print))
        {
            tokens.push_back("PRINT");
            tok = "";
        }

        else if (containsSomething(tok, numbers))
        {
            expr += tok;
            tok = "";
        }

        else if (containsSomething(tok, operators) || tok == "(" || tok == ")")
        {
            isexpr = 1;
            expr += tok;
            tok = "";
        }

        else if (tok == "\"")
        {
            if (state == 0)
            {
                state = 1;
            }

            else if (state == 1)
            {
                temp = "STRING:" + str + "\"";
                tokens.push_back(temp);
                temp = "";
                str = "";
                state = 0;
                tok = "";
            }
        }

        else if (state == 1)
        {
            str += y;
            tok = "";
        }
    }
}

std::string evalExpression(std::string expr)
{
    expr = "," + expr;

    size_t i = expr.length() - 1;
    std::string num = "";
    std::string temp = "";

    while (i >= 0)
    {
        temp = expr[i];

        if (containsSomething(temp, operators) || temp == "%")
        {
            std::reverse(num.begin(), num.end());
            num_stack.push_back(num);
            num_stack.push_back(temp);
            num = "";
        }

        else if (temp == ",")
        {
            std::reverse(num.begin(), num.end());
            num_stack.push_back(num);
            num = "";
        }

        else
        {
            num += expr[i];
        }

        if (i != 0)
        {
            i--;
            temp = "";
        }

        else
        {
            temp = "";
            break;
        }
    }

    for (auto x : num_stack)
    {
        std::cout << x << std::endl;
    }
}

void print(std::string str)
{
    if (str.substr(0, 6) == "STRING")
    {
        str = str.substr(7);
        str = str.substr(0, str.length() - 1);
    }

    else if (str.substr(0, 3) == "NUM")
    {
        str = str.substr(4);
    }

    else if (str.substr(0, 4) == "EXPR")
    {
        str = evalExpression(str.substr(5));
    }

    std::cout << str << std::endl;
}

void parse()
{
    std::string temp;

    size_t i = 0;
    while(i < tokens.size())
    {
        if (evaluateTokens(tokens, i, "PRINT STRING", 6) || evaluateTokens(tokens, i, "PRINT NUM", 3) || evaluateTokens(tokens, i, "PRINT EXPR", 4))
        {
            if (tokens[i + 1].substr(0, 6) == "STRING")
            {
                print(tokens[i + 1]);
            }

            else if (tokens[i + 1].substr(0, 3) == "NUM")
            {
                print(tokens[i + 1]);
            }

            else if (tokens[i + 1].substr(0, 4) == "EXPR")
            {
                print(tokens[i + 1]);
            }

            i+=2;
        }
    }
}

void run(std::string path)
{
    keywords* k = new keywords;

    std::string data = open_file(path);
    lex(data, k);
    parse();

    delete k;
}