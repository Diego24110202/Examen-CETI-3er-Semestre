#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace ftxui;

int main() {
    const int width = 80;
    const int height = 24;

    srand(time(nullptr));
    Screen screen = Screen::Create(Dimension::Fixed(width), Dimension::Fixed(height));

    // === Diseño del cohete ===
    std::vector<std::u32string> cohete = {
        U"    ^    ",
        U"   /^\\   ",
        U"   |-|   ",
        U"   |-|   ",
        U"   |-|   ",
        U"  /___\\  ",
        U"  |   |  ",
        U"  |___|  ",
        U"   | |   ",
        U"   | |   ",
        U"  /   \\  ",
        U"  '---'  "
    };

    // === Generar estrellas aleatorias ===
    std::vector<std::pair<int, int>> estrellas;
    for (int i = 0; i < 60; ++i)
        estrellas.push_back({rand() % width, rand() % height});

    int frame = 0;
    int pos_y = height; // posición inicial del cohete

    while (true) { // Bucle infinito
        screen.Clear();

        // === Dibujar estrellas parpadeantes ===
        for (auto [x, y] : estrellas) {
            if (rand() % 5 != 0) { // Algunas se apagan aleatoriamente
                screen.PixelAt(x, y).character = U'*';
                screen.PixelAt(x, y).foreground_color = (rand() % 2 == 0) ? Color::GrayDark : Color::White;
            }
        }

        // === Dibujar cohete ===
        int y_base = pos_y;
        for (size_t i = 0; i < cohete.size(); ++i) {
            int y = y_base + i;
            if (y >= 0 && y < height) {
                for (size_t x = 0; x < cohete[i].size(); ++x) {
                    screen.PixelAt(38 + x, y).character = cohete[i][x];
                    screen.PixelAt(38 + x, y).foreground_color = Color::White;
                }
            }
        }

        // === Dibujar fuego animado ===
        if (y_base + cohete.size() < height - 1) {
            std::u32string fuego1 = (frame % 2 == 0) ? U"  *  " : U" *** ";
            std::u32string fuego2 = (frame % 2 == 0) ? U" *** " : U"  *  ";

            for (size_t x = 0; x < fuego1.size(); ++x) {
                screen.PixelAt(40 + x, y_base + cohete.size()).character = fuego1[x];
                screen.PixelAt(40 + x, y_base + cohete.size()).foreground_color = Color::Red;
            }
            for (size_t x = 0; x < fuego2.size(); ++x) {
                screen.PixelAt(39 + x, y_base + cohete.size() + 1).character = fuego2[x];
                screen.PixelAt(39 + x, y_base + cohete.size() + 1).foreground_color = Color::Yellow;
            }
        }

        // === Mostrar frame ===
        std::cout << screen.ToString() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(120));

        // === Subir el cohete ===
        pos_y--;
        if (pos_y + (int)cohete.size() < 0) {
            pos_y = height; // Reiniciar cuando salga de pantalla
        }

        frame++;
    }

    return 0;
}
