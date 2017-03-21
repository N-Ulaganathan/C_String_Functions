/*
*	String Functions in C.
*	Copyright (C) 2017  Ulaganathan Natarajan
*	<ulaganathan.n@hotmail.com>
*
*	This library is free software; you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as published by
*	the Free Software Foundation; either version 2.1 of the License, or (at
*	your option) any later version.
*
*	This library is distributed in the hope that it will be useful, but
*	WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*	Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with this library; if not, write to the Free Software
*	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
*	USA.
*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifndef STRINGFUNCTIONS_H
#define	STRINGFUNCTIONS_H


//Prototypes
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

int commonArrayLen = 0;


//String split_string
char** split_string(char *source, const char* delimiter) {
	char **outStr = NULL, *token;
	int arrayLen = 0;
	source = strdup(source);
	if(source == NULL || delimiter == NULL)
	return NULL;
	token = strtok(source, delimiter);
	while (token != NULL) {
		outStr = realloc(outStr, (arrayLen + 1) * sizeof(char*));
		if(outStr == NULL)
		return NULL;
		*(outStr + arrayLen) = malloc((strlen(token) + 1) * sizeof(char));
		*(outStr + arrayLen) = strdup(token);
		arrayLen++;
		token = strtok(NULL, delimiter);
	}
	commonArrayLen = arrayLen;
	return outStr;
}

//Find All Strings
char **find_all_string(char *source, char *startString, char *endString) {
	char **outStr = NULL, *startPos, *endPos, *findValue;
	int arrayLen = 0;
	int totalLen = 0, endLen = 0, startLen = 0;
	if(source == NULL || startString == NULL || endString == NULL)
	return NULL;
	if(strlen(startString) == 0 || strlen(endString) == 0)
	return NULL;
	if(strstr(source, startString) == NULL || strstr(source, endString) == NULL)
	return NULL;
	while(true) {
		startPos = strstr(source + startLen, startString);
		if(startPos == NULL)
		break;
		startLen = (startPos - source) + strlen(startString);
		endPos = strstr(source + startLen, endString);
		if(endPos == NULL)
		break;
		endLen = endPos - source;
		totalLen = endLen - startLen;
		outStr = realloc(outStr, (arrayLen + 1) * sizeof(char*));
		if(outStr == NULL)
		return NULL;
		findValue = malloc((totalLen + 1) * sizeof(char));
		strncpy(findValue, source + startLen, totalLen);
		findValue[totalLen] = '\0';
		*(outStr + arrayLen) = malloc((totalLen + 1) * sizeof(char));
		*(outStr + arrayLen) = strdup(findValue);
		arrayLen++;
	}
	commonArrayLen = arrayLen;
	return outStr;
}

//Find String
char *find_string(char *source, char *startString, char *endString) {
	char *outStr;
	int startLen = 0, endLen = 0, totalLen = 0;
	if(source == NULL)
	return NULL;
	if(startString == NULL){
		startLen = 0;
	}else{
		if(strlen(startString)==0)
		startLen = 0;
		else
		startLen = (strstr(source, startString) - source) + strlen(startString);
	}
	if(endString == NULL){
		endLen = strlen(source);
	}else{
		if(strlen(endString)==0){
			endLen = strlen(source);
		}else{
			if(startLen > 0)
			endLen = strstr(source+startLen, endString) - source;
			else
			endLen = strstr(source, endString) - source;
		}
	}
	if(startLen < 0 || endLen < 0 )
	return NULL;
	totalLen = endLen - startLen;
	outStr = malloc((totalLen + 1) * sizeof(char));
	strncpy(outStr, source + startLen, totalLen);
	outStr[totalLen] = '\0';
	return outStr;
}

//replace_all
char *replace_all(char *source, char *orig, char *rep) {
	char *outStr, *p;
	int pos = 0, replen = 0, origlen = 0;
	if(source == NULL || orig == NULL || rep == NULL)
	return source;
	p = strstr(source, orig);
	if(p == NULL)
	return source;
	replen = strlen(rep);
	origlen = strlen(orig);
	pos = (p - source) + replen;
	outStr = malloc(1 * sizeof(char));
	while(p != NULL) {
		outStr = realloc(outStr, (strlen(source) + replen + 1));
		*outStr = '\0';
		strcat(outStr, source);
		sprintf(outStr + (p - source), "%s%s", rep, p + origlen);
		source = strdup(outStr);
		p = strstr(source + pos, orig);
		pos = (p - source) + replen;
	}
	free(outStr);
	return source;
}

// Replace
char *replace(char* source, char* orig, char* rep) {
	char *outStr, *p;
	if(source == NULL || orig == NULL || rep == NULL)
	return source;
	p = strstr(source, orig);
	if(p == NULL)
	return source;
	outStr = malloc(strlen(source) + strlen(rep) + 1 * sizeof(char));
	*outStr = '\0';
	strcat(outStr, source);
	sprintf(outStr + (p - source), "%s%s", rep, p + strlen(orig));
	return outStr;
}

//Sub String
char *sub_string(char *source, int start_len, int end_len){
	char *out_str;
	if(source == NULL)
	return NULL;
	if(start_len>end_len)
	end_len = strlen(source);
	int total_len=end_len - start_len;
	out_str = malloc((total_len + 1) * sizeof(char));
	strncpy(out_str, source + start_len, total_len);
}

//Contains
bool contains(char *source, char *find) {
	char *exist;
	if(source == NULL || find == NULL)
	return false;
	exist = strstr(source, find);
	if(exist != NULL) {
		return true;
	}
	return false;
}

//Contains Ignore Case
bool contains_ignore_case(char *source, char *find) {
	char *exist;
	if(source == NULL || find == NULL)
	return false;
	source = to_lower_case(source);
	find = to_lower_case(find);
	exist = strstr(source, find);
	if(exist != NULL) {
		return true;
	}
	return false;
}

//Equals
bool equals(char *source, char *find) {
	if(source == NULL || find == NULL)
	return false;
	if(strcmp(source, find) == 0) {
		return true;
	}
	return false;
}

//Equls Ignore Case
bool equals_ignore_case(char *source, char *find) {
	if(source == NULL || find == NULL)
	return false;
	source = to_lower_case(source);
	find = to_lower_case(find);
	if(strcmp(source, find) == 0) {
		return true;
	}
	return false;
}

//Starts With
bool starts_with(char *source, char* find) {
	if(source == NULL || find == NULL)
	return false;
	if((strstr(source, find) - source) == 0) {
		return true;
	}
	return false;
}

//Ends With
bool ends_with(char *source, char *find) {
	int sourcelen, findlen;
	if(source == NULL || find == NULL)
	return false;
	sourcelen = strlen(source);
	findlen = strlen(find);
	if((sourcelen >= findlen) && (0 == strcmp(source + sourcelen - findlen, find))) {
		return true;
	}
	return false;
}

// To Lower Case
char* to_lower_case(char *source) {
	char *outStr;
	int i, length = 0;
	if(source == NULL)
	return NULL;
	outStr = strdup(source);
	length = strlen(source);
	for (i = 0; i < length; i++)
	outStr[i] = (char) tolower(source[i]);
	return outStr;
}

//To Upper Case
char* to_upper_case(char *source) {
	char *outStr;
	int i, length = 0;
	if(source == NULL)
	return NULL;
	outStr = strdup(source);
	length = strlen(source);
	for(i = 0; i < length; i++)
	outStr[i] = (char) toupper(source[i]);
	return outStr;
}

//Trim
char* trim(char *source) {
	char *outStr = malloc((strlen(source) + 1) * sizeof(char));
	int sourceLen = strlen(source), startLen = 0, endLen = 0, totalLen = 0, x;
	if(source == NULL)
	return NULL;
	for(x = 0; x < sourceLen; x++, startLen++) {
		if(!isspace(source[x]))
		break;
	}
	for(x = sourceLen - 1; x >= 0; x--, endLen++) {
		if(!isspace(source[x]))
		break;
	}
	totalLen = sourceLen - (startLen + endLen);
	if(totalLen < 1)
	return NULL;
	strncpy(outStr, source + startLen, (size_t) totalLen);
	outStr[totalLen] = '\0';
	return outStr;
}

//get index of string
int index_of(char *source, char *find){
	if(source == NULL)
	return NULL;
	char *p = strstr(source, find);
	if (p != NULL)
	return p - source;
	return -1;
}

//get index of string
int index_of(char *source, char *find, int start){
	if(source == NULL)
	return NULL;
	char *p = strstr(source + start, find);
	if (p != NULL)
	return p - source;
	return -1;
}

char *get_random_string(const int size, const int randomType) {
	char *outStr=malloc(size*sizeof(char)+1), alphaNumerics[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	int x, sIndex = 0, eIndex = 0;
	if(randomType == 0 || randomType > 2){
		sIndex = 0;
		eIndex = 35;
	}else if(randomType == 1){
		sIndex = 0;
		eIndex = 25;
	}else if(randomType == 2){
		sIndex = 26;
		eIndex = 35;
	}
	for(x=0; x<size; x++){
		outStr[x] = alphaNumerics[rand() % (eIndex - sIndex + 1) + sIndex];
	}
	outStr[size] = '\0';
	return outStr;
}

#endif	/* STRINGFUNCTIONS_H */
