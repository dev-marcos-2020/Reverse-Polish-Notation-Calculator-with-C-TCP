// ConsoleApplication6.cpp : main project file.

#include "stdafx.h"
#include <string>
#include <array>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>


using namespace System;
using namespace std;


namespace Dice {

    array<string, 7> Dice_1 = {
        "(    _______   )",
        "(  /\       \  )",
        "( /o \   o   \ )",
        "(/   o\_______\)",
        "(\o   /o      /)",
        "( \o /   o   / )",
        "(  \/______o/  )"
    };
    array<string, 7> Dice_2 = {
        "(    _______   )",
        "(  /\ o     \  )",
        "( /o \       \ )",
        "(/   o\______o\)",
        "(\o   /       /)",
        "( \o /   o   / )",
        "(  \/_______/  )"
    };

    array<string, 7> Dice_3 = {
        "(    _______   )",
        "(  /\ o     \  )",
        "( /o \   o   \ )",
        "(/    \______o\)",
        "(\    /       /)",
        "( \o /   o   / )",
        "(  \/_______/  )"
    };

    array<string, 7> Dice_4 = {
        "(    _______   )",
        "(  /\ o    o\  )",
        "( /o \       \ )",
        "(/    \o_____o\)",
        "(\    /o     o/)",
        "( \o /   o   / )",
        "(  \/o_____o/  )"
    };

    array<string, 7> Dice_5 = {
        "(    _______   )",
        "(  /\ o    o\  )",
        "( /o \   o   \ )",
        "(/   o\o_____o\)",
        "(\o   /       /)",
        "( \o /   o   / )",
        "(  \/_______/  )"
    };

    array<string, 7> Dice_6 = {
        "(    _______   )",
        "(  /\ o  o o\  )",
        "( /o \       \ )",
        "(/    \o__o__o\)",
        "(\    /o     o/)",
        "( \o /   o   / )",
        "(  \/o_____o/  )"
    };
    array<string, 7> GetAscii(int random = 0) {
        switch (random) {
            case 1: return Dice_1; break;
            case 2: return Dice_2; break;
            case 3: return Dice_3; break;
            case 4: return Dice_4; break;
            case 5: return Dice_5; break;
            case 6: return Dice_6; break;
            default: return Dice_1; break;
        }
    }
}

namespace Utils {
    void ClearScreen(char fill = ' ') {
        // Set initial coords on Console
        COORD tl = {0,0};
        // Variable to save Console buffer data
        CONSOLE_SCREEN_BUFFER_INFO s;
        // Get console output handle
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        // Save screen buffer info to previously declared variable
        GetConsoleScreenBufferInfo(console, &s);
        // Calculate the cells that we need to write to (the entire screen)
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        // Fill the calculated cells with the fill char on the output handle.
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        // Fill the calculated cells with the original attributes
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        // Reset cursor position to initial (0, 0)
        SetConsoleCursorPosition(console, tl);
    }
    pair<int, int> Selection(char c, pair<int, int> initial, pair<int, int> min, pair<int, int> max, bool esc = false) {
        int ARRIBA = 72;
        int ABAJO = 80;
        int IZQUIERDA = 75;
        int DERECHA = 77;
        int ENTER = 13;
        int ESCAPE = 27;

        int x = initial.first, y = initial.second;
        char key;
        Console::SetCursorPosition(x, y);
        cout << c;

        while (true) {
            key = _getch();
            Console::SetCursorPosition(x, y);
            cout << " ";
            if (key == ABAJO) {
                y++;
                if (y == max.second)
                    y--;
            }
            if (key == ARRIBA) {
                y--;
                if (y == min.second)
                    y++;
            }
            if (key == IZQUIERDA) {
                x--;
                if (x == min.first)
                    x++;
            }
            if (key == DERECHA) {
                x++;
                if (x == max.first)
                    x--;
            }
            if (key == ENTER) {
                return make_pair(x, y);
            }
            if (esc && key == ESCAPE) {
                return make_pair(0, 0);
            }
            Console::SetCursorPosition(x, y);
            cout << c;
        }
    }
    void WaitEscape() {
        int ESCAPE = 27;
        char key;
        while (true) {
            key = _getch();
            if (key == ESCAPE) {
                return;
            }
        }
    }
    bool CheckIfChar(char &key, char c) {
        return (int)key == (int)c;
    }
    int GetRandomNumber(int min, int max) {
        return rand() % max + min;
    }
    bool SortInRev(pair<int, int> &a, pair<int, int> &b) {
        return a.first > b.first;
    }
    namespace Print {
        void Centered(string text, bool newLine = true, int width = Console::WindowWidth, int startX = 0, int startY = Console::CursorTop) {
            Console::SetCursorPosition(startX + ((width - text.length()) / 2), startY);
            cout << text;
            if (newLine) cout << "\n";
        }
        void ClearLine(int x, int y, int width) {
            Console::ResetColor();
            Console::SetCursorPosition(x, y);
            for (int i = 0; i < width; i++) {
                cout << " ";
            }
            Console::SetCursorPosition(x, y);
        }
        void StringArray(string msg[], int size, bool center = false) {
            for (int i = 0; i < size; i++) {
                if (center) Print::Centered(msg[i]);
                else cout << msg[i] << "\n";
            }
        }
    }
}

namespace Movements {
    /**
     * @brief Board layout definition.
     */
    ConsoleColor BoardColors[15][15] = {
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::White, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Gray, ConsoleColor::DarkRed, ConsoleColor::Gray, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White},
        {ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Gray, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White},
        {ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Gray, ConsoleColor::DarkYellow, ConsoleColor::Gray, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::White},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
    };

    /**
     * @brief Movements definitions.
     * @details Relationship between initial pos and final pos.
     */
    pair<pair<int, int>, pair<int, int>> Movements[88] = {
        make_pair(make_pair(6, 0), make_pair(7, 0)),
        make_pair(make_pair(6, 1), make_pair(6, 0)),
        make_pair(make_pair(6, 2), make_pair(6, 1)),
        make_pair(make_pair(6, 3), make_pair(6, 2)),
        make_pair(make_pair(6, 4), make_pair(6, 3)),
        make_pair(make_pair(6, 5), make_pair(6, 4)),
        make_pair(make_pair(6, 9), make_pair(5, 8)),
        make_pair(make_pair(6, 10), make_pair(6, 9)),
        make_pair(make_pair(6, 11), make_pair(6, 10)),
        make_pair(make_pair(6, 12), make_pair(6, 11)),
        make_pair(make_pair(6, 13), make_pair(6, 12)),
        make_pair(make_pair(6, 14), make_pair(6, 13)),
        make_pair(make_pair(7, 9), make_pair(7, 8)),
        make_pair(make_pair(7, 10), make_pair(7, 9)),
        make_pair(make_pair(7, 11), make_pair(7, 10)),
        make_pair(make_pair(7, 12), make_pair(7, 11)),
        make_pair(make_pair(7, 13), make_pair(7, 12)),
        make_pair(make_pair(7, 14), make_pair(6, 14)),
        make_pair(make_pair(7, 0), make_pair(8, 0)),
        make_pair(make_pair(7, 1), make_pair(7, 2)),
        make_pair(make_pair(7, 2), make_pair(7, 3)),
        make_pair(make_pair(7, 3), make_pair(7, 4)),
        make_pair(make_pair(7, 4), make_pair(7, 5)),
        make_pair(make_pair(7, 5), make_pair(7, 6)),
        make_pair(make_pair(8, 0), make_pair(8, 1)),
        make_pair(make_pair(8, 1), make_pair(8, 2)),
        make_pair(make_pair(8, 2), make_pair(8, 3)),
        make_pair(make_pair(8, 3), make_pair(8, 4)),
        make_pair(make_pair(8, 4), make_pair(8, 5)),
        make_pair(make_pair(8, 5), make_pair(9, 6)),
        make_pair(make_pair(8, 9), make_pair(8, 10)),
        make_pair(make_pair(8, 10), make_pair(8, 11)),
        make_pair(make_pair(8, 11), make_pair(8, 12)),
        make_pair(make_pair(8, 12), make_pair(8, 13)),
        make_pair(make_pair(8, 13), make_pair(8, 14)),
        make_pair(make_pair(8, 14), make_pair(7, 14)),
        make_pair(make_pair(9, 6), make_pair(10, 6)), make_pair(make_pair(10, 6), make_pair(11, 6)), make_pair(make_pair(11, 6), make_pair(12, 6)), make_pair(make_pair(12, 6), make_pair(13, 6)), make_pair(make_pair(13, 6), make_pair(14, 6)), make_pair(make_pair(14, 6), make_pair(14, 7)),
        make_pair(make_pair(9, 7), make_pair(8, 7)), make_pair(make_pair(10, 7), make_pair(9, 7)), make_pair(make_pair(11, 7), make_pair(10, 7)), make_pair(make_pair(12, 7), make_pair(11, 7)), make_pair(make_pair(13, 7), make_pair(12, 7)), make_pair(make_pair(14, 7), make_pair(14, 8)),
        make_pair(make_pair(9, 8), make_pair(8, 9)), make_pair(make_pair(10, 8), make_pair(9, 8)), make_pair(make_pair(11, 8), make_pair(10, 8)), make_pair(make_pair(12, 8), make_pair(11, 8)), make_pair(make_pair(13, 8), make_pair(12, 8)), make_pair(make_pair(14, 8), make_pair(13, 8)),
        make_pair(make_pair(0, 6), make_pair(1, 6)), make_pair(make_pair(1, 6), make_pair(2, 6)), make_pair(make_pair(2, 6), make_pair(3, 6)), make_pair(make_pair(3, 6), make_pair(4, 6)), make_pair(make_pair(4, 6), make_pair(5, 6)), make_pair(make_pair(5, 6), make_pair(6, 5)),
        make_pair(make_pair(0, 7), make_pair(0, 6)), make_pair(make_pair(1, 7), make_pair(2, 7)), make_pair(make_pair(2, 7), make_pair(3, 7)), make_pair(make_pair(3, 7), make_pair(4, 7)), make_pair(make_pair(4, 7), make_pair(5, 7)), make_pair(make_pair(5, 7), make_pair(6, 7)),
        make_pair(make_pair(0, 8), make_pair(0, 7)), make_pair(make_pair(1, 8), make_pair(0, 8)), make_pair(make_pair(2, 8), make_pair(1, 8)), make_pair(make_pair(3, 8), make_pair(2, 8)), make_pair(make_pair(4, 8), make_pair(3, 8)), make_pair(make_pair(5, 8), make_pair(4, 8)),
        make_pair(make_pair(2, 2), make_pair(1, 6)), make_pair(make_pair(3, 2), make_pair(1, 6)),
        make_pair(make_pair(2, 3), make_pair(1, 6)), make_pair(make_pair(3, 3), make_pair(1, 6)),
        make_pair(make_pair(2, 11), make_pair(6, 13)), make_pair(make_pair(3, 11), make_pair(6, 13)),
        make_pair(make_pair(2, 12), make_pair(6, 13)), make_pair(make_pair(3, 12), make_pair(6, 13)),
        make_pair(make_pair(11, 2), make_pair(8, 1)), make_pair(make_pair(12, 2), make_pair(8, 1)),
        make_pair(make_pair(11, 3), make_pair(8, 1)), make_pair(make_pair(12, 3), make_pair(8, 1)),
        make_pair(make_pair(11, 11), make_pair(13, 8)), make_pair(make_pair(12, 11), make_pair(13, 8)),
        make_pair(make_pair(11, 12), make_pair(13, 8)), make_pair(make_pair(12, 12), make_pair(13, 8))
    };

    /**
     * @brief Special movements according to player color.
     * @see playerColors array on game.h
     */
    pair<pair<int, int>, pair<int, int>> SpecialMovements[4] = {
        make_pair(make_pair(0, 7), make_pair(1, 7)),
        make_pair(make_pair(7, 0), make_pair(7, 1)),
        make_pair(make_pair(14, 7), make_pair(13, 7)),
        make_pair(make_pair(7, 14), make_pair(7, 13))
    };

    /**
     * @brief Initial positions on board.
     */
    pair<int, int> InitialPositions[4][4] = {
        { make_pair(2, 2), make_pair(3, 2), make_pair(2, 3), make_pair(3, 3) },
        { make_pair(11, 2), make_pair(12, 2), make_pair(11, 3), make_pair(12, 3) },
        { make_pair(11, 11), make_pair(12, 11), make_pair(11, 12), make_pair(12, 12) },
        { make_pair(2, 11), make_pair(3, 11), make_pair(2, 12), make_pair(3, 12) }
    };

    /**
     * @brief Final positions on board.
     */
    pair<int, int> FinalPositions[4] = { make_pair(6, 7), make_pair(7, 6), make_pair(8, 7), make_pair(7, 8) };
}

namespace Menu {
    namespace Print {
        /**
         * @brief Print game logo. This logo has 7 lines.
         * 
         * @param center If the logo should be centered.
         */
        void Logo(bool center = true) {
            string logo[] = {
                "( __       __  __  ____    _____      )",
                "(/\ \     /\ \/\ \/\  _`\ /\  __`\    )",
                "(\ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   )",
                "( \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  )",
                "(  \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ )",
                "(   \ \____/ \ \_____\ \____/\ \_____\)",
                "(    \/___/   \/_____/\/___/  \/_____/)"
            };
            Utils::Print::StringArray(logo, 7, center);
        }

        /**
         * @brief Print game winner trophy. This logo has 9 lines.
         * 
         * @param center If the logo should be centered.
         */
        void Trophy(bool center = true) {
            string trophy[] = {
                "( .-=========-. )",
                "( \'-=======-'/ )",
                "( _|   .=.   |_ )",
                "(((|  {{1}}  |)))",
                "( \|   /|\   |/ )",
                "(  \__ '`' __/  )",
                "(    _`) (`_    )",
                "(  _/_______\_  )",
                "( /___________\ )"
            };
            Utils::Print::StringArray(trophy, 9, center);
        }
    }

    /**
     * @brief Prompts user to select an option from the main menu.
     * 
     * @return The option that was selected.
     */
    int Main() {
        string texts[] = {
            "( ) Start match",
            "( ) Instructions  ",
            "( ) Credits       ",
            "( ) Leave          ",
            "",
            "Use the up and down arrows to select",
            " Press Enter to select the marked option"
        };
        int size = sizeof(texts) / sizeof(texts[0]);
        pair<int, int> ini = make_pair((Console::WindowWidth / 2 - ((texts[1].length() / 2))), 11);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[1].length() / 2))) - 1, 10);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[4].length() / 2))) + 1, 15);

        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n\n\n\n";
        Utils::Print::StringArray(texts, size, true);

        pair<int, int> selection = Utils::Selection('*', ini, min, max);

        return selection.second - 10;
    }

    /**
     * @brief Shows the instructions menu.
     */
    void Instructions() {
        string texts[] = {
            "===== REGLAS DEL JUEGO =====",
            "",
            "- Se juega con un dado de seis caras y el objetivo es",
            "trasladar las 4 fichas desde la cárcel o partida a la casa", 
            "o meta.",
            "- A cada jugador en su turno, le corresponde lanzar el dado utilizando la",
            "BARRA ESPACIADORA y mover sus fichas si le corresponde. El seis del",
            "dado sirve como salida. Se utiliza para sacar fichas de",
            "la cárcel y se obtiene un turno extra (lanza de nuevo",
            "el dado).",
            "",
            "- Las fichas a mover es seleccionada por el usuario y se mueven según el puntaje del dado.",
            "Para seleccionar la ficha, utilice los números del teclado. Si un jugador obtiene tres veces",
            "seguidas seis se le castiga y pierde su turno.",
            "",
            "- Un jugador puede capturar (expulsar y poner en la cárcel) las",
            "fichas de un contrincante, si en su turno ocupa la casilla de este último.", 
            "Ningún jugador puede tener más de una ficha en cada casilla, si en un turno", 
            "se saca un número que da como destino una casilla con una ficha propia, no",
            "se puede mover y se pierde el turno.",
            "",
            "- Cuando una ficha llega a la vertical de color está seguro, es decir ningún", 
            "contrincante puede capturarla. Sin embargo, debe llegar a la casa o meta con la",
            "cuenta exacta, de lo contrario tiene que moverse dentro de la vertical de color según", 
            "lo indicado por el dado.",
            "",
            "- El juego finaliza cuando uno de los jugadores ha colocado las 4 fichas en la casa o meta.",
            "","",
            "Presione ESC para regresar al menú"
        };
        int size = sizeof(texts) / sizeof(texts[0]);
        
        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringArray(texts, size, true);
        Utils::WaitEscape();
    }

    /**
     * @brief Shows the credits menu.
     */
    void Credits() {
        string texts[] = {
            "===== CREDITS =====",
            "",
            "Work made by:",
            "Diego Albitres Blondet (202015652)",
            "Angel Omar Meneses Torres (202010349)",
            "",
            "Career: Software Engineering",
            "Course: Programming I",
            "Cycle: 2020-I",
            "Section: WV1B",
            "",
            "Press ESC to return to the menu"
        };
        int size = sizeof(texts) / sizeof(texts[0]);

        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringArray(texts, size, true);
        Utils::WaitEscape();
    }

    /**
     * @brief Sub-menu for getting the number of players.
     * 
     * @return The number of players selected. Returns 0 if ESC is pressed.
     */
    int GetPlayers() {
        string texts[] = {
            "",
            "Select the number of players:",
            "( ) 2 players",
            "( ) 4 players",
            "",
            "Use the up and down arrows to select",
            " Press Enter to select the marked option",
            "Press ESC to return to the menu"
        };
        int size = sizeof(texts) / sizeof(texts[0]);
        pair<int, int> ini = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2))), 9);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2))) - 1, 8);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[3].length() / 2))) + 1, 11);

        Utils::ClearScreen();
        Menu::Print::Logo();
        Utils::Print::StringArray(texts, size, true);
        
        pair<int, int> players = Utils::Selection('*', ini, min, max, true);
        
        if (players.first == 0 && players.second == 0) {
            return 0;
        }

        switch (players.second) {
            case 9: return 2;
            case 10: return 4;
            default: return 0;
        }
    }

    /**
     * @brief Sub-menu for getting the player names.
     * 
     * @param playerNames The array to store each player name.
     * @param players The number of players that were seleted.
     */
    void GetPlayerNames(array<string, 4> &playerNames, int &players) {
        int DEL = 8;
        int ENTER = 13;
        string name;
        char key;
        for (int i = 0; i < players; i++) {
            Utils::ClearScreen();
            Menu::Print::Logo();
            cout << "\n";
            Utils::Print::Centered(string("Enter the player's name ").append(to_string(i+1)));
            cout << "\n\n";
            Utils::Print::Centered("Press Enter to confirm name");
            Utils::Print::Centered("The character limit is 20");
            while (true) {
                Console::SetCursorPosition(44, 9);
                for (int i = 0; i < 40; i++) {
                    cout << " ";
                }
                Console::SetCursorPosition(((Console::WindowWidth / 2) - (name.length() / 2)), 9);
                Utils::Print::Centered(name);
                key = _getch();
                if (key == DEL && name.length() > 0) {
                    name.pop_back();
                } else if (key == ENTER) {
                    if (name.length() > 0) {
                        playerNames[i] = name;
                        name = "";
                        break;
                    }
                } else {
                    if (name.length() <= 20) {
                        name.push_back(key);
                    }
                }
            }
        }
    }

    /**
     * @brief Sub-menu for a loading screen.
     * 
     * @param players The number of players to show.
     */
    void LoadingScreen(int &players) {
        string str = "Preparing match for ";
        str.append(to_string(players));
        str.append(" players");

        Utils::ClearScreen();
        Menu::Print::Logo();

        for (int i = 0; i < 4; i++) {
            Utils::Print::ClearLine(0, 9, Console::WindowWidth);
            Utils::Print::Centered(str, false, Console::WindowWidth, 0, 9);
            str.append(".");
            Sleep(1000);
        }
    }

    void ShowWinner(string &playerName, ConsoleColor &playerColor) {
        Utils::ClearScreen();
        Menu::Print::Logo();
        Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 1);
        Console::ForegroundColor = playerColor;
        Menu::Print::Trophy();
        Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 1);
        Utils::Print::Centered(string("Congratulations, ").append(playerName).append("!"));
        Console::ResetColor();
        Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 1);
        Utils::Print::Centered("Press ESC to return to the menu");
        Utils::WaitEscape();
    }
}

namespace Game {
    /**
     * Printing utils on Game Module
     */
    namespace Print {
        /**
         * @brief Print the board using the defined layout.
         */
        void Board() {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    Console::BackgroundColor = Movements::BoardColors[i][j];
                    for (int k = 0; k < 2; k++) {
                        for (int l = 0; l < 5; l++) {
                            Console::SetCursorPosition((5 * (j + 1)) + l, (2 * (i + 1)) + k);
                            cout << " ";
                        }
                    }
                    Console::ResetColor();
                }
            }
        }

        /**
         * @brief Print scoreboard without re-rendering board.
         * 
         * @param players The number of players.
         * @param playerNames An array that has the names of each player.
         * @param current The current player (the active player).
         * @param playerColors An array that has the colors of each player.
         * @param ranking An array that has the current ranking.
         * @param random The generated number used to print the dice.
         * @param timesPlayed An array that has the number of times every player has played.
         * @param showSelection True if the scoreboard should prompt to select a token to move, otherwise false.
         */
        void Scoreboard(int &players, array<string, 4> &playerNames, int &current, array<ConsoleColor, 4> &playerColors, array<pair<int, int>, 4> &ranking, int &random, int timesPlayed[4], bool showSelection) {
            // The width of the board
            int boardWidth = 81;
            // The width the scoreboard can use
            int scoreboardWidth = Console::WindowWidth - boardWidth;
            // Auxiliary string
            string str;

            // Sort rankings array
            sort(ranking.begin(), ranking.end(), Utils::SortInRev);
            // Get dice
            array<string, 7> dice = Dice::GetAscii(random);

            // Header
            Utils::Print::Centered("===== MATCH =====", false, scoreboardWidth, boardWidth, 2);

            // Show who's turn is
            Utils::Print::ClearLine(boardWidth, 4, scoreboardWidth);
            Console::ForegroundColor = playerColors[current];
            Utils::Print::Centered(string("Turn of ").append(playerNames[current]), true, scoreboardWidth, boardWidth, 4);
            Console::ResetColor();
            
            // Print the dice
            Utils::Print::Centered("===== DICE =====", true, scoreboardWidth, boardWidth, 6);
			for (int i = 0; i < dice.size(); i++) {
                Utils::Print::Centered(dice[i], true, scoreboardWidth, boardWidth);
            }

            // Print instructions
            Utils::Print::ClearLine(boardWidth, 15, scoreboardWidth);
            Utils::Print::ClearLine(boardWidth, 16, scoreboardWidth);
            if (!showSelection) {
                Utils::Print::Centered("Press the SPACE key", true, scoreboardWidth, boardWidth, 15);
                Utils::Print::Centered("to roll the dice", true, scoreboardWidth, boardWidth, 16);
            } else {
                Utils::Print::Centered("Select the tab you want to move", true, scoreboardWidth, boardWidth, 15);
                Utils::Print::Centered("using keys 1, 2, 3 or 4", true, scoreboardWidth, boardWidth, 16);
            }

            // Print ranking
            Utils::Print::Centered("===== RANKING =====", true, scoreboardWidth, boardWidth, 18);
            for (int i = 0; i < players; i++) {
                str = "";
                str.append(to_string(i + 1)).append(". ").append(playerNames[ranking[i].second]);
                str.append(" - ").append(to_string(ranking[i].first));
                Utils::Print::ClearLine(boardWidth, Console::CursorTop + 1, scoreboardWidth);
                Console::ForegroundColor = playerColors[ranking[i].second];
                Utils::Print::Centered(str, false, scoreboardWidth, boardWidth, Console::CursorTop);
            }
            Console::ResetColor();

            // Print the turns each players has already played
            Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 2);
            Utils::Print::Centered("===== TURNS PLAYED =====", true, scoreboardWidth, boardWidth);
            for (int i = 0; i < players; i++) {
                str = "";
                str.append(to_string(i + 1)).append(". ").append(playerNames[i]);
                str.append(" - ").append(to_string(timesPlayed[i]));
                Utils::Print::ClearLine(boardWidth, Console::CursorTop + 1, scoreboardWidth);
                Console::ForegroundColor = playerColors[ranking[i].second];
                Utils::Print::Centered(str, false, scoreboardWidth, boardWidth, Console::CursorTop);
            }
            Console::ResetColor();
        }
    }

    /**
     * @brief Print a token on the board based on coords.
     * 
     * @param tokenCoords The coords in which the token should be printed.
     * @param tokenNumber The number of the token to be printed.
     * @param playerColor The color of the player.
     */
    void SetTokenPosition(pair<int, int> &tokenCoords, int &tokenNumber, const ConsoleColor &playerColor = ConsoleColor::Black) {
        int x = (5 * (tokenCoords.first + 1)) + 2;
        int y = 2 * (tokenCoords.second + 1);
        Console::BackgroundColor = playerColor;
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(x, y);
        cout << tokenNumber + 1;
        Console::SetCursorPosition(x, y + 1);
        cout << '^';
        Console::ResetColor();
    }

    /**
     * @brief Finds the next position corresponding to the current position of a token and assign it.
     * 
     * @param tokenCoords The current token coords, passed as a reference.
     * @param savedTokens An array that has the tokens a player has already saved (almost finishing).
     * @param selectedToken The selected token that will move.
     * @param current The current player (the active player).
     * @param random The number generated randomly for the dice.
     */
    void SetNewCoords(pair<int, int> &tokenCoords, bool savedTokens[4], int &selectedToken, int &current) {
        if (Movements::SpecialMovements[current].first == tokenCoords) {
            tokenCoords = Movements::SpecialMovements[current].second;
            savedTokens[selectedToken] = true;
            return;
        }
        for (int i = 0; i < 88; i++) {
            if (Movements::Movements[i].first == tokenCoords) {
                tokenCoords = Movements::Movements[i].second;
                return;
            }
        }
    }

    /**
     * @brief Finds the next position corresponding to the current position of a token and returns it.
     * 
     * @param tokenCoords The current token coords, passed as a reference.
     * @param current The current player (the active player).
     * @return The new position of a token.
     */

    pair<int, int> GetNewCoords(pair<int, int> &tokenCoords, int &current) {
        if (Movements::SpecialMovements[current].first == tokenCoords) {
            return Movements::SpecialMovements[current].second;
        }
        for (int i = 0; i < 88; i++) {
            if (Movements::Movements[i].first == tokenCoords) {
                return Movements::Movements[i].second;
            }
        }
        return make_pair(0, 0);
    }

    /**
     * @brief Checks whether a token must go to jail again because an enemy token ocupied its position.
     * 
     * @param playerTokens An array that has the coords of each token of every player.
     * @param tokensOut An array that has whether a token has already come out of jail.
     * @param selectedTokens The selected token that will move.
     * @param current The current turn (the active player).
     * @param players The number of players in the current game.
     * @return True if a token was sent to jail, otherwise false.
     */
    bool SendTokenToJail(pair<int, int> playerTokens[4][4], bool tokensOut[4][4], int &selectedTokens, int &current, int &players) {
        for (int i = 0; i < players; i++) {
            if (i != current) {
                pair<int, int> *p = find(begin(playerTokens[i]), end(playerTokens[i]), playerTokens[current][selectedTokens]);
                if (p != end(playerTokens[i]) && *p == playerTokens[current][selectedTokens]) {
                    int d = distance(begin(playerTokens[i]), p);
                    playerTokens[i][d] = Movements::InitialPositions[i][d];
                    tokensOut[i][d] = false;
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Calculate movements left for a token to enter the safe zone.
     * 
     * @param tokenCoords An array that has the coords of each token of an specific player.
     * @param savedTokens An array that has the tokens a player has already saved (almost finishing).
     * @param current The current turn (the active player).
     * @param selectedToken The selected token that will move.
     * @return The number of movements for a token.
     */
    int GetMovementsLeft(pair<int, int> tokenCoords[4], bool savedTokens[4], int &current, int &selectedToken) {
        if (savedTokens[selectedToken]) {
            switch (current) {
            case 0:
                return abs(Movements::FinalPositions[current].first - tokenCoords[selectedToken].first);
                break;
            case 1:
                return abs(Movements::FinalPositions[current].second - tokenCoords[selectedToken].second);
                break;
            case 2:
                return abs(Movements::FinalPositions[current].first - tokenCoords[selectedToken].first);
                break;
            case 3:
                return abs(Movements::FinalPositions[current].second - tokenCoords[selectedToken].second);
                break;
            default:
                return 0;
                break;
            }
        }
        return 0;
    }

    /**
     * @brief Calculate the number of tokens a player has available to move.
     * 
     * @param tokenCoords An array that has the coords of each token of an specific player.
     * @param savedTokens An array that has the tokens a player has already saved (almost finishing).
     * @param tokensOut An array that has whether a token has already come out of jail.
     * @param tokensFinished An array that has whether a token has already won.
     * @param current The current turn (the active player).
     * @param random The number generated randomly for the dice.
     * @return The number of tokens a player can move.
     */
    int GetMovableTokens(pair<int, int> tokenCoords[4], bool savedTokens[4], bool tokensOut[4], bool tokensFinished[4], int &current, int &random) {
        int movable = 0;
        for (int i = 0; i < 4; i++) {
            if (savedTokens[i]) { if (GetMovementsLeft(tokenCoords, savedTokens, current, i) >= random) movable++; }
            else if (random == 6 && !tokensFinished[i]) movable++;
            else if (random != 6 && tokensOut[i] && !tokensFinished[i]) movable++;
        }
        return movable;
    }

    /**
     * @brief Main function of the game logic.
     */
    void Start() {
        // Two-dimension array for each players' tokens
        pair<int, int> tokenCoords[4][4];
        // Save the state of each players' tokens (if it's out or not)
        bool tokensOut[4][4] = { {false}, {false}, {false}, {false} };
        // Array to store player names
        array<string, 4> playerNames;
        // Current player (the active player)
        int currentPlayer = 0;
        // Used to know if the token of a player just came out of jail on last turn
        bool tokenCameOut = false;
        // Should reload board
        bool reload = false;
        // Selected token to move
        int selectedToken = 0;
        // Counter for 6s
        int sixCounter = 0;
        // Should render scoreboard
        bool renderScoreboard = true;
        // Times played counter
        int timesPlayed[4] = {0};
        // Save pressed key
        char key;
        // Random number for dice
        int random = 0;
        // Number of active tokens
        int activeTokens;
        // Should skip current turn
        bool skipTurn = false;
        // Array to store rankings
        array<pair<int, int>, 4> playerRanking;
        // Save token state of each player (if it has finished its path or not)
        bool tokensFinished[4][4] = { {false}, {false}, {false}, {false} };
        // Tokens in finish line (the ones that are safe)
        bool savedTokens[4][4] = { {false}, {false}, {false}, {false} };
        // Movements left for a player to win
        int movementsLeft;
        // Array for player colors
        array<ConsoleColor, 4> playerColors = { ConsoleColor::Green, ConsoleColor::DarkRed, ConsoleColor::Blue, ConsoleColor::DarkYellow };

        // Get number of players
        int players = Menu::GetPlayers();
        // Exit menu if ESC is pressed
        if (players == 0) return;

        // Set initial token positions
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tokenCoords[i][j] = Movements::InitialPositions[i][j];
            }
        }

        // Set initial ranking based on number of players
        for (int i = 0; i < players; i++) {
            playerRanking[i] = make_pair(0, i);
        }

        // Self-explanatory
        Menu::GetPlayerNames(playerNames, players);
        Menu::LoadingScreen(players);

        // Clear everything before printing board
        Utils::ClearScreen();
        Print::Board();

        // Print initial token positions
        for (int i = 0; i < players; i++) {
            for (int j = 0; j < 4; j++) {
                SetTokenPosition(tokenCoords[i][j], j, playerColors[i]);
            }
        }

        // Start game loop
        while (true) {
            Print::Scoreboard(players, playerNames, currentPlayer, playerColors, playerRanking, random, timesPlayed, false);

            do {
                key = _getch();
            } while (!Utils::CheckIfChar(key, 32));

            if (Utils::CheckIfChar(key, 32)) {
                // Pre-calculate number of active tokens based on tokens out
                activeTokens = count(begin(tokensOut[currentPlayer]), end(tokensOut[currentPlayer]), true);

                // Generate random number for current player
                random = Utils::GetRandomNumber(1, 6);

                // Counter for times played of every player
                timesPlayed[currentPlayer]++;

                // Counter of 6's
                if (random == 6) {
                    sixCounter++;
                }

                // If the player has had 3 six in a row, skip turn
                if (sixCounter == 3) {
                    sixCounter = 0;
                    currentPlayer++;
                    if (currentPlayer == players) currentPlayer = 0;
                    continue;
                }

                // Set initial movements left on every loop
                movementsLeft = -1;

                // Only run if player has more than 1 player on the board
                // or player got a six and has at least 1 player on the board
                if (GetMovableTokens(tokenCoords[currentPlayer], savedTokens[currentPlayer], tokensOut[currentPlayer], tokensFinished[currentPlayer], currentPlayer, random) > 1) {
                    // Re-render scoreboard only on first loop
                    renderScoreboard = true;
                    do {
                        do {
                            if (renderScoreboard) {
                                renderScoreboard = false;
                                Print::Scoreboard(players, playerNames, currentPlayer, playerColors, playerRanking, random, timesPlayed, true);
                            }
                            key = _getch();
                            switch (key) {
                                case '1':
                                    selectedToken = 0;
                                    break;
                                case '2':
                                    selectedToken = 1;
                                    break;
                                case '3':
                                    selectedToken = 2;
                                    break;
                                case '4':
                                    selectedToken = 3;
                                    break;
                                default:
                                    selectedToken = -1;
                                    break;
                            }
                        } while (!(selectedToken >= 0 && selectedToken <= 3));

                        // Calculate the number of movements left
                        if (savedTokens[currentPlayer][selectedToken])
                            movementsLeft = GetMovementsLeft(tokenCoords[currentPlayer], savedTokens[currentPlayer], currentPlayer, selectedToken);
                    
                    } while (!((tokensOut[currentPlayer][selectedToken] && random != 6 && !savedTokens[currentPlayer][selectedToken]) || (random == 6 && !savedTokens[currentPlayer][selectedToken]) || (savedTokens[currentPlayer][selectedToken] && movementsLeft >= random) || (tokensFinished[currentPlayer][selectedToken] && !savedTokens[currentPlayer][selectedToken])));
                } else if (activeTokens == 1) {
                    // Select the only active token that the player has
                    selectedToken = distance(begin(tokensOut[currentPlayer]), find(begin(tokensOut[currentPlayer]), end(tokensOut[currentPlayer]), true));
                } else {
                    // Select the first token that hasn't already finished
                    selectedToken = distance(begin(tokensFinished[currentPlayer]), find(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), false));
                }

                // Calculate the number of movements left if not set before
                if (movementsLeft == -1)
                    movementsLeft = GetMovementsLeft(tokenCoords[currentPlayer], savedTokens[currentPlayer], currentPlayer, selectedToken);
                
                // Check if a player wants to move a token to a position where he has already a token of its own
                pair<int, int> newPossibleCoords = tokenCoords[currentPlayer][selectedToken];
                if (tokensOut[currentPlayer][selectedToken]) {
                    for (int i = 0; i < random; i++) {
                        newPossibleCoords = GetNewCoords(newPossibleCoords, currentPlayer);
                    }
                } else newPossibleCoords = GetNewCoords(newPossibleCoords, currentPlayer);
                for (int i = 0; i < 4; i++) {
                    if (tokenCoords[currentPlayer][i] == newPossibleCoords && !tokensFinished[currentPlayer][i]) {
                        skipTurn = true;
                    }
                }
                if (skipTurn) {
                    sixCounter = 0;
                    currentPlayer++;
                    if (currentPlayer == players) currentPlayer = 0;
                    skipTurn = false;
                    continue;
                }

                // Only run when token is in safe zone (almost finishing)
                if (savedTokens[currentPlayer][selectedToken] && activeTokens > 0 && movementsLeft >= random) {
                    // Queue the reload
                    reload = true;
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(tokenCoords[currentPlayer][selectedToken], savedTokens[currentPlayer], selectedToken, currentPlayer);
                    }
                    if (movementsLeft == random) {
                        tokensFinished[currentPlayer][selectedToken] = true;
                        for (int i = 0; i < players; i++) {
                            if (playerRanking[i].second == currentPlayer) {
                                playerRanking[i].first = count(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), true);
                            }
                        }
                        tokensOut[currentPlayer][selectedToken] = false;
                    }
                }

                // Only run if dice got 6 and the token selected is inside of jail
                if (random == 6 && activeTokens < 4 && !tokensOut[currentPlayer][selectedToken] && !savedTokens[currentPlayer][selectedToken]) {
                    // Set that a token has just came out
                    tokenCameOut = true;
                    // Queue the reload
                    reload = true;
                    SetNewCoords(tokenCoords[currentPlayer][selectedToken], savedTokens[currentPlayer], selectedToken, currentPlayer);
                    tokensOut[currentPlayer][selectedToken] = true;
                    SendTokenToJail(tokenCoords, tokensOut, selectedToken, currentPlayer, players);
                }

                // Move the player the times the dice says and check if the new position
                // already has another player's token, then send it to jail if there is
                // Only run if a token hasn't just come out of jail
                if (activeTokens > 0 && !tokenCameOut && !savedTokens[currentPlayer][selectedToken]) {
                    // Queue the reload
                    reload = true;
                    // Check if the token is about to enter the safe zone and with a 6 can win
                    if (Movements::SpecialMovements[currentPlayer].first == tokenCoords[currentPlayer][selectedToken] && random == 6) {
                        tokensFinished[currentPlayer][selectedToken] = true;
                        for (int i = 0; i < players; i++) {
                            if (playerRanking[i].second == currentPlayer) {
                                playerRanking[i].first = count(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), true);
                            }
                        }
                        tokensOut[currentPlayer][selectedToken] = false;
                    }
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(tokenCoords[currentPlayer][selectedToken], savedTokens[currentPlayer], selectedToken, currentPlayer);
                    }
                    if (!savedTokens[currentPlayer][selectedToken])
                        SendTokenToJail(tokenCoords, tokensOut, selectedToken, currentPlayer, players);
                }

                // Reload board and token positions only when a change has been queued previously 
                if (reload) {
                    Print::Board();
                    for (int i = 0; i < players; i++) {
                        for (int j = 0; j < 4; j++) {
                            SetTokenPosition(tokenCoords[i][j], j, playerColors[i]);
                        }
                    }
                }

                // Exit loop if current player won
                if (count(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), true) == 4) break;

                // Change turn to next person and reset six counter
                if (random != 6) {
                    sixCounter = 0;
                    currentPlayer++;
                    if (currentPlayer == players) currentPlayer = 0;
                }
            }

            // Reset variables on every loop
            tokenCameOut = false;
            selectedToken = 0;
            reload = false;
        }
        
        // Show winner and then return to main menu
        Menu::ShowWinner(playerNames[currentPlayer], playerColors[currentPlayer]);
    }
}

//int main(array<System::String ^> ^args)
#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 40

int main()
{
//    Console::WriteLine(L"Hello World");

    // Start random seed
    srand(time(NULL));
    // Set locale to use UTF-8 characters
    setlocale(LC_ALL, "es_PE.UTF-8");
    // Set console window size
    Console::SetWindowSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    
    // Initialize loop variable
    bool loop = true;

    // Just in case
    Utils::ClearScreen();
    
    // Start menu loop
    while (loop) {
        // Get selection from main menu
        int option = Menu::Main();

        switch (option) {
            case 1:
                Game::Start();
                break;
            case 2: 
                Menu::Instructions();
                break;
            case 3:
                Menu::Credits();
                break;
            case 4:
                loop = false;
                break;
        }
    }

    // Wait for any key to exit
    Utils::ClearScreen();
    Menu::Print::Logo();
    cout << "\n";
    Utils::Print::Centered("Press any key to exit");
    _getch();
    exit(0);
	
	return 0;
}