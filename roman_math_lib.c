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

// Sort and combine roman symbols
static void sort_and_combine_roman_string(char* src)
{
    int ch_count[7] = {0};
    int length = strlen(src);

    // get the count of each symbols 
    for(int idx = 0; idx < length; idx++)
    {
        ch_count[get_index(src[idx], roman_char)]++;
    }

    // combine symbols if required
    for(int idx = 0; idx < 7; idx++)
    {
        if(ch_count[0] >= 5)
        {
            ch_count[0] -= 5;
            ch_count[1]++;
        }
        if(ch_count[1] >= 2)
        {
            ch_count[1] -= 2;
            ch_count[2]++;
        }
        if(ch_count[2] >= 5)
        {
            ch_count[2] -= 5;
            ch_count[3]++;
        }
        if(ch_count[3] >= 2)
        {
            ch_count[3] -= 2;
            ch_count[4]++;
        }
        if(ch_count[4] >= 5)
        {
            ch_count[4] -= 5;
            ch_count[5]++;
        }
        if(ch_count[5] >= 2)
        {
            ch_count[5] -= 2;
            ch_count[6]++;
        }
    }

    // Update the string using the table
    int t = 0;
    memset(src,'\0',length);
    for(int idx = 6; idx >= 0; idx--)
    {
        int max = ch_count[idx];
        for( int i = 0; i < max; i++){
            src[t++] = roman_char[idx];
        }
    }
}

static void compact_subtractives(char *str)
{
    char *ptr = str;
    int idx = 0;
    int length = strlen(str);
    char res[MAX_ROMAN_STRING_SIZE] = {0};
    int t = 0;

    while(idx < length)
    {
        if (strncmp((char*)(ptr+idx), "IIII", 4) == 0)
        {
            res[t++] = 'I';
            res[t++] = 'V';
            idx += 4;

        }
        if (strncmp((char*)(ptr+idx), "VIIII", 5) == 0)
        {
            res[t++] = 'I';
            res[t++] = 'X';
            idx += 5;
        }
        if (strncmp((char*)(ptr+idx), "XXXX", 4) == 0)
        {
            res[t++] = 'X';
            res[t++] = 'L';
            idx += 4;

        }
        if (strncmp((char*)(ptr+idx), "LXXXX", 5) == 0)
        {
            res[t++] = 'X';
            res[t++] = 'C';
            idx += 5;

        }
        if (strncmp((char*)(ptr+idx), "CCCC", 4) == 0)
        {
            res[t++] = 'C';
            res[t++] = 'D';
            idx += 4;

        }
              if (strncmp((char*)(ptr+idx), "DCCCC", 5) == 0)
        {
            res[t++] = 'C';
            res[t++] = 'M';
            idx += 5;

        }
        else
        {
            res[t++]=ptr[idx++];
        }
    }
    strcpy(str, res);
}


//Function to add two roman numbers
char* add(char* first, char* second)
{
    static char temp[MAX_ROMAN_STRING_SIZE] = {0};
    static char result[MAX_ROMAN_STRING_SIZE] = {0};

    memset(temp,'\0',MAX_ROMAN_STRING_SIZE);
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

    // Step 2: Concat both numbers together
    strcat(result, temp);

    // Step 3: Sort and combine strings
    sort_and_combine_roman_string(result);

    // Step 4: Substitute any subtractives
    compact_subtractives(result);

    return result;
}
