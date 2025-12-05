#ifndef FAT_VALIDATION_H
#define FAT_VALIDATION_H

#include "fat_types.h"
#include "fat_volume.h"
#include "fat_file.h"
#include <stdlib.h>

#define FAT12_MAX_FILE_SIZE (16 * 1024 * 1024)              // 16 mb
#define FAT16_MAX_FILE_SIZE (2 * 1024 * 1024 * 1024UL)      // 2GB
#define FAT32_MAX_FILE_SIZE (4 * 1024 * 1024 * 1024UL -1)   // 4GB

#define MAX_CLUSTER_CHAIN_LENGTH (1024 * 1024)

fat_error_t fat_validate_cluster_range(fat_volume_t *volume, 
                                       cluster_t cluster);
fat_error_t fat_validate_cluster_chain(fat_volume_t *volume, 
                                       cluster_t start_cluster);
fat_error_t fat_check_fat_consistency(fat_volume_t *volume);
fat_error_t fat_validate_file_size_limits(fat_volume_t *volume, 
                                          uint32_t file_size);
fat_error_t fat_validate_api_parameters_mount(fat_block_device_t *device, 
                                              fat_volume_t *volume);
fat_error_t fat_validate_api_parameters_open(fat_volume_t *volume, 
                                             const char *path, 
                                             int flags, 
                                             fat_file_t **file);
fat_error_t fat_validate_api_parameters_read(fat_file_t *file, void *buffer, 
                                             size_t size);
fat_error_t fat_validate_api_parameters_write(fat_file_t *file, 
                                              const void *buffer, 
                                              size_t size);
fat_error_t fat_propagate_device_error(int device_error);
fat_error_t fat_check_volume_integrity(fat_volume_t *volume);
bool fat_is_valid_cluster_number(fat_volume_t *volume, cluster_t cluster);
uint32_t fat_get_max_file_size(fat_volume_t *volume);

#endif