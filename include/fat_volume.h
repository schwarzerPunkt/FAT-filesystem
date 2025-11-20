#ifndef FAT_VOLUME_H
#define FAT_VOLUME_H

#include <stdint.h>
#include <stdbool.h>
#include "fat_types.h"
#include "fat_boot.h"
#include "fat_block_device.h"

// volume structure

typedef struct{
    fat_block_device_t *device;
    fat_boot_sector_t boot_sector;
    fat_type_t type;

    // cached filesystem parameters
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint32_t bytes_per_cluster;
    
    uint16_t reserved_sector_count;
    uint8_t num_fats;
    uint32_t fat_size_sectors;

    uint32_t root_entry_count;
    uint32_t root_cluster;

    uint32_t total_sectors;             // total volume size
    uint32_t total_clusters;            // number of data clusters

    // important sector offsets
    uint32_t fat_begin_sector;
    uint32_t data_begin_sector;
    uint32_t root_dir_sectors;

    // fat cache

    uint8_t *fat_cache;                 // pointer to the allocated FAT buffer
    uint32_t fat_cache_size;            // size in bytes
    bool fat_dirty;
} fat_volume_t;

fat_error_t fat_mount(fat_block_device_t *device, fat_volume_t *volume);
fat_error_t fat_flush(fat_volume_t *volume);
fat_error_t fat_unmount(fat_volume_t *volume);

#endif