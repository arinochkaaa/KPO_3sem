#ifndef FST_H
#define FST_H

namespace FST {
    struct RELATION {
        char symbol;      // ������ �������� 
        short nnode;      // ����� ������� ������� 

        // ���������� ������������
        RELATION(char c = 0x00, short ns = 0);
    };

    struct NODE {
        short n_relation; // ���������� ����������� �����
        RELATION* relations;  // ����������� ����� 

        // ���������� �������������
        NODE();
        NODE(short n, RELATION rel, ...);
    };

    struct FST {
        char* string;     // ������� (������, ����������� 0x00)
        short position;   // ������� ������� � ������� 
        short nstates;    // ���������� ��������� ��������
        NODE* nodes;      // ���� ���������
        short rstates;    // ��������� ��������� �������� �� ������ ������� 

        // ���������� ������������ � �����������
        FST(const char* s, short ns, NODE* n);
        ~FST();
    };

    // ���������� ������� ���������� �������������
    bool execute(FST& fst);
};

#endif
