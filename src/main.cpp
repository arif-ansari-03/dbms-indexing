#include <iostream>
#include "btree.hpp"
#include "cursor.hpp"

using namespace std;

bool operator==(string a, string b)
{
    if (a.length() != b.length()) return 0;
    for (int i = 0; i < a.length(); i++) if (a[i] != b[i]) return 0;
    return 1;
}


int main()
{
    // vector<pair<char*, uint32_t>> node(2);
    // node[0].second = 2;
    // node[1].second = 3;
    // node[1].first = new char[3];
    // node[1].first[0] = 1;
    // node[1].first[1] = 0;
    // node[1].first[2] = 'a';  


    // write_page(1, node, 0); 

    uint32_t parent = 1;
    vector<pair<char*, uint32_t>> node = load_page(1, parent);
    cout << parent << '\n';
    for (auto &a : node)
        cout << a.second << '\n';

    uint32_t temp = 0;
    memcpy(&temp, node[1].first, 2);
    cout << temp << '\n';
    
    pager.close();
}