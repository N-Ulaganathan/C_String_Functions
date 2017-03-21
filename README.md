# C-String-Functions
Copyright (C) 2017  Ulaganathan Natarajan
<ulaganathan.n@hotmail.com>

Java like string functions to manipulate c strings

list of functions
--------------------------------------------------------------

char** split_string(char*, const char*);

char** find_all_string(char*, char*, char*);

char* find_string(char*, char*, char*);

char* replace_all(char*, char*, char*);

char* replace(char*, char*, char*);

char* sub_string(char, int, int);

bool contains(char*, char*);

bool contains_ignore_case(char*, char*);

bool equals(char*, char*);

bool equals_ignore_case(char*, char*);

bool starts_with(char*, char*);

bool ends_with(char*, char*);

char* to_lower_case(char*);

char* to_upper_case(char*);

char* trim(char*);

int index_of(char*, char*);

int index_of_from(char*, char*, int);

char* get_random_string(const int, const int);
