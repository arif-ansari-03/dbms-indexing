#include <iostream>
#include "btree.hpp"
#include "cursor.hpp"

using namespace std;

uint32_t page_size = 400;

bool operator==(string a, string b)
{
    if (a.length() != b.length()) return 0;
    for (int i = 0; i < a.length(); i++) if (a[i] != b[i]) return 0;
    return 1;
}

Pager pager;

void create_table(string s)
{

}

int main()
{
    
}