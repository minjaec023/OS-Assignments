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
#include "fs.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int does_exefile_exists(const char* path)
{
  // TODO: Fill it!
  struct stat st;
  if(stat(path, &st) == 0 && st.st_mode & S_IXUSR && S_ISREG(st.st_mode))
	 return 1;
    char* env_path = getenv("PATH");
    char* str = (char*)malloc(strlen(env_path)+1);
    strcpy(str, env_path);
    char name[1024];
    char* token = strtok(str, ":");

    while (token) {
        snprintf(name, sizeof(name), "%s/%s", token, path);
        
        if(stat(name, &st) == 0 && st.st_mode & S_IXUSR && S_ISREG(st.st_mode)){
		free(str);
        	 return 1;}
        token = strtok(NULL, ":");
    }
   free(str);
   
  
  return 0;
}
