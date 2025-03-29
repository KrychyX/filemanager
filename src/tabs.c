#include <stdlib.h>
#include "tabs.h"

// Инициализация менеджера вкладок
void init_tab_manager(TabManager* tm) {
    tm->tabs = NULL;      // Пока нет вкладок
    tm->tab_count = 0;    // Количество вкладок = 0
    tm->current_tab = 0;  // Текущая вкладка (не выбрана)
}

// Добавление новой вкладки
void add_new_tab(TabManager* tm, const char* title, const char* path) {
    // Увеличиваем массив вкладок на 1
    tm->tabs = realloc(tm->tabs, (tm->tab_count + 1) * sizeof(Tab));

    // Настраиваем новую вкладку
    Tab* new_tab = &tm->tabs[tm->tab_count];
    strncpy(new_tab->title, title, 31);  // Копируем заголовок

    // Инициализируем левую и правую панели
    init_panel(&new_tab->left_panel, path);
    init_panel(&new_tab->right_panel, path);
    new_tab->active_panel = 0;  // Активна левая панель

    tm->tab_count++;             // Увеличиваем счётчик
    tm->current_tab = tm->tab_count - 1;  // Переключаемся на новую вкладку
}

// Переключение на следующую вкладку
void switch_to_next_tab(TabManager* tm) {
    tm->current_tab = (tm->current_tab + 1) % tm->tab_count;
}