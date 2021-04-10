#include <stdio.h>
//#include "struct.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstring>
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
     msg_t msg;


     char c_send[6] = {'s','e','n','d',':','\0'};
     char c_exit[5] = {'e','x','i','t','\0'};
     string c_string;
     msg_type_t typ;
     char client_msg[MSG_LENGTH];

     int fork_id = fork();

     if(fork_id == 0){// client procsess
       while(1){
         close(fd[READ]);
       cin >> c_string;
       int n = c_string.length();
       char temp_s[n+1];
       strcpy(temp_s, c_string.c_str());
       temp_s[5] = '\0';

          if(temp_s[0] == c_send[0] && temp_s[1] == c_send[1] && temp_s[2] == c_send[2] &&
             temp_s[3] == c_send[3] && temp_s[4] == c_send[4] && temp_s[5] == c_send[5]){
               //cout<<endl<<"hello!";

               int c_string_length = c_string.length();
               typ = REGULAR;
               msg.type = typ;
               c_string.erase(0,5);
               strcpy(temp_s, c_string.c_str());
               //temp_s = temp_s + 5;
               strcpy(msg.message_text, temp_s);
               //cout<<endl<<"msg txt "<<msg.message_text;
               write(fd[WRITE], &msg, 100);
               close(fd[WRITE]);
               // write(fd[WRITE], msg.message_text, n+1);
               // close(fd[WRITE]);
               exit(EXIT_SUCCESS);

          }else{
            if(temp_s[0] == c_exit[0] && temp_s[1] == c_exit[1] && temp_s[2] == c_exit[2] &&
               temp_s[3] == c_exit[3] && temp_s[4] == c_exit[4]){
               cout<<endl<<"exit";
               typ = COMMAND;
               msg.type = typ;
               write(fd[WRITE], &msg, 100);
               close(fd[WRITE]);
               exit(EXIT_SUCCESS);
             }
          }
        }

     }else{//  server procsess
       close(fd[WRITE]);
       while(1){
          read(fd[READ], &msg, 100);

          if(msg.type == COMMAND){
            //cout<<endl<<"exit";
            exit(EXIT_SUCCESS);
          }

          if(msg.type == REGULAR){
          int pidtemp = getpid();
          cout<<endl<<"server:"<<pidtemp<<"  recieved "<<msg.message_text<<" from client:"<<fork_id;
          fork_id = fork();
        }
      }
     }
     return 0;
}
