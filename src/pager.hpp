#include <map>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

extern uint32_t page_size;

/*
** Free_Page_List is a linked list storing page numbers of all.
** The last 9 bytes will store the number of pages(1B), previous page(4B) and next page(4B).
** Page 0 has information regarding the last page of this list.
** Everytime a new page is required, The last page of this linked list is opened,
** and the last page available is popped from the list.
** If a page is freed, it is added to the last page.
*/
struct Free_Page_List
{
    uint32_t last_page;
};

struct First_Page
{
    // contents of page 0
    uint32_t free_page_list_lp; // last page of free_page_list
};

struct Pager
{
    First_Page first_page;
    Free_Page_List free_page_list;

    vector<char*> page_list;
    map<uint32_t, uint32_t> page_index;
    char* buffer;

    void init()
    {

    }

    void checkPage(uint32_t page_num)
    {
        if (page_index.count(page_num)) return;

        fstream file("mydb.db");
        file.seekg(page_num * page_size);
        buffer = new char[page_size];
        file.read(buffer, page_size);
        file.close();

        page_index[page_num] = page_list.size();
        page_list.emplace_back(buffer);
    }
};
