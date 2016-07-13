// File: roman_calc_lib.c 
// Description: Roman arithemetic operations
#include <string.h>
#include <stdlib.h>
#include "roman_math_lib.h"

static char roman_char[] = "IVXLCDM";
static int decimal_val[] = {1, 5, 10, 50, 100, 500, 1000};

static char roman_compact[] = "VXLCDM";
static char* roman_xtnd[] = {"IIII","VIIII","XXXX","LXXXX","CCCC","DCCCC"};

#define MAX_ROMAN_STRING_SIZE 50

static int get_index(char ch, char arr[])
{
    for(int idx = 0; idx < 7; idx++)
    {
        if(arr[idx] == ch)
        {
            return idx;
        }
    }
    return -1;
}
// Helper function to uncompact the roman string
static void uncompact_roman_string(char *src)
{
    char tmp[MAX_ROMAN_STRING_SIZE] = {0};
    int length = strlen(src);
    int cnt = 0;
    for (int idx = 0; idx < length; idx++)
    {
        int curr = get_index(src[idx], roman_char);
        int next = get_index(src[idx + 1], roman_char);

        if (curr >= next)
        {
            tmp[cnt++] = src[idx];
        }
        else
        {
            int cmt = get_index(src[idx + 1], roman_compact);

            strcat((char*)(tmp + cnt), roman_xtnd[cmt]);
            cnt += strlen(roman_xtnd[cmt]);
            idx = idx + 1;
        }
    }

    strcpy(src, tmp);
}

//Function to add two roman numbers
char* add(char* first, char* second)
{
    static char temp[MAX_ROMAN_STRING_SIZE] = {0};
    static char result[MAX_ROMAN_STRING_SIZE] = {0};

    memset(temp1,'\0',MAX_ROMAN_STRING_SIZE);
    memset(result,'\0',MAX_ROMAN_STRING_SIZE);

    // Step 1: Uncompact the roman number strings

    // Uncompact first number
    strcpy(temp, first);
    uncompact_roman_string(temp);
    strcat(result, temp);

    // Uncompact second number
    memset(temp,'\0',MAX_ROMAN_STRING_SIZE);
    strcpy(temp, second);
    uncompact_roman_string(temp);

    return result;
}
