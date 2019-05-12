//bismillah

#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#include<ao/ao.h>
#include<mpg123.h>

#include<termios.h>

#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<dirent.h>

#include<stdio.h>
#include<string.h>

#define BITS 8


int tampilan_menu = 0;
int tampilan_play = 0;
int print_display = 0;

int i, j = 0;
char song[1000][1000];
char current[1000];

char user_input;

int flag_play = 0;
int flag_pause = 0;
int flag_stop = 0;
int flag_close = 0;
pthread_t tid1, tid2, tid3, tid4;

int getch()
{
    struct termios oldt, newt;
    int inp;

    tcgetattr (STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newt);
    inp = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return inp;
}

int plays(char argv[])
{
    while(1)
    {
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

        // initializations
        ao_initialize ();
        driver = ao_default_driver_id ();
        mpg123_init ();
        mh = mpg123_new (NULL, &err);
        buffer_size = mpg123_outblock(mh);
        buffer = (unsigned char*) malloc (buffer_size * sizeof(unsigned char));

        // open the file and get the decoding format
        mpg123_open (mh, argv);
        mpg123_getformat (mh, &rate, &channels, &encoding);

        // set the output format and open the output device
        format.bits = mpg123_encsize(encoding) * BITS;
        format.rate = rate;
        format.channels = channels;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;
        dev = ao_open_live (driver, &format, NULL);

        // decode and play
        while (mpg123_read (mh, buffer, buffer_size, &done) == MPG123_OK)
        {
            ao_play(dev, buffer, done);
            if(flag_stop == 1)
                break;
            while (flag_pause == 1)
            {
                printf("\r");
                if(flag_pause == 0)
                    break;
            }
        }
        flag_stop = 0;

        // clean up
        free(buffer);
        ao_close(dev);
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        ao_shutdown();
        break;
    }
}

void* fitur (void *arg)
{
    while(1)
    {
        tampilan_menu = 1;

        user_input = getch(); 
        
        if (user_input == '1') //print playlistnya
        {
            tampilan_menu = 0;
            system ("clear");
            printf("\r");
            print_display = 1;

            user_input = getch(); //nunggu input
            if (user_input == '1') //Back
            {
                print_display = 0;
                tampilan_menu = 1;
            }
        }

        else if (user_input == '2') //mulai lagunya
        {
            tampilan_menu = 0;
            tampilan_play = 1;

            int nomor = 0, judul_lagu = 0;

            while(1)
            {
                printf("\r");
                judul_lagu = 0;

                while (song[nomor][judul_lagu] != '\0')
                {
                    sprintf(current, "%s%c", current, song[nomor][judul_lagu]);
                    judul_lagu++;
                }

                flag_play = 1;
                tampilan_play = 1;


                user_input = getch(); 
                if (user_input == '1') //Pause
                {
                    if (flag_pause == 0) //mengepause
                    {
                        flag_pause = 1;
                        current[0]='\0';
                    }

                    else if (flag_pause == 1) //meresume
                    {
                        flag_pause = 0;
                        current[0]='\0';
                    }

                }

                else if (user_input == '2') //Stop
                {
                    flag_stop = 1;
                    flag_play = 0;
                    current[0]='\0';
                    break;
                }
            }
        }

        else if (user_input == '3') //tutup
        {
            printf("Player ditutup.\n");
            printf("\r");
            flag_close = 1;
            break;
        }
    }
}

void* mulai (void *arg)
{
    while(1)
    {
        printf("\r");
        if(flag_play == 1)
            plays(current);
    }
}

void* display (void *arg)
{
    while(1)
    {
        printf("\r");
        if(tampilan_menu == 1)
        {
            printf("Fitur mp3 player:\n");
            printf("1. Tampilkan Playlist\n");
            printf("2. Mainkan lagu\n3. Tutup player\n\n");
            printf("Pilihan Anda:\n");
            sleep(1);
            system("clear");
        }

        if(tampilan_play == 1)
        {
            printf("Memainkan : %s\n", current);
            printf("1. Pause/play\n");
            printf("2. Stop\n");
            sleep(1);
            system("clear");
        }

        if (print_display == 1)
        {
            printf("\r");
            printf("Daftar lagu :\n\n");

            DIR *d;
            struct dirent *dir;
            d = opendir(".");

            if(d)
            {
                while ((dir = readdir(d)) != NULL) 
                {
                    char files[100];

                    int a, b;

                    strcpy (files, dir->d_name);
                    if ((files [strlen(files)-3] == 'm') && (files [strlen(files)-2] == 'p') && (files [strlen(files)-1] == '3'))
                    {
                        for(a = 0; a < strlen(files); a++) 
                            song[b][a] = files[a];

                        for(a = 0; a < strlen(files); a++) 
                            printf("%c", song[b][a]);

                        b++;
                        printf("\n");
               }
              }
                closedir(d);
            }

            sleep(1);
            system("clear");
        }
}
}

void* selesai (void *arg)
{
    printf("\r");
    while (flag_close == 0)
    {
        printf("\r");

        if(flag_close == 1)
            break;
    }

    pthread_kill(tid1, SIGKILL);
    pthread_kill(tid2, SIGKILL);
    pthread_kill(tid3, SIGKILL);
    pthread_kill(tid4, SIGKILL);
}

int main(void)
{
    pthread_create(&(tid1), NULL, fitur, NULL);
    pthread_create(&(tid2), NULL, mulai, NULL);
    pthread_create(&(tid3), NULL, display, NULL);
    pthread_create(&(tid4), NULL, selesai, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    return 0;

}

//gcc -O2 -pthread -o player lifplayer.c -lmpg123 -lao
