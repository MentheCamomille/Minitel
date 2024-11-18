#include <ncurses.h>
#include <stdlib.h>

void display_info();
void quit_program();

int main() {
    initscr();                
    cbreak();                 
    noecho();                 
    keypad(stdscr, TRUE);     
    int ch;

    while (1) {
        clear();
        mvprintw(0, 0, "=== Minitel 3.1 ===");
        mvprintw(2, 0, "1. Afficher les informations système");
        mvprintw(3, 0, "2. Quitter");
        mvprintw(5, 0, "Choisissez une option : ");

        ch = getch();
        switch (ch) {
            case '1':
                display_info();
                break;
            case '2':
                quit_program();
                break;
            default:
                mvprintw(7, 0, "Option invalide. Réessayez.");
                break;
        }
    }
    endwin();                 
    return 0;
}

void display_info() {
    clear();
    mvprintw(0, 0, "=== Informations Système ===");

    FILE *fp = popen("uname -a", "r"); 
    if (fp == NULL) {
        mvprintw(1, 0, "Erreur : Impossible d'exécuter uname.");
    } else {
        char buffer[128];
        int row = 1;
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            mvprintw(row++, 0, "%s", buffer); 
        }
        pclose(fp);
    }

    mvprintw(10, 0, "Appuyez sur une touche pour continuer...");
    getch();
}

void quit_program() {
    endwin();
    exit(0);
}
