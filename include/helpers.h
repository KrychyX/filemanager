#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

// Конвертация размера в читаемый формат (KB/MB/GB)
void format_size(off_t size, char* buffer, size_t buf_size);

// Проверка: является ли файл исполняемым
bool is_executable(const char* path);

// Обрезка строки с добавлением "..."
void truncate_with_ellipsis(char* str, int max_len);

#endif