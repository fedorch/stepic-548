#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void usage(char *name)
{
    printf("usage: %s\n \
        \t-h this message\n \
        \t-c [config file]\n \
        \t--help this message\n \
        \t--config=config_file\n", name);
    return;
}

int main (int argc, char *argv[])
{
    int c;
    while (1)
    {
        static struct option long_opt[] = {
            {"help", 0, 0, 'h'},
            {"config", 1, 0, 'c'},
            {0,0,0,0}
        };
        int optIdx;

        if((c = getopt_long(argc, argv, "c:h", long_opt, &optIdx)) == -1)
            break;
        switch(c)
        {
            case 'h':
                usage(argv[0]);
                return(-1);
            case 'c':
                printf("option 'c' selected, filename: %s\n", optarg);
                return(1);
            default:
                usage(argv[0]);
                return(-1);
        }
    }
    return 0;
}
