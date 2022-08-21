// C 字符串库的封装
#include "base.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isdigit(c)      ((c >= '0' && c <= '9'))
#define ischaracter(c)  ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

///////////////////////////////////////////////////////////////////////////////

// c string
typedef struct string_s {
    int size;
    int capacity;
    char data[];
} string_t;

///////////////////////////////////////////////////////////////////////////////
// Base API

extern "C" {

// 创建字符串
string_t* str_create(const char* data) 
{
    int sz = sizeof(string_t) + 2*strlen(data);
    string_t* str = (string_t*) malloc(sz);
    if(!str) return 0;

    for(int i = 0; i < strlen(data); i++) {
        str->data[i] = data[i];
    }
    str->size = strlen(data);
    str->capacity = sz;
    str->data[str->size] = '\0';
    return str;
}


void str_print(string_t *s) 
{
    if(!s) return;
    puts(s->data);
}

// 创建字符串（初始化为 n 个 c 字符）
string_t* str_create_nchar(int n, char c) 
{
    if(n < 0) n = 1;
    int sz = sizeof(string_t) + 2 * n;
    string_t* str = (string_t*) malloc(sz);
    if(!str) return 0;
    for(int i = 0; i < n; i++) str->data[i] = c;
    str->size = n;
    str->capacity = sz;
    str->data[str->size] = '\0';
    return str;
}

// 销毁字符串
void str_destroy(string_t* str) {
    free(str);
}

// 字符串尾部追加
void str_append(string_t* str, char c) {
    if(!str) return;
    if(str->size <= str->capacity) {
        str->data[str->size] = c;
        str->data[str->size + 1] = '\0';
        str->size++;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Wrapper API

// 查找所有的指定字符并打印
void str_find_chr(string_t* str, char c) 
{
    // check
    if(!isdigit(c) && !ischaracter(c)) return;

    // ready
    char* arr = str->data;
    int cnt = 0;
    char *p = arr, *p_ori = arr;
    int pos = -1;

    // find
    while((p = strchr(p, c)) != 0 && *p) {
        pos = p - p_ori;
        if(pos < 0) return;
        string_t *t = str_create_nchar(pos, ' ');
        str_append(t, '^');
        printf("%s (at pos %d)\n%s\n", p_ori, pos, t->data);
        p++;
        cnt++;
    }
    printf("all found %d pos about char '%c'\n", cnt, c);
}

// 查找指定子串出现的位置
int str_find_str(string_t* s, const char* target) 
{
    char *p = s->data;
    int pos = 0;
    int cnt = 0;
    while (pos < s->size)
    {
        p = strstr(p, target);
        pos = p++ - s->data;
        if(pos >= s->size || pos < 0) break;
        string_t* t = str_create_nchar(pos, ' ');
        str_append(t, '^');
        printd("%s (at pos %d)\n%s\n", s->data, pos, t->data);
        p++;
        cnt++;
    }
    return cnt;
}

// 字符串深拷贝
string_t* str_copy(string_t *s) 
{
    string_t* str = str_create(s->data);
    str->size = s->size;
    str->capacity = s->capacity;
    return str;
}

// 字符串覆盖
string_t* str_overwrite(string_t *s1, string_t *s2) {
    strcpy(s2->data, s1->data);
    s2->size = s1->size;
    s2->capacity = s1->capacity;
    return s2;
}

// 替换字符串中的指定子串为新的子串
void str_replace(string_t* s, const char* oldstr, const char* newstr) 
{
    int cnt = 0;
    int sz1 = strlen(oldstr), sz2 = strlen(newstr);
    int sz = strlen(s->data);
    cnt = str_find_str(s, oldstr);
    if (cnt == 0) return;

    int newsz = sz + cnt * (sz2 - sz1);
    string_t* tmp = str_create_nchar(newsz, 'c');
    int idx = 0;
    for (int i = 0; i < sz; i++) {
        if (strncmp(s->data + i, oldstr, sz1) == 0) {
            strncpy(tmp->data + idx, newstr, sz2);
            idx += sz2;
        }
        else tmp->data[idx++] = s->data[i];
        // str_print(tmp);
    }
    str_overwrite(tmp, s);
}

// 字符串拼接
string_t* str_concat(string_t* dst, string_t* src) 
{
    dst->size += src->size;
    
    // 动态扩容
    if(dst->size > dst->capacity) {
        int nsz = sizeof(string_t) + 2*dst->capacity;
        printd("string_t dst expand memory (%d -> %d)\n", dst->capacity, nsz);
        dst = (string_t*) realloc(dst, nsz);
        if(!dst) exit(1);
        dst->capacity = 2*dst->capacity;
    }
    strcat(dst->data, src->data);
    dst->size += strlen(src->data);
    return dst; // new dst
}

// 将字符串拆分成单词数组
void str_split(string_t* s, const char* split, char* words[]) 
{
    char *p = s->data;
    int index = 0;
    char *word = p;
    
    while(word) {
        word = strtok(p, split);
        if(word) words[index++] = word; 
        if(p - s->data + strlen(word) + 1 < s->size) 
            p += strlen(word) + 1;
        else break;
    }
    words[index++] = NULL; 
}

} // end of extern "C" 
