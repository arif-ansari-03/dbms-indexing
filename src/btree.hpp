#include <iostream>
#include <cstring>
#include "pager.hpp"

using namespace std;

extern Pager pager;

/*
** What a btree page looks like:
** forgot abt parent node :S will add next time
**    
**   4 bytes, pointer to another btree page
**   ^              2 bytes, points to its data starting location in the page
**   |              ^
**   |              | 
** +----------------------------------------------------------------------+
** | p0 | k1 | p1 | k2 | p2 |              | s2 |  d2   |  s1 | d1  | num |
** +----------------------------------------------------------------------+
**        |         |                      ^            ^
**        |         |                      |            |
**        |         +----------------------+            |
**        +---------------------------------------------+
**
** s1 is the size of d1 only (and doesn't include s1)
** num is number of keys, here it is 2 (k1, k2)
*/

vector<pair<char*, uint32_t>> load_page(uint32_t page_num)
{
    uint32_t num_keys = 0;
    pager.checkPage(page_num);

    char* page = pager.page_list[pager.page_index[page_num]];

    memcpy(&num_keys, page+page_size-4, 4);
    vector<pair<char*, uint32_t>> node;
    if (num_keys == 0) return node;

    uint32_t cur_key = 0;
    memcpy(&cur_key, page, 4);
    char* temp = new char[1];
    temp[0] = 0;

    node.emplace_back(temp, cur_key);

    uint32_t offset = 4;
    while (1)
    {
        if (node.size() == num_keys+1) break;
        uint32_t data = 0;
        memcpy(&data, page+offset, 2);
        
        uint32_t data_size = 0; // does not include the 2 bytes used to store data_size itself
        memcpy(&data_size, page+data, 2);
        temp = new char[data_size+2];
        memcpy(temp, &data_size, 2);
        memcpy(temp+2, page+data+2, data_size);

        cur_key = 0;
        memcpy(&cur_key, page+offset+2, 4);
        node.emplace_back(temp, cur_key);
        offset += 8;
    }
    return node;
}

void write_page(uint32_t page_num, vector<pair<uint32_t, char*>> node)
{
    pager.checkPage(page_num);
    char* page = pager.page_list[pager.page_index[page_num]];

    uint32_t num_keys = node.size();
    if (num_keys) num_keys--;
    else
    {
        for (uint32_t i = 0; i < page_size; i++)
            page[i] = 0;
        return;
    }
    
    memcpy(page+page_size-4, &num_keys, 4);
    uint32_t data_written = 4; // this is to find how much data has been written from the end



}

void insert(uint32_t page_num, char* data)
{
    
}

uint32_t search_leaf(uint32_t cur_page, char* data)
{
    return 0;
}
