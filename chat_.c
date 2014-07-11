#include<stdio.h>
#include <sys/stat.h>
#include<unistd.h>

/*
void send()
  {
    char message[256];
    fgets(message , 256 , stdin);
    //printf("Message is : %s" , message);
    FILE * f1;
    f1= fopen("chatfile.txt", "w");
   if(f1== NULL)
   {
   printf("not open ");
   }
    fprintf(f1 , "%s" , message);
    fclose(f1);
  } 
  //-------------------------------------------------------
void recieve()
  {
    char message[256];
    FILE * f1;
    f1= fopen("chatfile.txt", "r");
    fgets(message , 256 , f1);
    printf("Message is : %s" , message);
    fclose(f1);
   }
   //-------------------------------------------------------
int file_size()
  {
    struct stat st;
    stat("chatfile.txt" , &st);
    int size = st.st_size;
    return size;
  }
  //------------------------------------------------------

*/
int main()
{
int size =0;

//printf("%d" , getpid());
pid_t pid;
pid = fork();
//while(1)
{
if( pid == 0)

   {
   printf("parent\n");
  // send();
    }
else 
  {
   printf("child\n");
  // recieve();
  }
}     


}
