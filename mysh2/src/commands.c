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
#include "commands.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>

static struct command_entry commands[] =
{
  {
    "pwd",
    do_pwd,
    err_pwd
  },
  {
    "cd",
    do_cd,
    err_cd
  }
};

struct command_entry* fetch_command(const char* command_name)
{
  // TODO: Fill it.
  for(int i=0;i<sizeof(commands)/sizeof(commands[0]);i++){
	if(!strcmp(commands[i].command_name, command_name))
		return &commands[i];
  }
  return NULL;
}

int do_pwd(int argc, char** argv)
{
  // TODO: Fill it.
  char buff[1024];
  if(getcwd(buff, sizeof(buff)) != -1){
	  //printf("%s\n",buff);
	  write(1, buff, strlen(buff));
	  write(1, "\n", 1);
	  return 0;
  }

  return -1;
}

void err_pwd(int err_code)
{
  // TODO: Fill it.
}

int do_cd(int argc, char** argv)
{
  // TODO: Fill it.
  int ret = chdir(argv[1]);
  if(ret == -1){
    if(errno == ENOENT)
       return 1;
    else if(errno == ENOTDIR)
       return 2;
  }
  return 0;
}

void err_cd(int err_code)
{
  // TODO: Fill it.
  if(err_code == 1)
	  fprintf(stderr, "cd: no such file or directory\n");
  else if(err_code == 2)
	  fprintf(stderr, "cd: not a directory\n");
}
