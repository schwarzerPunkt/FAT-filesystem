#ifndef FAT_DIR_LIST_H
#define FAT_DIR_LIST_H

#include "fat_types.h"
#include "fat_volume.h"
#include "fat_dir.h"

typedef struct {
    fat_volume_t *volume;
    cluster_t dir_cluster;
    cluster_t current_cluster;
    uint32_t current_entry_index;
    uint32_t cluster_offset;
    uint8_t *cluster_buffer;
    bool is_root_fat12;
    uint32_t max_entries;
} fat_dir_t;

typedef struct {
    char short_name[13];
    char long_name[256];
    uint8_t attributes;
    uint32_t file_size;
    uint16_t create_date;
    uint16_t create_time;
    uint16_t modify_date;
    uint16_t modify_time;
    uint16_t access_date;
    cluster_t start_cluster;
    bool is_directory;
    bool is_hidden;
    bool is_readonly;
} fat_dir_entry_info_t;

fat_error_t fat_opendir(fat_volume_t *volume, const char *path, fat_dir_t **dir);

fat_error_t fat_readdir(fat_dir_t *dir, fat_dir_entry_info_t *info);

fat_error_t fat_closedir(fat_dir_t *dir);

void fat_convert_short_name(const uint8_t *short_name, char *output);

fat_error_t fat_load_directory_cluster(fat_dir_t *dir, cluster_t cluster);

void fat_extract_entry_info(const fat_dir_entry_t *entry, const char *long_name, 
                            fat_dir_entry_info_t *info);

#endif