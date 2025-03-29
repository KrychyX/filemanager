#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include "tabs.h"

// ������������� ncurses (�����, ������ �����)
void init_ncurses(void);

// ��������� ����� ����������
void draw_interface(TabManager* tm);

// ��������� ����� ������
void draw_panel(Panel* panel, int y, int x, int width, int height, bool is_active);

// ��������� ������-���� (��������� ������)
void draw_status_bar(void);

#endif