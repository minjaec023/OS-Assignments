/**********************************************************************
 * Copyright (C) Jaewon Choi <jaewon.james.choi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 *********************************************************************/
#include "parser.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void parse_command(const char* input,
                   int* argc, char*** argv)
{
  // TODO: Fill it!

  //char* str = strdup(input);
  char* str = (char*)malloc(strlen(input)+1);
  strcpy(str, input);
  char* start = str;
  int i = 0;
  char* ptr = 0;
  int len = strlen(str);
  int quote_flag = 0;

  while (i <= len) {
    if (*str == '"') {
      quote_flag ^= 1;
      *str = '\0';
    }
    if (!quote_flag  &&  isspace(*str)) {
      *str = '\0';
    }
    str++;
    i++;
  }

  str = start;
  i = 0;
  *argc = 0;
  *argv = (char**)malloc(sizeof(**argv));
  while (1) {
    
    while (*str == '\0' && i < len) {
      str++;
      i++;
    }
    if(i >= len) break;
    *argv = (char**)realloc(*argv, (*argc+1+1) * sizeof(**argv));
   // (*argv)[*argc] = strdup(str);
    (*argv)[*argc] = (char*)malloc(strlen(str)+1);
    strcpy((*argv)[*argc], str);
    (*argc)++;
    while (*str) {
      str++;
      i++;
    }
  }
  (*argv)[*argc] = NULL;
  
  free(start);
}
