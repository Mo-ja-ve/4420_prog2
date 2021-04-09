#include <stdio.h>
//#include "struct.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define MSG_LENGTH 100
#define READ 0
#define WRITE 1

using namespace std;

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
          string c_send = "send:";
          string c_exit = "EXIT";
          string temp_s;
          string c_string;
          msg_type_t typ;
          msg_t msg;

          cin >> c_string;
          c_string.copy(temp_s,0,5);
          if(temp_s == c_send){
               typ = REGULAR;
               msg.type = typ;
               strcpy(msg.message_text, c_string);
               cout<<endl<<"msg txt "<<msg.message_text;

          }else{
               cout<<endl<<"not okay";
          }


     }else{
          close(fd[WRITE]);

          //printf("server");
     }

     return 0;
}
