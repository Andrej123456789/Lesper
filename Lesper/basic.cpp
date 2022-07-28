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
    int varstarted = 0;
    std::string str = "";
    std::string expr = "";
    std::string n = "";
    std::string var = "";
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

            else if (var != "")
            {
                tokens.push_back("VAR:" + var);
                var = "";
                varstarted = 0;
            }
            tok = "";
        }

        else if (tok == "=" && state == 0)
        {
            if (var != "")
            {
                tokens.push_back("VAR:" + var);
                var = "";
                varstarted = 0;
            }

            tokens.push_back("EQUALS");
            tok = "";
        }

        else if (tok == "$" && state == 0)
        {
            varstarted = 1;
            var += tok;
            tok = "";
        }

        else if (varstarted == 1)
        {
            if (tok == "<" || tok == ">")
            {
                if (var != "")
                {
                    tokens.push_back("VAR:" + var);
                    var = "";
                    varstarted = 0;
                }
            }
            var += tok;
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

float evalExpression(std::string expr)
{
    Eval eval = Eval(expr, parentheses, numbers);

    if (eval.error_state == true)
    {
        return atof("Nan");
    }

    else
    {
        return eval.ret;
    }
}

void print(std::string str)
{
    float temp;

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
        temp = evalExpression(str.substr(5));
        str = (temp == static_cast<int>(temp)) ? std::to_string(static_cast<int>(temp)) : std::to_string(temp);
    }

    else
    {
        return;
    }

    std::cout << str << std::endl;
}

void assign(std::string varname, std::string varvalue)
{
    if (symbols.find(varname.substr(4)) == symbols.end())
    {
        symbols.insert({varname.substr(4), varvalue});
    }

    else
    {
        symbols[varname.substr(4)] = varvalue;
    }
}

std::string get_variable(std::string varname, struct errors* error)
{
    varname = varname.substr(4);
    for (auto x : symbols)
    {
        if (varname == x.first)
        {
            return x.second;
        }

        else
        {
            continue;
        }
    }

    return error->undefined_variable;
}

void parse(struct errors* error)
{
    std::string temp;

    size_t i = 0;
    while(i < tokens.size())
    {
        if (evaluateTokens(tokens, i, "PRINT STRING", 6, 0) || evaluateTokens(tokens, i, "PRINT NUM", 3, 0) || evaluateTokens(tokens, i, "PRINT EXPR", 4, 0) || evaluateTokens(tokens, i, "PRINT VAR", 3, 0))
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

            else if (tokens[i + 1].substr(0, 3) == "VAR")
            {
                print(get_variable(tokens[i + 1], error));
            }

            i+=2;
        }

        else if (evaluateTokens(tokens, i, "VAR EQUALS STRING", 6, 1) || evaluateTokens(tokens, i, "VAR EQUALS NUM", 3, 1) || evaluateTokens(tokens, i, "VAR EQUALS EXPR", 4, 1))
        {
            if (tokens[i + 2].substr(0, 6) == "STRING")
            {
                std::cout << "here" << std::endl;
                assign(tokens[i], tokens[i + 2]);
            }

            else if (tokens[i + 2].substr(0, 3) == "NUM")
            {
                assign(tokens[i], tokens[i + 2]);
            }

            else if (tokens[i + 2].substr(0, 4) == "EXPR")
            {
                std::string tmp = "NUM:";
                tmp += (evalExpression(tokens[i + 2].substr(5)) == static_cast<int>(evalExpression(tokens[i + 2].substr(5)))) ? std::to_string(static_cast<int>(evalExpression(tokens[i + 2].substr(5)))) : std::to_string(evalExpression(tokens[i + 2].substr(5)));
                assign(tokens[i], tmp);
            }
            i+=3;
        }
    }
}

void run(std::string path)
{
    keywords* k = new keywords;
    errors* error = new errors;

    std::string data = open_file(path);
    lex(data, k);
    parse(error);

    delete k;
    delete error;
}