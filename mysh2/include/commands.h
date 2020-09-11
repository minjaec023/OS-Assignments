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
#ifndef COMMANDS_H_
#define COMMANDS_H_

typedef int (*command_t)(int, char**);
typedef void (*command_error_handler)(int);

struct command_entry
{
  const char* command_name;
  command_t command_func;
  command_error_handler err;
};

struct command_entry* fetch_command(const char* command_name);

int do_pwd(int argc, char** argv);
void err_pwd(int err_code);

int do_cd(int argc, char** argv);
void err_cd(int err_code);

#endif // COMMANDS_H_
