#include <iostream>
#include "FST.h"

using namespace std;

// Функция для выполнения и вывода промежуточных шагов автомата
void executeAndPrint(FST::FST& fst) {
    cout << "Проверяем цепочку: " << fst.string << endl;
    if (FST::execute(fst)) {
        cout << "Цепочка распознана." << endl;
    }
    else {
        cout << "Цепочка не распознана." << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    // Определение автомата для регулярного выражения ab(c)*((d|e|f)b)+c*g
    FST::NODE nodes[] = {
        FST::NODE(1, FST::RELATION('a', 1)), // 0
            FST::NODE(1, FST::RELATION('b', 2)), // 1
            FST::NODE(4,                         // 2
                FST::RELATION('c', 2),
                FST::RELATION('d', 3),
                FST::RELATION('e', 3),
                FST::RELATION('f', 3)),
            FST::NODE(1, FST::RELATION('b', 4)), // 3
            FST::NODE(5,                         // 4
                FST::RELATION('c', 5),
                FST::RELATION('g', 6),
                FST::RELATION('d', 3),
                FST::RELATION('e', 3),
                FST::RELATION('f', 3)),
            FST::NODE(2, FST::RELATION('c', 5), FST::RELATION('g', 6)), // 5
            FST::NODE()                          // 6
    };

    cout << "Пример для цепочки ab(c)*((d|e|f)b)+c*g:" << endl;

    // Тестируем цепочки
    FST::FST fst1("abdbg", 7, nodes);
    executeAndPrint(fst1);

    FST::FST fst2("abebcg", 7, nodes);
    executeAndPrint(fst2);

    FST::FST fst3("abccdbccg", 7, nodes);
    executeAndPrint(fst3);

    FST::FST fst4("abebdbdbccg", 7, nodes);
    executeAndPrint(fst4);

    FST::FST fst5("abccfbcccg", 7, nodes);
    executeAndPrint(fst5);

    FST::FST fst6("abccebdbdbdbebfbcccg", 7, nodes);
    executeAndPrint(fst6);

    FST::FST fst7("abebdbebdbdbebcg", 7, nodes);
    executeAndPrint(fst7);

    return 0;
}
