#include <stdio.h>
#include <stdlib.h>


int
main()
{
    char total[100];
    char freemem[100];
    char buffers[100];
    char cache[100];
    char reclaimable[100];

    float USED_RAM = 0.0;
    int TOTAL_RAM = 0;
    char MorG = 0;
    int t = 0;
    int f = 0;
    int b = 0;
    int ca =0;
    int r = 0;

    int c = 0;

    FILE *fp = fopen("/proc/meminfo", "r");
    if(fp == NULL) {
        perror("/proc/meminfo");
        exit(EXIT_FAILURE);
    }
    // this is a mess to look at but I don't see another alternative

    fscanf(fp, "%*99s %99s %*99s\n", total);

    fscanf(fp, "%*99s %99s %*99s\n", freemem);
    while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s %*99s\n", buffers);

    fscanf(fp, "%*99s %99s %*99s\n", cache);
    for (int i = 0; i < 18; i++) while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s %*99s\n", reclaimable);


    fclose(fp);

    sscanf(total, "%d", &t);      // total

    sscanf(freemem, "%d", &f);       // free

    sscanf(buffers, "%d", &b);    // buffers

    sscanf(cache, "%d", &ca);     // cache

    sscanf(reclaimable, "%d", &r);//reclaimable


    USED_RAM = (t - f - b - ca - r)/1000./1000.;

    TOTAL_RAM = (t/1000/1000);

    if (USED_RAM < 1) {
        MorG = 'M';
        USED_RAM = (USED_RAM * 1000);
    }
    else {
        MorG = 'G';
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
    /*
     * explanation for pragma:
     * we explicitly want to
     * convert to double here.
     * */
    printf("%.1f%c/%dG\n", \
            USED_RAM, MorG, TOTAL_RAM);
#pragma clang diagnostic pop

    return EXIT_SUCCESS;
}
