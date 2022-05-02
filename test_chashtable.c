#include "chashtable.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>


int main()
{

    printf("%d", sizeof("helloword!"));
    // LARGE_INTEGER frequency;
    // LARGE_INTEGER start;
    // LARGE_INTEGER end;
    // double interval;
    // double ns_per_count = 1.0e9 / (double)(frequency.QuadPart);

    // struct string * vec = calloc(13120, sizeof (struct string));

    // // QueryPerformanceFrequency(&frequency);

    // FILE *f = NULL;
    // fopen_s(&f, "words.txt", "r");

    // if(!f)
    //     return 1;

    // chash_table_st *hash_table;

    // chash_table_init(hash_table, uint64_t, 16000);

    // char line[128];
    // for(int i = 0; i < 13120; i++)
    // {
    //     fgets(line, 200, f);
    //     line[strcspn(line, "\n")] = 0;
    //     uint32_t size = strlen(line);
    //     vec[i].data = _strdup(line);
    //     vec[i].size = size;
    // }

    // for(int i = 0; i < 13120; i++)
    // {
    //     chash_table_add(hash_table, vec[i].data, vec[i].size, i);
    // }

    // for(uint32_t count = 0; count < 10; count++)
    // {
    //     //chash_table_init(hash_table, uint64_t, 16000);
    //     QueryPerformanceCounter(&start);
    //     for(int i = 0; i < 13120; i++)
    //     {
    //         //chash_table_add(hash_table, CTABLE_KEY(*vec[i].data, vec[i].size), i);
    //         void *data = chash_table_get(hash_table, vec[i].data, vec[i].size);
    //     }
    //     QueryPerformanceCounter(&end);
    //     interval = (double) (1000*(end.QuadPart - start.QuadPart)) / frequency.QuadPart;
    //     //chash_table_finish(hash_table);
    //     printf("tempo de execução : %fms\n", interval);
    // }

    // fclose(f);
   // chash_table_finish(hash_table);

    //printf("%lld", sizeof(long long));
}

