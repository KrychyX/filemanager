#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include "tabs.h"

// Инициализация ncurses (цвета, режимы ввода)
void init_ncurses(void);

// Отрисовка всего интерфейса
void draw_interface(TabManager* tm);

// Отрисовка одной панели
void draw_panel(Panel* panel, int y, int x, int width, int height, bool is_active);

// Отрисовка статус-бара (подсказки клавиш)
void draw_status_bar(void);

#endif