#include "stdafx.h"
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

namespace In
{
    // ������� ��� �������� ������ �������� � �������� ���������
    int removeExtraSpaces(std::string& input) {
        int deletedSpaces = 0;  // ���������� ��������� ��������
        bool insideQuotes = false;  // ���� ��� ��������� �������
        const std::string operators = ";,}{()=+-/*";  // ���������, ������ ������� ������� �������

        // ������� � �������� �������� � ������ ������
        size_t startSpaces = 0;
        while (startSpaces < input.length() && input[startSpaces] == ' ') {
            ++startSpaces;
            deletedSpaces++;  // ����������� �������
        }
        input.erase(0, startSpaces);  // ������� ������� � ������ ������

        // �������� ������ �������� ����� �������
        size_t i = 0;
        while (i < input.length()) {
            if (input[i] == '\'') {
                insideQuotes = !insideQuotes;  // ������������ �������
            }

            // ������������ ������ ������� ����� �������
            if (!insideQuotes && input[i] == ' ') {
                size_t spacesToRemove = 0;
                // ������� ���������� ��������
                while (i + spacesToRemove < input.length() && input[i + spacesToRemove] == ' ') {
                    ++spacesToRemove;
                }
                // ���� ������ ������ �������, ������� ������
                if (spacesToRemove > 1) {
                    deletedSpaces += spacesToRemove - 1;
                    input.erase(i + 1, spacesToRemove - 1);
                    continue;
                }
            }

            // �������� �������� ������ ����������
            if (operators.find(input[i]) != std::string::npos) {
                // �������� �������� ����� ����������
                while (i > 0 && std::isspace(input[i - 1])) {
                    input.erase(i - 1, 1);
                    deletedSpaces++;
                    --i;
                }

                // �������� �������� ����� ���������
                while (i + 1 < input.length() && std::isspace(input[i + 1])) {
                    input.erase(i + 1, 1);
                    deletedSpaces++;
                }
            }

            i++;
        }

        // �������� �������� � ����� ������
        size_t endSpaces = input.length();
        while (endSpaces > 0 && input[endSpaces - 1] == ' ') {
            endSpaces--;
            deletedSpaces++;
        }
        input.erase(endSpaces);  // ������� ������� � ����� ������

        return deletedSpaces;
    }

    // ������� ��� ������ � ��������� ������ �� �����
    IN getin(wchar_t infile[]) {
        ifstream fin;
        char* outFile = new char[wcslen(infile) + 1];
        wcstombs_s(NULL, outFile, wcslen(infile) + 1, infile, wcslen(infile) + 1);
        fin.open(infile);

        if (fin.bad()) {
            throw ERROR_THROW(116);
        }
        if (!fin.is_open()) {
            throw ERROR_THROW(110);
        }

        IN resultIn;
        resultIn.size = 0;
        resultIn.lines = 0;
        int position = 0;
        int ch;
        std::string currentLine;
        std::string buffer;

        while (std::getline(fin, buffer)) {
            resultIn.lines++;

            for (int i = 0; i < buffer.length(); i++) {
                ch = buffer[i];

                if (ch == fin.eof()) {
                    break;
                }

                switch (resultIn.code[(unsigned char)ch]) {
                case IN::F: // ������������ �������, ������� �������� ����������������
                    resultIn.text.push_back(currentLine);
                    throw ERROR_THROW_IN(111, resultIn.lines, ++position, buffer, resultIn.text);
                    break;

                case IN::I:
                    resultIn.ignor++;
                    position++;
                    break;

                case IN::T: // ������������ ��������� �������
                    currentLine += ch;
                    position++;
                    resultIn.size++;
                    break;

                default:
                    currentLine += resultIn.code[(unsigned char)ch];
                    resultIn.size++;
                    position++;
                    break;
                }
            }

            if (!currentLine.empty()) {
                int deletedSpaces = removeExtraSpaces(currentLine);  // ������� ������ ������� � ������
                resultIn.text.push_back(currentLine);
                currentLine.clear();

                resultIn.ignor += deletedSpaces;  // ����������� ���������� �������������� �������� �� ���������� ��������� ��������
            }
        }

        fin.close();

        return resultIn;
    }
}
