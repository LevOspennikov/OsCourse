#include <signal.h>
#include <stdio.h>
typedef int bool; 

bool sig_caught = 0;

void sig_handler(int signum, siginfo_t* info, void* context){
	if (!sig_caught){
		sig_caught = 1;
		int usr_num; 
		if (signum == SIGUSR1){
			usr_num = 1;
		}
		if (signum == SIGUSR2){
			usr_num = 2;
		}
		if (usr_num > 0){
			printf("SIGUSR%d from %d\n", usr_num, info->si_pid);
		}
	}
}
		
int main(){
	struct sigaction act;
	act.sa_handler = sig_handler;	
	sigset_t set;
	act.sa_flags = SA_SIGINFO; 

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_mask = set;
	
	if (sigaction(SIGUSR1, &act, 0) < 0 || sigaction(SIGUSR2, &act, 0) < 0) { 
		perror("Error \n"); 
	} 

	int t = sleep(10); 
	
	if (!sig_caught) { 
		printf("No signals were caught\n"); 
	} 
	return 0;
}