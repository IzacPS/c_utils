#include <stdio.h>
#include <stdint.h>
//#include "murmur3.h"
#include "fnv.h"
//#include "xxhash.h"
#include <string.h>

int main()
{
    uint64_t mm[2];

    FILE *f = NULL;
    fopen_s(&f, "words.txt", "r");
    FILE *fna = NULL;
    fopen_s(&fna, "fnva.txt", "w");
    
    FILE *xxhash = NULL;
    fopen_s(&xxhash, "xxhash.txt", "w");
    FILE *murmur = NULL;
    fopen_s(&murmur, "murmur.txt", "w");


    if(!f)
        return 1;

    char line[128];
    char data[256];
    for(int i = 0; i < 13120; i++)
    {
        fgets(line, 200, f);
        line[strcspn(line, "\n")] = 0;
        uint64_t line_size = strlen(line);

        sprintf(data, "%lld\n", fnv_64_buf(line, line_size, FNV1A_64_INIT));
        fputs(data, fna);

        //sprintf(data, "%lld\n", XXH64(line, line_size, 0));
        //fputs(data, xxhash);

        //MurmurHash3_x64_128(line, line_size, 0, mm);
        //sprintf(data, "%lld\n", mm[0]);
        //fputs(data, murmur);
    }

    fclose(fna);
    fclose(xxhash);
    fclose(murmur);
    fclose(f);
}