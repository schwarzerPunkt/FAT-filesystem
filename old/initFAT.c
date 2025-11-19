
/*
void initFAT(AUX* AUX, BPB* BPB){

    /// initialises a new fat

    AUX -> RootDirSectors = ((BPB -> BPB_RootEntCnt * 32) + (BPB -> BPB_BytsPerSec - 1)) / BPB -> BPB_BytsPerSec;
    DWORD TmpVal1 = AUX -> DskSize - (BPB -> BPB_ResvdSecCnt + AUX -> RootDirSectors);
    DWORD TmpVal2 = (256 * BPB -> BPB_SecPerClus) + BPB -> BPB_NumFATs;

    if(AUX -> FATType == 32)
        TmpVal2 = TmpVal2 / 2;
    
    AUX -> FATSz = (TmpVal1 + (TmpVal2 - 1)) / TmpVal2;

    if (AUX -> FATType == 32){
        BPB -> BPB_FATSz16 = 0;
        BPB -> BPB_FATSz32 = AUX -> FATSz;

    } else {
        BPB -> BPB_FATSz16 = LOWORD(AUX -> FATSz);
        // no BPB_FATSz32 in FAT16 BPB
    }
}

*/