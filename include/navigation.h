#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "tabs.h"

// Перемещение курсора вверх/вниз
void move_cursor(Tab* tab, int key);

// Переключение активной панели
void switch_panel(TabManager* tm);

// Открытие выбранного файла/директории
void open_selected(Tab* tab);

#endif