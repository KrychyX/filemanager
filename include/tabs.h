#ifndef TABS_H
#define TABS_H

#include "fileops.h"

// ������������ ���������� �������� � ��������� �������
#define MAX_TAB_TITLE 32

// ��������� ������
typedef struct {
    char path[PATH_MAX];      // ������� ����
    FileEntry* files;         // ������ ������
    int file_count;          // ���������� ������
    int cursor_pos;         // ������� �������
    int scroll_offset;      // �������� �������
} Panel;

// ��������� �������
typedef struct {
    char title[MAX_TAB_TITLE];  // ��������� �������
    Panel left_panel;          // ����� ������
    Panel right_panel;         // ������ ������
    int active_panel;         // 0 = �����, 1 = ������
} Tab;

// �������� �������
typedef struct {
    Tab* tabs;               // ������ �������
    int tab_count;           // ���������� �������
    int current_tab;         // ������ ������� �������
} TabManager;

// ������������� ��������� �������
void init_tab_manager(TabManager* tm);

// ���������� ����� �������
void add_new_tab(TabManager* tm, const char* title, const char* path);

// ������������ �� ��������� �������
void switch_to_next_tab(TabManager* tm);

// ������� ��������
void cleanup(TabManager* tm);

#endif