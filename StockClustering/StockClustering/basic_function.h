#pragma once

#include "basic_definition.h"

static vector<string> SeperateString(const string& text, char token)
{
    vector<string> result;

    string unit;
    size_t size = text.size();

    for (size_t i = 0; i < size; ++i)
    {
        if (text[i] == token)
        {
            result.push_back(unit);
            unit.clear();
        }
        else
        {
            unit.push_back(text[i]);

            if (i == size - 1) // Last loop
            {
                result.push_back(unit);
            }
        }
    }

    return result;
}