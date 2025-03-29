#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

// ����������� ������� � �������� ������ (KB/MB/GB)
void format_size(off_t size, char* buffer, size_t buf_size);

// ��������: �������� �� ���� �����������
bool is_executable(const char* path);

// ������� ������ � ����������� "..."
void truncate_with_ellipsis(char* str, int max_len);

#endif