#include <ncurses.h>
#include "ui.h"
#include "tabs.h"

int main() {
    // Инициализация библиотеки ncurses (режим работы с терминалом)
    init_ncurses();

    // Создаём менеджер вкладок и добавляем первую вкладку
    TabManager tab_manager;
    init_tab_manager(&tab_manager);  // Настраиваем начальные значения
    add_new_tab(&tab_manager, "Tab 1", getenv("HOME"));  // HOME = /home/user

    // Главный цикл программы (работает, пока running = true)
    bool running = true;
    while (running) {
        // Перерисовываем интерфейс
        draw_interface(&tab_manager);

        // Ждём нажатия клавиши
        int ch = getch();

        // Обрабатываем клавиши
        switch (ch) {
        case 'q':  // Выход
            running = false;
            break;
        case KEY_LEFT:  // Переключение между левой/правой панелью
        case KEY_RIGHT:
            switch_panel(&tab_manager);
            break;
        case KEY_UP:  // Движение курсора вверх/вниз
        case KEY_DOWN:
            move_cursor(&tab_manager.tabs[tab_manager.current_tab], ch);
            break;
        case '\t':  // Переключение вкладок
            switch_to_next_tab(&tab_manager);
            break;
        case '\n':  // Enter - открыть файл/папку
            open_selected(&tab_manager.tabs[tab_manager.current_tab]);
            break;
        }
    }

    // Очистка памяти и завершение ncurses
    cleanup(&tab_manager);
    endwin();
    return 0;
}