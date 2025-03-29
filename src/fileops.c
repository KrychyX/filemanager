#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"

void scan_directory(Panel* panel) {
    DIR* dir = opendir(panel->path);
    if (!dir) {
        panel->file_count = 0;
        panel->files = NULL;
        return;
    }

    // Первый проход: подсчёт файлов
    struct dirent* entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            count++;
        }
    }
    rewinddir(dir);

    // Выделение памяти
    panel->files = realloc(panel->files, count * sizeof(FileEntry));
    panel->file_count = count;

    // Второй проход: заполнение данных
    int idx = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        FileEntry* fe = &panel->files[idx];
        strncpy(fe->name, entry->d_name, 255);
        fe->name[255] = '\0';

        char full_path[PATH_MAX];
        snprintf(full_path, PATH_MAX, "%s/%s", panel->path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0) {
            fe->is_dir = S_ISDIR(st.st_mode);
            fe->size = st.st_size;
            fe->mtime = st.st_mtime;
        }
        idx++;
    }
    closedir(dir);

    qsort(panel->files, count, sizeof(FileEntry), compare_files);
}

int compare_files(const void* a, const void* b) {
    const FileEntry* fa = a, * fb = b;
    if (fa->is_dir && !fb->is_dir) return -1;
    if (!fa->is_dir && fb->is_dir) return 1;
    return strcasecmp(fa->name, fb->name);
}

void init_panel(Panel* panel, const char* path) {
    strncpy(panel->path, path, PATH_MAX - 1);
    panel->path[PATH_MAX - 1] = '\0';
    panel->files = NULL;
    panel->file_count = 0;
    panel->cursor_pos = 0;
    panel->scroll_offset = 0;
    scan_directory(panel);
}