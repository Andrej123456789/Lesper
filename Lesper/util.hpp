#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string lower(std::string str);
bool containsSomething(std::string str, std::vector<std::string> vec);
bool evaluateTokens(std::vector<std::string> tokens, int i, std::string str, int substr);