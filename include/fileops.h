#ifndef FILEOPS_H
#define FILEOPS_H

#include <stdbool.h>
#include "tabs.h"

// Структура для хранения информации о файле
typedef struct {
    char name[256];  // Имя файла
    bool is_dir;     // Это директория?
    off_t size;      // Размер в байтах
    time_t mtime;    // Время изменения
} FileEntry;

// Сканирует директорию и заполняет панель файлами
void scan_directory(Panel* panel);

// Сравнение файлов для сортировки (qsort)
int compare_files(const void* a, const void* b);

// Инициализация панели с указанным путем
void init_panel(Panel* panel, const char* path);

#endif