#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Set/Set.h"

#define RUN_TEST

#ifdef RUN_TEST
#include "tests.h"
#else

#define println(x) std::cout << x << std::endl;

void addToSet(sbl::Set* st);
void removeFromSet(sbl::Set* st);
void showAsciiArt(std::string name);

int main() {
    sbl::Set* A = new sbl::Set();
    sbl::Set* B = new sbl::Set();

    sbl::Set* selected = A;
    sbl::Set s;

    std::string str;
    int a;

    println("Welcome!");

    bool stoploop = false;
    while (!stoploop) {
        std::string selected_set = (selected == A ? "A" : "B");
        std::string unselected_set = (selected == A ? "B" : "A");

        println("---------- Main Menu ----------");
        println("Selected Set: " << selected_set);
        println("0 - Exit");
        println("1 - Clear selected set");
        println("2 - Insert into set " << selected_set);
        println("3 - Remove from set " << selected_set);
        println("4 - Echo set " << selected_set);
        println("5 - Change set: " << selected_set << "->" << unselected_set);
        println("6 - Intersect: A&B");
        println("7 - SymDiff: A|B");
        println("8 - Is set " << selected_set << " empty?");
        println("-------------------------------");

        int menu_selecton;
        std::cout << ">>> ";
        std::cin >> menu_selecton;

        switch (menu_selecton) {
            case 0:
                stoploop = true;
                break;
            case 1:
                selected->clear();
                break;
            case 2:
                addToSet(selected);
                break;
            case 3:
                removeFromSet(selected);
                break;
            case 4:
                std::cout << *(selected) << std::endl;
                break;
            case 5:
                if (selected == A) {
                    selected = B;
                } else {
                    selected = A;
                }
                break;
            case 6:
                s = *A & *B;
                std::cout << s << std::endl;
                break;
            case 7:
                s = *A | *B;
                std::cout << s << std::endl;
                break;
            case 8:
                std::cout << (selected->isEmpty() ? "Empty" : "Not Empty") << std::endl;
                break;
        }
    }

    showAsciiArt("aperture");
    println("This was a triumph...");
}

void addToSet(sbl::Set* st) {
    std::cout << "[]> ";

    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    int n;

    while (ss >> n) {
        st->insert(n);
    }
}

void removeFromSet(sbl::Set* st) {
    std::cout << "[]> ";

    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    int n;

    while (ss >> n) {
        st->remove(n);
    }
}

void showAsciiArt(std::string name) {
    std::ifstream f("ascii/" + name + ".txt");
    if (f.is_open()) {
        std::string str;
        while (std::getline(f, str)) {
            std::cout << str << std::endl;
        }
    }
}

#endif
