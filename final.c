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
void *playit( void *ptr );//fungsi untuk thread ke 2 buat play dll

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
    
    /*
    iret2 = pthread_create( &thread1, NULL, fuseit, (void*) simpan2); 
    if(iret2)
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }
    */

    pthread_join( thread1, NULL);
//    pthread_join( thread2, NULL);
    exit(EXIT_SUCCESS);

}

void *fuseit( void *ptr ){
    char *fusenya;
    fusenya= (char *) ptr;
    system(fusenya);
}
/*
void *playit( void *ptr){
    char message1[1000];
    char *playyey="play";
    while(scanf("%s",message1)){
    if(strncmp(message,playyey,5)==0){
    
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    mpg123_open(mh, message1[1]);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        ao_play(dev, buffer, done);

    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}*/
