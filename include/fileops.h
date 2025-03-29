#ifndef FILEOPS_H
#define FILEOPS_H

#include <stdbool.h>
#include "tabs.h"

// ��������� ��� �������� ���������� � �����
typedef struct {
    char name[256];  // ��� �����
    bool is_dir;     // ��� ����������?
    off_t size;      // ������ � ������
    time_t mtime;    // ����� ���������
} FileEntry;

// ��������� ���������� � ��������� ������ �������
void scan_directory(Panel* panel);

// ��������� ������ ��� ���������� (qsort)
int compare_files(const void* a, const void* b);

// ������������� ������ � ��������� �����
void init_panel(Panel* panel, const char* path);

#endif