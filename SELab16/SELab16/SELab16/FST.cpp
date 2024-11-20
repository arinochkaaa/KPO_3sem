#include "FST.h"
#include <cstring> 
#include <cstdarg> 

namespace FST {
    // Реализация конструктора RELATION
    RELATION::RELATION(char c, short ns) : symbol(c), nnode(ns) {}

    // Реализация конструктора NODE (по умолчанию)
    NODE::NODE() : n_relation(0), relations(nullptr) {}

    // Реализация конструктора NODE (с параметрами)
    NODE::NODE(short n, RELATION rel, ...) : n_relation(n) {
        relations = new RELATION[n_relation];

        va_list args;
        va_start(args, rel);

        relations[0] = rel;
        for (int i = 1; i < n_relation; ++i) {
            relations[i] = va_arg(args, RELATION);
        }

        va_end(args);
    }

    // Реализация конструктора FST
    FST::FST(const char* s, short ns, NODE* n) : position(0), nstates(ns), nodes(n), rstates(0) {
        // Копирование строки
        if (s != nullptr) {
            string = new char[std::strlen(s) + 1]; // +1 для символа завершения строки
            strcpy_s(string, std::strlen(s) + 1, s); // Безопасная версия strcpy
        }
        else {
            string = nullptr;
        }
    }

    // Реализация деструктора для освобождения памяти
    FST::~FST() {
        delete[] string;
    }

    // Реализация функции execute
    bool execute(FST& fst) {
        bool* current_states = new bool[fst.nstates];
        bool* next_states = new bool[fst.nstates];

        for (short i = 0; i < fst.nstates; i++) {
            current_states[i] = false;
            next_states[i] = false;
        }
        current_states[0] = true;

        while (fst.string[fst.position] != '\0') {
            char symbol = fst.string[fst.position];

            for (short i = 0; i < fst.nstates; i++) {
                if (current_states[i]) {
                    NODE& node = fst.nodes[i];

                    for (short j = 0; j < node.n_relation; j++) {
                        RELATION& rel = node.relations[j];
                        if (rel.symbol == symbol) {
                            next_states[rel.nnode] = true;
                        }
                    }
                }
            }

            for (short i = 0; i < fst.nstates; i++) {
                current_states[i] = next_states[i];
                next_states[i] = false;
            }

            fst.position++;
        }

        bool result = current_states[fst.nstates - 1];

        delete[] current_states;
        delete[] next_states;

        return result;
    }
}
