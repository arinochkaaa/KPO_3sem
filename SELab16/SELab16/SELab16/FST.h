#ifndef FST_H
#define FST_H

namespace FST {
    struct RELATION {
        char symbol;      // символ перехода 
        short nnode;      // номер смежной вершины 

        // ќбъ€вление конструктора
        RELATION(char c = 0x00, short ns = 0);
    };

    struct NODE {
        short n_relation; // количество инцидентных ребер
        RELATION* relations;  // инцидентные ребра 

        // ќбъ€вление конструкторов
        NODE();
        NODE(short n, RELATION rel, ...);
    };

    struct FST {
        char* string;     // цепочка (строка, завершаетс€ 0x00)
        short position;   // текуща€ позици€ в цепочке 
        short nstates;    // количество состо€ний автомата
        NODE* nodes;      // граф переходов
        short rstates;    // возможные состо€ни€ автомата на данной позиции 

        // ќбъ€вление конструктора и деструктора
        FST(const char* s, short ns, NODE* n);
        ~FST();
    };

    // ќбъ€вление функции выполнени€ распознавани€
    bool execute(FST& fst);
};

#endif
