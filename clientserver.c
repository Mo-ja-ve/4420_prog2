#include <stdio.h>
//#include "struct.h"
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

          close(fd[READ]);

          char c_string[100];
          scanf("%s",c_string);
          int c_str_size=0;
          int c_str_or  =0;
          while(c_string[c_str_size] != '\0'){
               c_str_size++;
               c_str_or = c_str_or || c_string[c_str_size];
          }

          if(c_str_or != 's'||'e'||'n'||'d'||':'){
               printf("ERROR: incorect input");
               return;
          }else{
               printf("%s", c_string);
          }

     }else{
          close(fd[WRITE]);

          printf("server");
     }

     return 0;
}
