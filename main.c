#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

void display_general_info();
void display_packages();
void list_installed_packages();

int main() {
    initscr();                
    cbreak();                 
    noecho();                 
    keypad(stdscr, TRUE);     
    int ch;

    while (1) {
        clear();
        mvprintw(0, 0, "=== Minitel 3.1 ===");
        mvprintw(2, 0, "1. Informations générales");
        mvprintw(3, 0, "2. Liste des paquets installés");
        mvprintw(4, 0, "3. Quitter");
        mvprintw(6, 0, "Choisissez une option : ");

        ch = getch();
        switch (ch) {
            case '1':
                display_general_info();
                break;
            case '2':
                display_packages();
                break;
            case '3':
                endwin();   
                exit(0);
                break;
            default:
                mvprintw(8, 0, "Option invalide. Réessayez.");
                getch();
                break;
        }
    }
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

void display_general_info() {
    clear();
    mvprintw(0, 0, "=== Informations Générales ===");

    // v du système d'exploitation
    mvprintw(2, 0, "Version de l'OS :");
    system("cat /etc/os-release | grep '^PRETTY_NAME=' | cut -d= -f2 | tr -d '\"'");

    // uptime
    mvprintw(4, 0, "Uptime :");
    system("uptime -p");

    // v du Kernel
    mvprintw(6, 0, "Version du Kernel :");
    system("uname -r");

    // infos matérielles
    mvprintw(8, 0, "CPU :");
    system("lscpu | grep 'Model name' | cut -d: -f2 | xargs");

    mvprintw(10, 0, "Mémoire totale :");
    system("free -h | grep 'Mem:' | awk '{print $2}'");

    mvprintw(12, 0, "Espace disque disponible :");
    system("df -h / | tail -1 | awk '{print $4}'");

    // lim de fichiers et de processus
    mvprintw(14, 0, "Limite fichiers ouverts :");
    system("ulimit -n");

    mvprintw(16, 0, "Limite processus :");
    system("ulimit -u");

    mvprintw(18, 0, "Appuyez sur une touche pour revenir au menu principal...");
    getch();
}

void display_packages() {
    clear();
    mvprintw(0, 0, "=== liste des paquets Installés ===");
    mvprintw(2, 0, "1. Afficher la liste paginée des paquets");
    mvprintw(3, 0, "2. Retour au menu principal");
    mvprintw(5, 0, "Choisissez une option :");

    int ch = getch();
    switch (ch) {
        case '1':
            list_installed_packages();
            break;
        case '2':
            return;
        default:
            mvprintw(7, 0, "option invalide. Réessayez.");
            getch();
            break;
    }
}

void list_installed_packages() {
    clear();
    mvprintw(0, 0, "=== liste des paquets Installés ===");
    mvprintw(2, 0, "appuyez sur une touche pour défiler ou 'q' pour quitter.");

    FILE *fp = popen("dpkg -l | less", "r"); // pour les distrib basées sur Debian
    if (fp == NULL) {
        mvprintw(4, 0, "error : impossible de lister les paquets.");
        getch();
        return;
    }
    pclose(fp);

    mvprintw(4, 0, "Fin de la liste. Appuyez sur une touche pour revenir...");
    getch();
}
