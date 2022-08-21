#include "cstring.hpp"

void test_find_char()
{
    string_t* str = str_create("hello world");
    str_find_chr(str, 'l');    
}

void test_find_str()
{
    string_t* s = str_create("helloworld lo nihao hello");
    str_find_str(s, "lo");
}

void test_replace()
{
    string_t* s = str_create("hello world hello");
    str_replace(s, " ", "%20");
    str_print(s);
}

void test_concat()
{
    string_t* s1 = str_create("hello");
    string_t* s2 = str_create("world!world!world!");
    s1 = str_concat(s1, s2);
    str_print(s1); 
}

void test_split()
{
    string_t* s = str_create("hello world ni hao hello");
    char* words[100] = {NULL};
    char split[] = " ";
    char** pp = words;
    str_split(s, split, words);
    int idx = 0;
    puts("Words list are shown as follow: ");
    for(int idx = 0; *pp; idx++, pp++) {
        printf("%d) %s\n", idx + 1, *pp);
    }
}

int main()
{
    test_find_char();
    test_find_str();
    test_replace();
    test_concat();
    test_split();
}
