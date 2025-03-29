#include <unistd.h>      // Для chdir()
#include <sys/stat.h>    // Для stat()
#include <dirent.h>      // Для opendir()
#include <stdlib.h>      // Для system()
#include <string.h>      // Для strncpy()
#include <limits.h>      // Для PATH_MAX
#include "navigation.h"
#include "ui.h"
#include "fileops.h"
#include "helpers.h"

// Перемещение курсора вверх/вниз
void move_cursor(Tab* tab, int key) {
    Panel* active_panel = (tab->active_panel == 0) ? &tab->left_panel : &tab->right_panel;

    switch (key) {
    case KEY_UP:
        if (active_panel->cursor_pos > 0) {
            active_panel->cursor_pos--;
            // Если курсор уходит за верх видимой области, скроллим вверх
            if (active_panel->cursor_pos < active_panel->scroll_offset) {
                active_panel->scroll_offset = active_panel->cursor_pos;
            }
        }
        break;

    case KEY_DOWN:
        if (active_panel->cursor_pos < active_panel->file_count - 1) {
            active_panel->cursor_pos++;
            // Если курсор уходит за низ видимой области, скроллим вниз
            int visible_items = LINES - 5;  // Высота панели
            if (active_panel->cursor_pos >= active_panel->scroll_offset + visible_items) {
                active_panel->scroll_offset++;
            }
        }
        break;
    }
}

// Переключение между левой и правой панелью
void switch_panel(TabManager* tm) {
    Tab* current_tab = &tm->tabs[tm->current_tab];
    current_tab->active_panel = !current_tab->active_panel;  // 0 ↔ 1
}

// Открытие выбранного файла или папки
void open_selected(Tab* tab) {
    Panel* active_panel = (tab->active_panel == 0) ? &tab->left_panel : &tab->right_panel;

    // Если нет файлов - выходим
    if (active_panel->file_count == 0) return;

    FileEntry* selected = &active_panel->files[active_panel->cursor_pos];
    char full_path[PATH_MAX];
    snprintf(full_path, PATH_MAX, "%s/%s", active_panel->path, selected->name);

    // Если это папка - заходим в неё
    if (selected->is_dir) {
        // Обновляем путь в активной панели
        strncpy(active_panel->path, full_path, PATH_MAX - 1);
        // Пересканируем директорию
        scan_directory(active_panel);
        // Сбрасываем позицию курсора
        active_panel->cursor_pos = 0;
        active_panel->scroll_offset = 0;
    }
    // Если это файл - открываем во внешней программе
    else {
        // Для текстовых файлов - через less
        if (is_text_file(full_path)) {
            char cmd[PATH_MAX + 10];
            snprintf(cmd, PATH_MAX + 10, "less \"%s\"", full_path);
            endwin();  // Временно выключаем ncurses
            system(cmd);
            refresh();  // Возвращаем ncurses
        }
        // Для изображений - через xdg-open
        else if (is_image_file(full_path)) {
            char cmd[PATH_MAX + 10];
            snprintf(cmd, PATH_MAX + 10, "xdg-open \"%s\"", full_path);
            system(cmd);
        }
    }
}

// Вспомогательная функция: проверка, является ли файл текстовым
static bool is_text_file(const char* path) {
    // Простая проверка по расширению (можно заменить на magic.h для точного определения)
    const char* ext = strrchr(path, '.');
    if (!ext) return false;

    const char* text_exts[] = { ".txt", ".c", ".h", ".cpp", ".md", ".log", NULL };
    for (int i = 0; text_exts[i]; i++) {
        if (strcmp(ext, text_exts[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Вспомогательная функция: проверка на изображение
static bool is_image_file(const char* path) {
    const char* ext = strrchr(path, '.');
    if (!ext) return false;

    const char* image_exts[] = { ".jpg", ".png", ".gif", ".bmp", ".svg", NULL };
    for (int i = 0; image_exts[i]; i++) {
        if (strcmp(ext, image_exts[i]) == 0) {
            return true;
        }
    }
    return false;
}