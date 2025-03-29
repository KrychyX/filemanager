#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "tabs.h"

// ����������� ������� �����/����
void move_cursor(Tab* tab, int key);

// ������������ �������� ������
void switch_panel(TabManager* tm);

// �������� ���������� �����/����������
void open_selected(Tab* tab);

#endif