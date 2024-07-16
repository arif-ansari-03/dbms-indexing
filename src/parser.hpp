#include <iostream>
#include <sstream>
#include "cursor.hpp"

using namespace std;

char* create_table(string s)
{
    stringstream ss(s);
    string table_name;
    ss << table_name;
    char* data;

    vector<string> col_names;
    vector<pair<uint32_t, uint32_t>> col_types;

    string temp;
    uint32_t num_col = 0;
    while (ss >> temp)
    {
        num_col++;

        col_names.emplace_back(temp);

        ss >> temp;
        pair<uint32_t, uint32_t> col_type;

        if (temp == "varchar")
        {
            col_type.first = 0;
            ss >> col_type.second;
        }
        else if (temp == "int")
        {
            col_type.first = 1;
            col_type.second = 4;
        }
        else
        {
            col_type.first = 2;
            col_type.second = 4;
        }
        col_types.emplace_back(col_type);
    }

    
}