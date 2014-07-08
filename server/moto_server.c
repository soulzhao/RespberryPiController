#include <wiringPi.h>

#include <time.h>  
#include <stdlib.h>  
#include <signal.h>

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <pthread.h>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#define PORT 			8989
#define BACKLOG 		5   		/* Number of allowed connections */ 
#define MAXDATASIZE 	4096

/**
*  Define the pins of the Stepper motor driver board.
*/
//#define	PIN_ENA 0	// GPIO 0(17) used as ENABLE
#define	PIN_DIR 1	// GPIO 1(18) used as Direction
#define	PIN_CLK 2	// GPIO 2(21) used as CLOCK


/**
*  Define the driection of the Stepper motor.
*/
#define	F_DIR	0	// Forward direction
#define	R_DIR	1	// Reversed direction

/**
*  Define the run status of the Stepper motor.
*/

#define	RS_STP	0	// Stopped
#define	RS_RUN	1	// Running

const char *set_timer_start();
void process_cli(int connectfd,struct sockaddr_in client, int writefd, int readfd);
int setup_clock_timer();

/* function to be executed by the new thread */
void* start_routine(void* arg);

typedef struct{
	int pipe_write_fd;
	int pipe_read_fd;
	int connfd;
	struct sockaddr_in client;
}ARG;

typedef struct{
	int dir; // current direction
	int run; // current status of the motor
	int clk; // current clock
	int interval;
	timer_t* timerid; // timer id
}MotorState, *pMotorState;

MotorState motor_state = {F_DIR, RS_STP, 0, 0, NULL};


void restore_motor_state(){
	motor_state.run = RS_STP;
	motor_state.clk = 0;
	motor_state.dir = F_DIR;
	motor_state.interval = 0;	// Min: 0.5 MS, Max: 100MS(like the second pointer), 500 000 ~ 100 000 000
	motor_state.timerid = NULL;
}

void write_pins(){
	digitalWrite(PIN_CLK, motor_state.clk);
	digitalWrite(PIN_DIR, motor_state.dir);
}

void sig_handler(int signo){  
    motor_state.clk = ~motor_state.clk;
	write_pins();
}

void stop(int signo){
	printf("\nExiting...\n");
	delayMS(1000);
	restore_motor_state();
	write_pins();
    exit(0);
}

void stop_motor(){
	// delete the timer
	if(motor_state.run == RS_RUN){
		timer_delete(*(motor_state.timerid));
		free(motor_state.timerid);
		motor_state.timerid = NULL;
	}
	restore_motor_state();
	write_pins();
}

/* Suspend execution for x milliseconds intervals.
 *  @param ms Milliseconds to sleep.
 */
void delayMS(unsigned int x) { usleep(x * 1000); }

void setup_pi_pins(){
	printf("Setting up Pi's pins ...\n");
	
	int pins[2] = {PIN_DIR, PIN_CLK};
	/* setup pi*/
	if (-1 == wiringPiSetup()) {
		printf("Setup wiringPi failed!");
		exit(-1);
	}
	pinMode(pins[1], OUTPUT);
	pinMode(pins[2], OUTPUT);
	printf("Pi's pins set up successfully!\n");
}

void initilize_motor(){
	printf("Intilizing the step motor ...\n");
	/* setup motor status*/
	restore_motor_state();
	printf("Motor initialize successfully!\n");
}

char *wave_moter(char *command){
		char *pcmd = command;
		char *splt = " ";
		char* buf  = strstr(pcmd, splt);
		char *result = malloc(sizeof(char) * 100);
		
		if(buf == NULL){
			printf("cmd is: %s\n", pcmd);
			if(!strcmp(pcmd, "STOP")){
				delayMS(1000);
				stop_motor();
				strcpy(result, "STOP SUCCESS!\n");
			}else if(!strcmp(pcmd, "EXIT")){
				delayMS(1000);
				stop_motor();
				strcpy(result, "EXITING ...\n");
				//break;
			}else if(!strcmp(pcmd, "START")){
				if(!motor_state.run){
					delayMS(1000);
					puts("delayMS");
					// delete timer first
					if(motor_state.run == RS_RUN){
						timer_delete(*(motor_state.timerid));
						free(motor_state.timerid);
						motor_state.timerid = NULL;
					}
					set_motor_state(1, 'F');
					const char* r = set_timer_start();
					strcpy(result, r);
				}else{
					strcpy(result, "ERROR: MOTOR IS RUNNING!\n");
				}
			}else{
				printf("ERROR COMMAND TYPE!\n");
				strcpy(result, "ERROR COMMAND TYPE!\n");
			}
		}else{ // this should be command start
			buf[0] = '\0';
			if(strcmp(pcmd, "START") != 0){
					strcpy(result, "ERROR COMMAND TYPE!\n");
			}else{
				int interval = 0, param_count = 0; char cdir = 'F';
				do{
					pcmd = buf + 1;
					buf = strstr(pcmd, splt);
					if(buf != NULL) buf[0] = '\0';
					
					if(strlen(pcmd) == 1 && isalpha(*pcmd))
						cdir = *pcmd, param_count++;
					else
						interval = atoi(pcmd), param_count++;
				}while(buf != NULL && param_count <= 2);
					
				// delete timer first
				if(motor_state.run == RS_RUN){
					timer_delete(*(motor_state.timerid));
					free(motor_state.timerid);
					motor_state.timerid = NULL;
				}
				set_motor_state(interval, cdir);
				delayMS(1000);
				const char* r = set_timer_start();
				strcpy(result, r);
			}
		}
		return result;
}

int main(int argc,char* argv[]){
	signal(SIGINT, stop);

	int fd[2], fd2[2];
	pid_t pid;
	int *chld_write_fd = &fd[1];
    	int *prnt_read_fd = &fd[0];
	int *chld_read_fd = &fd2[0];
	int *prnt_write_fd = &fd2[1];
	
	int result = pipe(fd);
	if(result == -1){
		printf("pipe create error\n");
		exit(-1);
	}
	result = pipe(fd2);
	if(result == -1){
		printf("pipe create error\n");
		exit(-1);
	}
	
	pid = fork();
	if(pid == -1){
		printf("fork error\n");
		exit(-1);
	}
	
	if(pid==0){ // Chhild Process
	// refer to http://www.cnblogs.com/ayanmw/archive/2011/12/30/2308155.html
	// http://blog.csdn.net/worshiper/article/details/8193186
		setup_pi_pins();
		initilize_motor();
		char readbuffer[100];
		while(1){
			puts("read pipe");
			int nbytes = read(*chld_read_fd, readbuffer, sizeof(readbuffer));
			if(nbytes){
				readbuffer[nbytes] = '\0';
				//printf("read from pipe: %s\n", readbuffer);
				char * result = wave_moter(readbuffer);
				printf("child wirte pipe: %s", result);
				write(*chld_write_fd, result, strlen(result));
				free(result);
			}
		}
		
	}else{
		// Parent Process		
		printf("set thread now ... \n");
		int listenfd, connectfd; /* socket descriptors */ 
		pthread_t  thread;
		ARG *arg;
		struct sockaddr_in server; /* server's address information */ 
		struct sockaddr_in client; /* client's address information */ 
		socklen_t sin_size; 
		
		bzero(&server, sizeof(server));
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = inet_addr("192.168.1.101");
			server.sin_port = htons(PORT);

		if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("Creating socket failed.\n");
			exit(1);
		}
	 
		if(bind(listenfd, (struct sockaddr*)&server, sizeof(server))){
			printf("Server Bind Port : %d Failed!", PORT);
			exit(1);
		 }

		if(listen(listenfd, BACKLOG) == -1){
			perror("listen() error\n"); 
			exit(1); 
		}

		sin_size = sizeof(struct sockaddr_in);		
		while(1){
			if ((connectfd = accept(listenfd,(struct sockaddr *)&client, &sin_size)) == -1) {
				perror("accept() error\n"); 
				exit(1); 
			} 
			/*  Create thread*/
			arg = malloc(sizeof(ARG));
			arg->connfd = connectfd;
			arg->pipe_write_fd = *prnt_write_fd;
			arg->pipe_read_fd = *prnt_read_fd;
			memcpy((void *)&arg->client, &client, sizeof(client));

			if (pthread_create(&thread, NULL, start_routine, (void*)arg)) {
				perror("Pthread_create() error");
				exit(1);
			}
		}
		close(listenfd);
	}
}

int setup_clock_timer(){
	puts("Setting up clock ...");
	struct sigevent evp;
	struct sigaction act;
	
	/* setup timer action */
	memset(&act, 0, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_RESTART; // refer to http://blog.csdn.net/zhangjingyangguang/article/details/6155119
	sigemptyset(&act.sa_mask); // initialize the signal set
	if (sigaction(SIGUSR1, &act, NULL) == -1){ // setup the signal action
        	perror("fail to sigaction");  
        	return -1;
    	}
	
	/* setup the event */
	memset(&evp, 0, sizeof(struct sigevent));
	evp.sigev_signo = SIGUSR1;
	evp.sigev_notify = SIGEV_SIGNAL;
	
	motor_state.timerid = malloc(sizeof(timer_t));
	if(timer_create(CLOCK_REALTIME, &evp, motor_state.timerid) == -1){  
        	perror("fail to timer_create");  
        	return -1;  
    	}
	return 1;
}

/*
By default, interval set to 1 Ms, FR set to F
*/
void set_motor_state(int interval, char FR){
		if(interval){
			if(interval > 0 && interval <= 100) motor_state.interval = interval * 1000000;
			if(interval < 0) motor_state.interval = 1000000;
			if(interval > 100) motor_state.interval = 100 * 1000000;
		}
		if(FR == 'F') motor_state.dir = F_DIR;
		if(FR == 'R') motor_state.dir = R_DIR;
		motor_state.run = RS_RUN;
}

const char *set_timer_start(){
	puts("setup_clock_timer");
	int rs = setup_clock_timer();
	if(rs){ // create a timmer and stored in motor_state.timerid	
		struct itimerspec it;
		it.it_interval.tv_sec = 0;  
		it.it_interval.tv_nsec = motor_state.interval;
		it.it_value.tv_sec = 1;			    // time to startup  
		it.it_value.tv_nsec = 0;
		//puts("timer_settime");
		if (timer_settime(*(motor_state.timerid), 0, &it, 0) == -1){ 
			perror("fail to timer_settime");
			restore_motor_state();
			return "INTERNAL ERROR: fail to timer_settime!\n";
		}
		
		return "SUCCESS!\n";
	}
	return "FAILED!\n";
}

void process_cli(int connectfd, struct sockaddr_in client, int writefd, int readfd){
	int num;
	char recvbuf[MAXDATASIZE], result[MAXDATASIZE];

	/* prints client's IP */ 
	printf("%s:%d Client was connected\n",inet_ntoa(client.sin_addr), ntohs( client.sin_port) );
	
	char *welcome = "Welcome to use Motor control service!\n";
	send(connectfd, welcome, strlen(welcome), 0); /* send to the client welcome message */ 
	
	while (1) {
		num = recv(connectfd, recvbuf, MAXDATASIZE,0);
		if (num == 0) { continue; }
		if (num == -1) { perror("recv() error\n");  break; }
  
		printf("client send: %s\n",recvbuf);
		recvbuf[num] = '\0';
		write(writefd, recvbuf, strlen(recvbuf));
		//puts("parent reading pipe");
		int cc = read(readfd, result, MAXDATASIZE);
		result[cc] = '\0';
		printf("parent pipe read: %s\n", result);
		send(connectfd, result, strlen(result), 0); /* send to the client welcome message */ 
	}
	close(connectfd); /*  close connectfd */ 
}

void* start_routine(void* arg){
	ARG *info;
	info = (ARG *)arg;

	process_cli(info->connfd, info->client, info->pipe_write_fd, info->pipe_read_fd);

	free((ARG*)arg);
	pthread_exit(NULL);
}
