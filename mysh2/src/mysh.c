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
#include "parser.h"
#include "utils.h"
#include "fs.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <errno.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define BUFF_SIZE 1024
#define FILE_SERVER "./mysh"

void signal_handler(int signo){
	signal(signo, SIG_IGN);
	return;
}
void signal_generator(int pid){
	kill(pid, SIGKILL);
	return;
}
void *server_thread(char** argv){

	int server_socket;
        int client_socket;
	int client_addr_size;

//	int fd1, fd2;
	//fd1 = open(argv[0], O_RDONLY); //read
       // fd2 = dup(fd1);	//write

	struct sockaddr_un server_addr;
        struct sockaddr_un client_addr;

	char buff_rcv[BUFF_SIZE+5];
	char buff_snd[BUFF_SIZE+5];

	if(0 == access(FILE_SERVER, F_OK))
		unlink(FILE_SERVER);

	server_socket = socket(PF_FILE, SOCK_STREAM, 0);

	if(-1 == server_socket)
	{
		printf("server socket error\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, FILE_SERVER);
	
	if(-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))){
		printf("error\n");
		exit(1);
	}

	while(1)
	{
		if(-1 == listen(server_socket, 5))
		{
			exit(1);
		}
		
		client_addr_size = sizeof(client_addr);
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
		if(-1 == client_socket)
		{
			printf("accept error\n");
			exit(1);
		}
		while(1)
		{
			read(client_socket, buff_rcv, BUFF_SIZE);
			printf("[server]receive: %s\n", buff_rcv);

			sprintf(buff_snd, "%d bytes - %s", strlen(buff_rcv), buff_rcv);
			write(client_socket, buff_snd, strlen(buff_snd)+1);
		}
		close(client_socket);
	}
	return 0;
}

void *thread_client(char** argv){
	int client_socket;
	struct sockaddr_un server_addr;
	char *str_send = "";
	char buff[BUFF_SIZE+5];

	client_socket = socket(PF_FILE, SOCK_STREAM, 0);
	if(-1 == client_socket)
	{
		printf("client socket error\n");
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, FILE_SERVER);
	
	if(-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))){
		printf("error\n");
	}
	else
	{
		while(1)
		{
			write(client_socket, str_send, strlen(str_send)+1);
			read(client_socket, buff, BUFF_SIZE);
			printf("receive: %s\n", buff);
			sleep(1);
		}
	}
	close(client_socket);
	return 0;
 }	


static void zombie_handler(){
	wait(0);  
	printf("zombie alert\n");
	return;
}

int main()
{ 
  signal_handler(2);
  signal_handler(20);
  
 // signal(SIGCHLD, (void*)zombie_handler);


  char command_buffer[4096] = { 0, };

  while (fgets(command_buffer, 4096, stdin) != NULL) {
    int argc = -1;
    char** argv = NULL;
    int background = 0;
    int pipe_flag = 0;
    int status;

   //signal(SIGCHLD, (void*)zombie_handler);
   
    parse_command(command_buffer, &argc, &argv);
    
    if(strcmp(command_buffer, "\n") == 0){ 
	continue;
    }

    assert(argv != NULL);
    if (strcmp(argv[0], "exit") == 0) {
	int state;
	pid_t pid;
	pid = waitpid(pid, &state, WUNTRACED);
     if(pid > 0)
	     zombie_handler();
     FREE_2D_ARRAY(argc, argv);
      break;
    }


   //pipe check
   int pipe_index = 0;
   for(int i=0;i<argc;i++){
	  if( strcmp(argv[i], "|") == 0)
		  pipe_index = i;
		  pipe_flag = 1;
   }



     if(strcmp(argv[argc-1], "&") == 0){
            background = 1;
	    free(argv[argc-1]);
            argv[argc-1] = NULL;
            argc--;
     }

    
    struct command_entry* comm_entry = fetch_command(argv[0]);
      if (comm_entry != NULL) {

	      //pwd, background  fork
	      if(strcmp(comm_entry->command_name, "pwd") == 0 && background ==1){

	      int pid2 = fork();

	      if (pid2<0)
		      fprintf(stderr, "fork error\n");

	      else if (pid2 == 0){
		      int ret = comm_entry->command_func(argc, argv);
		      if (ret != 0) 
			      comm_entry->err(ret);
		      FREE_2D_ARRAY(argc, argv);
		      exit(0);
	      }
	      else {
		     signal(SIGCHLD, SIG_IGN); 
	      }
	      }
	      //cd run
	      else{
		      int ret = comm_entry->command_func(argc, argv);
                      if (ret != 0)
                              comm_entry->err(ret);
	      }

      }

      else if (strcmp(argv[0], "kill") == 0 && argv[1] != NULL){
        int pid_kill = atoi(argv[1]);
        signal_generator(pid_kill);
      }
  
     else if (does_exefile_exists(argv[0])) {
     // TODO: Execute the program of argv[0].
     // execv(argv[0], argv);
      int pid = fork();

      if(pid < 0) //error
	     fprintf(stderr, "fork error\n");
      else if(pid == 0){
	      //child 
	      char* path = argv[0];
	      execvp(path, argv);
      }
      else{
	 //parent
	 if(background == 0){
		 waitpid(pid, &status, 0);
		}
	 else{
		signal(SIGCHLD, SIG_IGN);
		 
      }
     }
     }      
      else if (strcmp(argv[0], "fg") == 0) {
            background = 0;
            wait(NULL);
	}
     
      else{
      assert(comm_entry == NULL);
      fprintf(stderr, "%s: command not found.\n", argv[0]);
    }
    FREE_2D_ARRAY(argc, argv);
  }
  return 0;
}
