#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //library thread
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ao/ao.h>
#include <string.h>
#include <mpg123.h>

#define BITS 8
void *fuseit( void *ptr );
void *playit( void *ptr );

int main()
{
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6;
    char *simpan1="pytagsfs -o dstfilter='\\.mp3$' /home/cikei/ /home/cikei/musicplayer";
    int  iret1, iret2, iret3, iret4, iret5, iret6;

    iret1 = pthread_create( &thread1, NULL, fuseit, (void*) simpan1); 
    if(iret1)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    pthread_join( thread1, NULL);
    exit(EXIT_SUCCESS);

}

void *fuseit( void *ptr )
{
    char *fusenya;
    fusenya= (char *) ptr;
    system(fusenya);
}
