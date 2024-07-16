#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


struct MasterRow
{
    char table_name[32];
    uint32_t num_col;
    uint32_t first_page;
    uint32_t types_size;
    uint32_t names_size;
    // first 48 bytes can be written directly, remaining (types_size+names_size) have to be
    // written manually
    char* types;
    char* names;

    void create_table(string s)
    {
        first_page = 0;
        stringstream ss(s);
        string temp;
        ss >> temp;
        strcpy(table_name, temp.c_str());

        vector<string> col_names;
        vector<pair<uint32_t, uint32_t>> col_types;

        num_col = 0;
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

        names_size = 4 * num_col;
        for (auto &s : col_names) names_size += 1+s.length();

        uint32_t cur_offset = 0;
        names = new char[names_size];

        for (auto &s : col_names)
        {
            uint32_t len = s.length()+1;
            memcpy(names+cur_offset, &len, 4);
            cur_offset+=4;

            strcpy(names+cur_offset, s.c_str());
            cur_offset += 1+s.length();
        }
        cout << names_size << '\n';
        types_size = 5 * num_col;
        types = new char[types_size];

        for (uint32_t i = 0; i < num_col; i++)
        {
            uint32_t temp = col_types[i].first;
            memcpy(types+5*i, &temp, 1);
            
            temp = col_types[i].second;
            memcpy(types+5*i+1, &temp, 4);
        }
    }

    void read_row(char* page, uint32_t offset)
    {
        names = new char[names_size];
        types = new char[types_size];
        memcpy(names, page+offset+56, names_size);
        memcpy(types, page+offset+56+names_size, types_size);
    }

    uint32_t row_size()
    {
        return 56 + types_size + names_size;
    }

    char* serialized()
    {
        char* data = new char[row_size()];
        memcpy(data, this, 48);
        memcpy(data+44, names, names_size);
        memcpy(data+44+names_size, types, types_size);
        return data;        
    }
};