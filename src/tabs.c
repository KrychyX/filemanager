#include <stdlib.h>
#include "tabs.h"

// ������������� ��������� �������
void init_tab_manager(TabManager* tm) {
    tm->tabs = NULL;      // ���� ��� �������
    tm->tab_count = 0;    // ���������� ������� = 0
    tm->current_tab = 0;  // ������� ������� (�� �������)
}

// ���������� ����� �������
void add_new_tab(TabManager* tm, const char* title, const char* path) {
    // ����������� ������ ������� �� 1
    tm->tabs = realloc(tm->tabs, (tm->tab_count + 1) * sizeof(Tab));

    // ����������� ����� �������
    Tab* new_tab = &tm->tabs[tm->tab_count];
    strncpy(new_tab->title, title, 31);  // �������� ���������

    // �������������� ����� � ������ ������
    init_panel(&new_tab->left_panel, path);
    init_panel(&new_tab->right_panel, path);
    new_tab->active_panel = 0;  // ������� ����� ������

    tm->tab_count++;             // ����������� �������
    tm->current_tab = tm->tab_count - 1;  // ������������� �� ����� �������
}

// ������������ �� ��������� �������
void switch_to_next_tab(TabManager* tm) {
    tm->current_tab = (tm->current_tab + 1) % tm->tab_count;
}