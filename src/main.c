#include <ncurses.h>
#include "ui.h"
#include "tabs.h"

int main() {
    // ������������� ���������� ncurses (����� ������ � ����������)
    init_ncurses();

    // ������ �������� ������� � ��������� ������ �������
    TabManager tab_manager;
    init_tab_manager(&tab_manager);  // ����������� ��������� ��������
    add_new_tab(&tab_manager, "Tab 1", getenv("HOME"));  // HOME = /home/user

    // ������� ���� ��������� (��������, ���� running = true)
    bool running = true;
    while (running) {
        // �������������� ���������
        draw_interface(&tab_manager);

        // ��� ������� �������
        int ch = getch();

        // ������������ �������
        switch (ch) {
        case 'q':  // �����
            running = false;
            break;
        case KEY_LEFT:  // ������������ ����� �����/������ �������
        case KEY_RIGHT:
            switch_panel(&tab_manager);
            break;
        case KEY_UP:  // �������� ������� �����/����
        case KEY_DOWN:
            move_cursor(&tab_manager.tabs[tab_manager.current_tab], ch);
            break;
        case '\t':  // ������������ �������
            switch_to_next_tab(&tab_manager);
            break;
        case '\n':  // Enter - ������� ����/�����
            open_selected(&tab_manager.tabs[tab_manager.current_tab]);
            break;
        }
    }

    // ������� ������ � ���������� ncurses
    cleanup(&tab_manager);
    endwin();
    return 0;
}