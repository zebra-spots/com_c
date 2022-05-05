#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Win() 
{
    int status = 0;
    printf("Unreachable print statement");
    return status;
}

int Usage(char * sProg)
{
    printf("Usage:\n %s <compareString>\n", sProg);
    return 1;
}

int Vuln(char * sCompare)
{
    int isAdmin = 0;
    int status = 1;
    char sTest[20] = "Hello World";
    // TODO: put in the super-secret check insted of this strcpy()
    strcpy(sTest, sCompare);
    if (isAdmin) 
    {
        status = Win();
    }
    return status;
}

int main(int argc, char * argv[])
{
    int status = 1;
    // Shows what argc and argv means
    //printf("This is argc1: %d \n", argc);
    //printf("This is argv0: %s \n", argv[0]);
    //printf("This is argv1: %s \n", argv[1]);
    //printf("This is argv2: %s \n", argv[2]);
    if (argc != 2)
    {
        status = Usage(argv[0]);
    }
    else
    {
        status = Vuln(argv[1]);
    }
    
    return status;
}
