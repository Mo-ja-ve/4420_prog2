#include <stdio.h>
#include "struct.h"
#include <fcntl.h>
#include <unistd.h>

#define MSG_LENGTH 100
#define READ 0
#define WRITE 1

typedef enum {
     REGULAR,
     COMMAND
} msg_type_t;

typedef struct msg {
     msg_type_t type;
     char message_text[MSG_LENGTH];
}msg_t;


int main(){

     int fd[2];
     pipe(fd);

     if(fork() != 0){// client procsess
          char c_string[100];
          scanf("%s",c_string);
          printf("%s", c_string);

          close(fd[READ]);

     }else{

          printf("server");
     }

     return 0;
}
