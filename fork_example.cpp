#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>

/*
 This program illustrates the use of fork and getpid getppid and execve.
 It forks itself creating two child processes.
 It then replaces the current image with a new one (itself), but restarted.
 */

int main (int argc, char *argv[], char *envp[])
{
  int gpid = 0;
  if(argc == 2)
  {
    gpid = atoi(argv[1]);
  } 
  std::cout << getpid() << "::gpid input is: " << gpid << std::endl; 
  std::cout << getpid() << "::ppid returns: " << getppid() << std::endl;
  if(gpid == getppid() || gpid == 0)
  {
    std::cout << getpid() << "::forking 2 child" << std::endl;
    char *new_argv[3] = {"./fork_example.o", "temp", 0};
    char *env[0];
    char buffer[10];
    if(gpid == 0) 
    { 
      sprintf(buffer, "%d", getppid());
    }
    else
    {
      sprintf(buffer, "%d", gpid);
    }
    new_argv[1] = buffer;

    int cpid = fork();
    if(cpid == -1) std::cout << getpid() << "::error creating first child" << std::endl;
    else if (cpid == 0){ 
      if(execve("./fork_example.o", new_argv, env)==-1) perror("can't execve");
    }
    else { 
      std::cout << getpid() << "::first child pid: " << cpid << std::endl;
    }

    cpid = fork();
    if(cpid==-1) std::cout << getpid() << "::error creating second child" << std::endl;
    else if (cpid == 0){
      if(execve("./fork_example.o", new_argv, env)==-1) perror("can't execve");
    }
    else {
      std::cout << getpid() << "::second child pid: " << cpid << std::endl;
    }
  }
  std::cout << getpid() << "::going into main loop" << std::endl;
  while(true) ; 
  return 0;
}
