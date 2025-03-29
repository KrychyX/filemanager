#ifndef TABS_H
#define TABS_H

#include "fileops.h"

// Максимальное количество символов в заголовке вкладки
#define MAX_TAB_TITLE 32

// Структура панели
typedef struct {
    char path[PATH_MAX];      // Текущий путь
    FileEntry* files;         // Массив файлов
    int file_count;          // Количество файлов
    int cursor_pos;         // Позиция курсора
    int scroll_offset;      // Смещение скролла
} Panel;

// Структура вкладки
typedef struct {
    char title[MAX_TAB_TITLE];  // Заголовок вкладки
    Panel left_panel;          // Левая панель
    Panel right_panel;         // Правая панель
    int active_panel;         // 0 = левая, 1 = правая
} Tab;

// Менеджер вкладок
typedef struct {
    Tab* tabs;               // Массив вкладок
    int tab_count;           // Количество вкладок
    int current_tab;         // Индекс текущей вкладки
} TabManager;

// Инициализация менеджера вкладок
void init_tab_manager(TabManager* tm);

// Добавление новой вкладки
void add_new_tab(TabManager* tm, const char* title, const char* path);

// Переключение на следующую вкладку
void switch_to_next_tab(TabManager* tm);

// Очистка ресурсов
void cleanup(TabManager* tm);

#endif