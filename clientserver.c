#include <stdio.h>
//#include "struct.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include<sys/wait.h>

#define MSG_LENGTH 100
#define READ 0
#define WRITE 1

using namespace std;
//  type defs structs for message passting
typedef enum {
     REGULAR,
     COMMAND
} msg_type_t;

typedef struct msg {
     msg_type_t type;
     char message_text[MSG_LENGTH];
}msg_t;

//  written by Andriy Kalinichenko (4,9,2021)
int main(){
    //creation of file discriptors for pipe, and calling of pipe
     int fd[2];
     pipe(fd);
     int result;
     msg_t msg;

     // char arrays to check if inputs are valid, will be tested against later
     char c_send[6] = {'s','e','n','d',':','\0'};
     char c_exit[5] = {'e','x','i','t','\0'};

     //string used to take in user input
     string c_string;

     //creation of message struct
     msg_type_t typ;
     char client_msg[MSG_LENGTH];

     //we call for to create child proccess
     int fork_id = fork();

     if(fork_id == 0){// client procsess
       while(1){

      //close end of pipe which we will not use
       close(fd[READ]);

       //below we take in input into a string, then convert it to char array so we can ceck if input is valid or not
       cout<<endl<<"hello, please input either send:message or exit: ";
       cin >> c_string;
       int n = c_string.length();
       char temp_s[n+1];
       strcpy(temp_s, c_string.c_str());
       temp_s[5] = '\0';

          //checking to see if it's a send case
          if(temp_s[0] == c_send[0] && temp_s[1] == c_send[1] && temp_s[2] == c_send[2] &&
             temp_s[3] == c_send[3] && temp_s[4] == c_send[4] && temp_s[5] == c_send[5]){

               //below we remove it send: portion of the string and send it to server, also set enum to REGULAR
               int c_string_length = c_string.length();
               typ = REGULAR;
               msg.type = typ;
               c_string.erase(0,5);
               strcpy(temp_s, c_string.c_str());

               strcpy(msg.message_text, temp_s);

               write(fd[WRITE], &msg, 100);
               close(fd[WRITE]);

          }else{// checking to see if it's an exit case
            if(temp_s[0] == c_exit[0] && temp_s[1] == c_exit[1] && temp_s[2] == c_exit[2] &&
               temp_s[3] == c_exit[3] && temp_s[4] == c_exit[4]){
              //exit command, we set enum and send it to server
               typ = COMMAND;
               msg.type = typ;
               write(fd[WRITE], &msg, 100);
               //close(fd[WRITE]);
               exit(EXIT_SUCCESS);
             }else{
               cout<<endl<<"WARNING: INVALID INPUT";
             }
        }
      }

     }else{//  server procsess

       // close end of pipe we shall not use
       close(fd[WRITE]);
       while(1){
          //  we read from child processe
          read(fd[READ], &msg, 100);

          // in case of exit command
          if(msg.type == COMMAND){

            exit(EXIT_SUCCESS);
          }
          // regular command
          if(msg.type == REGULAR){
          int pidtemp = getpid();
          cout<<endl<<"server:"<<pidtemp<<"  recieved "<<msg.message_text<<" from client:"<<fork_id;
        }

      }
     }
     return 0;
}
