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
     string c_exit = "EXIT";
     string c_string;
     msg_type_t typ;
     char client_msg[MSG_LENGTH];

     cin >> c_string;
     int n = c_string.length();
     char temp_s[n+1];
     strcpy(temp_s, c_string.c_str());
     temp_s[5] = '\0';

     int fork_id = fork();
     if(fork_id == 0){// client procsess

          close(fd[READ]);
          if(temp_s[0] == c_send[0] && temp_s[1] == c_send[1] && temp_s[2] == c_send[2] &&
             temp_s[3] == c_send[3] && temp_s[4] == c_send[4] && temp_s[5] == c_send[5]){

               int c_string_length = c_string.length();
               typ = REGULAR;
               msg.type = typ;
               c_string.erase(0,5);
               strcpy(temp_s, c_string.c_str());
               //temp_s = temp_s + 5;
               strcpy(msg.message_text, temp_s);
               //cout<<endl<<"msg txt "<<msg.message_text;
               write(fd[WRITE], msg.message_text, n+1);
               close(fd[WRITE]);

          }else{
               cout<<endl<<"not okay";
          }


     }else{//  server procsess
       close(fd[WRITE]);
       while(1){
          //printf("server");

          int input_read = -1;
          input_read = read(fd[READ], msg.message_text, n+1);
          //cout<<endl<<input_read;
          if(input_read != -1){
            int pidtemp = getpid();
            cout<<endl<<"server:"<<pidtemp<<"  recieved "<<msg.message_text<<" from client:"<<fork_id;
            //close(fd[READ]);
          }
      }
     }
     return 0;
}
