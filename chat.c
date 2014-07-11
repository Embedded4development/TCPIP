#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

/* Easier to alter if defined in one place 
   safere to put named-pipes in /tmp */
#define PIPENAME "/tmp/chatfile.pipe"

/* An empty parameter list means no parameter
   checking, not no parameters! */

void send(void)
{
    char message[256];

    fgets(message , 256 , stdin);

    FILE * f1;
    f1= fopen(PIPENAME, "w");

    if(f1 == NULL) { 
        /* printf writes to stdout
           perror writes to stderr, and includes the error */
        perror("not open ");
        exit(1);
    }

    fprintf(f1 , "%s" , message);
    fclose(f1);
}

//-------------------------------------------------------

void recieve(void)
{
    char message[256];
    FILE * f1;
    f1= fopen(PIPENAME, "r");

    /* You should check EVERY open */
    if (f1 == NULL) {
       perror("not open ");
       exit(1);
    }

    fgets(message , 256 , f1);
    printf("Message is : %s" , message);
    fclose(f1);
}

//------------------------------------------------------

int main(int argc, char *argv[])
{
    int iResult = mkfifo(PIPENAME,0666);
    if (iResult == -1 && errno != EEXIST) {
        perror("Unable to create pipe");
        exit(1);
    }

    pid_t pid;
    pid = fork();

    while(1)
    {
        if( pid == 0) {
            printf("parent");
            send();
        }
        else {
            printf("child");
            recieve();
        }
    }
    return 0;
}
