#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "helpers.h"

// Форматирует размер файла в читаемый вид (KB, MB, GB)
void format_size(off_t size, char* buffer, size_t buf_size) {
    const char* units[] = { "B", "KB", "MB", "GB" };
    int unit_idx = 0;
    double sz = size;

    while (sz >= 1024 && unit_idx < 3) {
        sz /= 1024;
        unit_idx++;
    }

    snprintf(buffer, buf_size, "%.1f %s", sz, units[unit_idx]);
}

// Проверяет, является ли файл исполняемым
bool is_executable(const char* path) {
    struct stat st;
    if (stat(path, &st) == -1) return false;
    return (st.st_mode & S_IXUSR);  // Проверка бита исполнения
}

// Обрезает строку с добавлением "..." (для отображения длинных имён)
void truncate_with_ellipsis(char* str, int max_len) {
    if (strlen(str) <= max_len) return;

    int ellipsis_pos = max_len - 3;
    if (ellipsis_pos < 0) ellipsis_pos = 0;

    str[ellipsis_pos] = '.';
    str[ellipsis_pos + 1] = '.';
    str[ellipsis_pos + 2] = '.';
    str[ellipsis_pos + 3] = '\0';
}

// Возвращает строку с датой модификации файла
void get_modification_time(time_t mtime, char* buffer, size_t buf_size) {
    struct tm* tm_info = localtime(&mtime);
    strftime(buffer, buf_size, "%Y-%m-%d %H:%M", tm_info);
}