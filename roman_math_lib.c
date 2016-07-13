// File: roman_calc_lib.c 
// Description: Roman arithemetic operations
// Assumption: Only valid roman numerals are passed. Input sanity checking not enabled. Max roman numeral supported is 3999

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "roman_math_lib.h"

static char roman_char[] = "IVXLCDM";
static int decimal_val[] = {1, 5, 10, 50, 100, 500, 1000};

static char roman_compact[] = "VXLCDM";
static char* roman_xtnd[] = {"IIII","VIIII","XXXX","LXXXX","CCCC","DCCCC"};

static int decimal_num[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
static char* roman_str[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

#define MAX_ROMAN_STRING_SIZE 50
#define MAX_SYMBOLS_SUPPORTED 7

static int get_index(char ch, char arr[])
{
    for(int idx = 0; idx < MAX_SYMBOLS_SUPPORTED; idx++)
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
    int ch_count[MAX_SYMBOLS_SUPPORTED] = {0};
    int length = strlen(src);

    // get the count of each symbols 
    for(int idx = 0; idx < length; idx++)
    {
        ch_count[get_index(src[idx], roman_char)]++;
    }

    // combine symbols if required
    for(int idx = 0; idx < MAX_SYMBOLS_SUPPORTED; idx++)
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
    for(int idx = MAX_SYMBOLS_SUPPORTED - 1; idx >= 0; idx--)
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

static int roman_to_decimal(char* str)
{
    int decimal_num = 0;
    int temp = 0;
    int prev_num = 0;

    for(int idx = strlen(str) - 1; idx >= 0; idx--)
    {
        int cnt = get_index(str[idx], roman_char);
        temp = decimal_val[cnt];

        if ( temp < prev_num)
        {
            decimal_num -= temp;
        }
        else
        {
            decimal_num += temp;
        }
        prev_num = temp;
    }
    return decimal_num;
}

static char* decimal_to_roman( int number)
{
    int num = number;
    int cnt = 0;
    static char temp[MAX_ROMAN_STRING_SIZE] = {0};
    memset(temp,'\0',MAX_ROMAN_STRING_SIZE);

    for (int idx = 0;idx < sizeof(decimal_num)/sizeof(int); idx++)
    {
        while(num >= decimal_num[idx])
        {
            strcat((char*)(temp+cnt), roman_str[idx]);
            cnt += strlen(roman_str[idx]);
            num -= decimal_num[idx];
        }
    }
    return temp;
}

//Function to add two roman numbers
// Input sanity checking not enabled. Use valid arguments
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

// Function to subtract two roman numbers
// Input sanity checking not enabled. Use valid arguments
char* subtract(char* first, char* second)
{
    // Step 1 : Convert to decimal
    int num1 = roman_to_decimal(first);
    int num2 = roman_to_decimal(second);

    // Step 2: Subtract the numbers in decimal
    int diff = num1 - num2;

    // Step 3: Convert from decimal to roman
    if ( diff <= 0 )
    {
        printf("Invalid arguments passed....\n");
        return NULL;
    }
    else
    {
        return decimal_to_roman(diff);
    }

}
