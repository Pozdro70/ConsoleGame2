#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>

#pragma once
class helperMethods
{
public:
    // remove leading/trailing ASCII whitespace + CR + NBSP
    static inline void trim_inplace(std::string& s) {
        auto is_ws = [](unsigned char ch) {
            return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\f' || ch == '\v' || ch == 0xA0; // NBSP
            };
        size_t i = 0, j = s.size();
        while (i < j && is_ws(static_cast<unsigned char>(s[i]))) ++i;
        while (j > i && is_ws(static_cast<unsigned char>(s[j - 1]))) --j;
        if (i > 0 || j < s.size()) s = s.substr(i, j - i);
    }

    // strip UTF-8 BOM if present (can appear on any line in some editors)
    static inline void strip_bom(std::string& s) {
        if (s.rfind("\xEF\xBB\xBF", 0) == 0) s.erase(0, 3);
    }
};

