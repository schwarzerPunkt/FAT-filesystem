#ifndef FAT_FORMAT_H
#define FAT_FORMAT_H

#include "fat_types.h"
#include "fat_block_device.h"

typedef struct {
    fat_type_t fat_type;
    uint32_t bytes_per_sector;
    uint32_t sectors_per_cluster;
    uint32_t bytes_per_cluster;
    uint32_t reserved_sectors;
    uint32_t num_fats;
    uint32_t fat_size_sectors;
    uint32_t root_entry_count;
    uint32_t total_sectors;
    uint32_t data_sectors;
    uint32_t total_clusters;
    uint32_t root_cluster;
    uint32_t fs_info_sector;
    uint32_t backup_boot_sector;
} fat_format_params_t;

fat_error_t fat_format(fat_block_device_t *device, fat_type_t fat_type, 
                       uint32_t cluster_size, const char *volume_label);

fat_error_t fat_calculate_format_parameters(uint32_t total_sectors, 
                                            uint32_t bytes_per_sector, 
                                            fat_type_t preferred_type, 
                                            uint32_t preferred_cluster_size, 
                                            fat_format_params_t *params);

fat_error_t fat_write_boot_sector(fat_block_device_t *device, 
                                  const fat_format_params_t *params, 
                                  const char *volume_label);

fat_error_t fat_initialize_fat_tables(fat_block_device_t *device, 
                                      const fat_format_params_t *params);

fat_error_t fat_initialize_root_directory(fat_block_device_t *device, 
                                          const fat_format_params_t *params, 
                                          const char *volume_label);

fat_error_t fat_create_fs_info_sector(fat_block_device_t *device, 
                                      const fat_format_params_t *params);

#endif