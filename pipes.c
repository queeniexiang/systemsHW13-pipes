/* 
Queenie Xiang
Systems pd5
HW13 -- Check your pipes for leaks
2017-11-20
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
  //NOTE: 0 is the input/read side, 1 is the output/write side
  
  int C_fds[2];
  int P_fds[2]; 
  int f;

  //creating pipes
  pipe(P_fds);
  pipe(C_fds);

  f = fork();

  if (f == 0) {
     printf("***************************\n");
     printf("Child active here!\n");
     
     int num_received;
     //reading the number received from parent
     read(P_fds[0], &num_received, sizeof(num_received));
     printf("[Child] Received this number: %d\n", num_received);
     
     num_received += 100;
     printf("[Child] New number to be sent: %d\n", num_received);

     //closing the input/read side 
     close(C_fds[0]);
     
     //writing to the output/write side
     printf("Child sending new number through pipe...\n");
     write(C_fds[1], &num_received, sizeof(num_received));
     
     printf("Child is done!\n"); 
     printf("***************************\n");   
   }

  else {
     printf("***************************\n");
     printf("Parent active here!\n");
     
     //closing the input/read side
     close (P_fds[0]);

     int num_to_send = 55; 
     //writing to the output/write side
     printf("[Parent] Sending %d through pipe to child...\n", num_to_send);
     write(P_fds[1], &num_to_send, sizeof(num_to_send)); 
     printf("***************************\n");

     int num_received;
     //reading the number received from child
     read(C_fds[0], &num_received, sizeof(num_received));
     printf("[Parent] Received this number from child: %d\n", num_received);
     
     printf("Parent is done!\n");
     printf("***************************\n");    
   }
  
  return 0; 
}


  
