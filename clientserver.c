#include <stdio.h>
//#include "struct.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
     int result;

     if(fork() != 0){// client procsess

          close(fd[READ]);

          char c_string[100];
          char c_send[] = "send";
          scanf("%s",c_string);

          result = strcmp(c_string, c_send);

          if(c_str_or != 's'||'e'||'n'||'d'||':'){
               printf("ERROR: incorect input");
               return 0;
          }else{
               printf("%s", c_string);
          }

     }else{
          close(fd[WRITE]);

          printf("server");
     }

     return 0;
}
