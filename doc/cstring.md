# A simple and useful string struct for C

## Usage

You just need to include the header `cstring.hpp`, and use it as follows:

## str_find_chr

```c
void test_find_char()
{
    string_t* str = str_create("hello world");
    str_find_chr(str, 'l');    
}
```

output:

```
hello world (at pos 2)
  ^
hello world (at pos 3)
   ^
hello world (at pos 9)
         ^
all found 3 pos about char 'l'
```

## str_find_str

```c
void test_find_str()
{
    string_t* s = str_create("helloworld lo nihao hello");
    str_find_str(s, "lo");
}
```

output:

```
helloworld lo nihao hello (at pos 3)
   ^
helloworld lo nihao hello (at pos 11)
           ^
helloworld lo nihao hello (at pos 23)
                       ^
```

## str_replace

```c
void test_replace()
{
    string_t* s = str_create("hello world hello");
    str_replace(s, " ", "%20");
    str_print(s);
}
```

output: 

```
hello%20world%20hello
```

## str_concat

```c
void test_concat()
{
    string_t* s1 = str_create("hello");
    string_t* s2 = str_create("world!world!world!");
    s1 = str_concat(s1, s2);
    str_print(s1); 
}
```
output:

```c
// string_t dst expand memory (18 -> 44)
helloworld!world!world!
```

## str_split

```c
void test_split()
{
    string_t* s = str_create("hello world ni hao hello");
    char* words[100] = {NULL};
    char* split = " ";
    char** pp = words;
    str_split(s, split, words);
    int idx = 0;
    puts("Words list are shown as follow: ");
    for(int idx = 0; *pp; idx++, pp++) {
        printf("%d) %s\n", idx + 1, *pp);
    }
}
```

output:
```
Words list are shown as follow:
1) hello
2) world
3) ni
4) hao
5) hello
```
