#include <ncurses.h>
#include <stdlib.h>
#include "ui.h"
#include "helpers.h"

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);    // Выделение
    init_pair(2, COLOR_BLUE, COLOR_BLACK);    // Папки
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Исполняемые
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);  // Симлинки
}

void draw_panel(Panel* panel, int y, int x, int width, int height, bool is_active) {
    WINDOW* win = newwin(height, width, y, x);
    box(win, 0, 0);

    // Заголовок панели
    char truncated_path[width];
    strncpy(truncated_path, panel->path, width - 5);
    truncate_with_ellipsis(truncated_path, width - 5);
    mvwprintw(win, 0, 2, " %s ", truncated_path);

    // Содержимое
    int items_to_show = height - 2;
    for (int i = 0; i < items_to_show && i + panel->scroll_offset < panel->file_count; i++) {
        FileEntry* fe = &panel->files[i + panel->scroll_offset];

        // Выделение
        if (i == panel->cursor_pos - panel->scroll_offset && is_active) {
            wattron(win, COLOR_PAIR(1));
        }

        // Цвета для типов файлов
        if (fe->is_dir) {
            wattron(win, COLOR_PAIR(2));
        }
        else if (is_executable(fe->name)) {
            wattron(win, COLOR_PAIR(3));
        }

        // Имя файла
        char display_name[width - 20];
        truncate_with_ellipsis(fe->name, width - 20);
        mvwprintw(win, i + 1, 1, "%-*s", width - 20, display_name);

        // Доп. информация
        if (!fe->is_dir) {
            char size_str[16];
            format_size(fe->size, size_str, 16);
            mvwprintw(win, i + 1, width - 18, "%10s", size_str);
        }

        wattroff(win, COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
    }
    wrefresh(win);
    delwin(win);
}