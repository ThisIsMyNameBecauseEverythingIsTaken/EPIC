#include <stdbool.h>
#include <libc/string.h>
#include <libk/assert.h>
#include <kernel/kmalloc.h>
#include "string.h"

string *string_split(const_string str, const_string delimiter)
{
  size_t length = strlen(str);
  string *parts = kmalloc(length + 5);
  string substr;
  int count = 0;

  for (size_t i = 0; i < strlen(str); i++)
  {
    substr = string_substring_range(str, i, length);

    int pos = string_find(substr, delimiter);
    kfree(substr);

    // TODO: This a hackish and buggy in some cases. (For example: ',,,,' with ',')
    if (pos == -1)
    {
      pos = length;
    }

    parts[count++] = string_substring(str, i, pos);

    i += pos;
  }

  parts[count] = NULL;

  return parts;
}

string string_normalize_spaces(const_string str)
{
  string result = kmalloc(string_length(str));
  char c = 0;
  int r = 0;

  for (size_t i = 0; i < string_length(result); i++)
  {
    while (c == ' ') //replaces two or more spaces by a single space
    {
      c = str[i++];
      if (c != ' ')
        result[r++] = c;
    }
  }

  return result;
}

// TODO: Should use a better algorithm here.
int string_find(const_string str, const_string needle)
{
  for (size_t i = 0; i < strlen(str); i++)
  {
    bool found = true;

    for (size_t j = 0; j < strlen(needle); j++)
    {
      if (str[i] != needle[j])
      {
        found = false;

        break;
      }
    }

    if (found)
    {
      return i;
    }
  }

  return -1;
}

string string_substring(const_string str, int start, int length)
{
  ASSERT(length > 0);

  string substr = kmalloc(length + 1);

  memcpy(substr, &str[start], length);

  substr[length] = '\0';

  return substr;
}

string string_substring_range(const_string str, int start, int end)
{
  ASSERT(start < end);

  return string_substring(str, start, end - start);
}

size_t string_length(const_string str)
{
  return strlen(str);
}