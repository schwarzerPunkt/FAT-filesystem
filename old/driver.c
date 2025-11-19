#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "driver.h"
#include "bootsector.c"
#include "FATentry.c"
#include "directory.c"

#define HIWORD(l)   ((WORD)(l))
#define LOWORD(l)   ((WORD)(((WORD)(l) >> 16) & 0xFFFF))

void main(){

    struct BPB BPB; 
    struct METADATA meta;
    struct CLUSTER_ENTRY clus;
    char* SecBuff = NULL;

    initBPB(&BPB);
    initMeta(&meta);
    initClus(&clus);
    
    meta.Filename = "FAT32disk.img";
    
    setBPB(&BPB, meta.Filename);

    // print BPB fields

    printBPB(&BPB);
    
    // determine the FAT Type

    detFatType(&BPB, &meta);

    meta.BytsPerSec = BPB.BPB_BytsPerSec;
    meta.SecPerClus = BPB.BPB_SecPerClus;

    //calculate first data sector

    meta.FirstDataSector = BPB.BPB_ResvdSecCnt + (BPB.BPB_NumFATs * meta.FATSz) + meta.RootDirSectors;
    
    // read the ROOT DIRECTORY

    DIR* root = NULL;

    // printf("FATType: \t\t%u\n", Meta.FATType);

    if (meta.FATType == 12 || meta.FATType == 16){          // FAT12 and FAT16 root directory

        // compute the first root dir sector number

        meta.FirstRootDirSecNum = BPB.BPB_ResvdSecCnt + (BPB.BPB_NumFATs * BPB.BPB_FATSz16);

        // print the # of root dir sectors and first root dir sector number

        printf("RootDirSectors: \t%u\n", meta.RootDirSectors);
        printf("FirstRootDirSecNum: \t%u\n", meta.FirstRootDirSecNum);

        loadData(meta.Filename, &SecBuff, meta.BytsPerSec * 4, meta.BytsPerSec * meta.FirstRootDirSecNum);

        root = FetchRootDirectory(&meta, SecBuff);

        // cleanup

        free(SecBuff);
        SecBuff = NULL;

    } else {                                                        // FAT32 root directory
        
        root = FetchRootDirectory2(&meta, &BPB);

        // cleanup

        free(SecBuff);
        SecBuff = NULL;
    }

    // print root dir entries
    if (root != NULL)
        printDirectory(root);
}



/*

uint64_t FirstSectorOfCluster(CLUSTER_ENTRY* entry, METADATA* meta){

    /// calculates the first sector of data cluster N

        return ((entry -> clusterNumber - 2) * meta -> SecPerClus) + meta -> FirstDataSector;
}
*/