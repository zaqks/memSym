#include <stdlib.h>
#include <strings.h>

#define MAX_STR_LEN 32
// 8 backspace
// 13 is enter

void mergeStr(char *word, const char *add)
{
    if (strlen(word) - strlen(word) < MAX_STR_LEN)
    {
        word[strlen(word)] = *add;
    }
};

void deleteLastChar(char *word)
{
    if (strlen(word) > 0)
    {
        word[strlen(word) - 1] = *"\0";
    }
}
