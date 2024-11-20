#include "stdafx.h"
#include "Error.h"
#include "In.h"
#include <cwchar>
#include <fstream>
#include <vector>

namespace In {
    IN getin(const wchar_t* infile) {
        IN result;
        result.size = 0;
        result.lines = 0;
        result.ignor = 0;
        result.text = nullptr;

        // Открываем файл
        std::wifstream file(infile, std::ios::binary);  // Конструктор принимает const wchar_t*
        if (!file.is_open()) {
            throw ERROR_THROW(110);  // Ошибка при открытии файла
        }

        // Считываем содержимое файла
        std::vector<unsigned char> buffer(IN_MAX_LEN_TEXT);
        unsigned char* pBuffer = buffer.data();
        unsigned char* pText = pBuffer;
        int currentLine = 0;
        int currentPos = 0;
        std::fill(std::begin(result.code), std::end(result.code), IN::F); // Инициализация таблицы проверки

        while (file.good() && pBuffer < buffer.data() + IN_MAX_LEN_TEXT) {
            char ch = file.get();
            if (file.eof()) break;
            if (ch == 'Y') ch = '!';
            if (ch == '\n') ch = '|';
            // Получаем код символа
            unsigned char code = static_cast<unsigned char>(ch);

            // Проверяем символ
            int check = IN_CODE_TABLE[code];

            if (check == IN::F) {
                // Генерация исключения для запрещенного символа
                throw ERROR_THROW_IN_WITH_CHAR(111, currentLine, ch, currentPos);
            }
            else if (check == IN::I) {
                // Игнорируем символ
                result.ignor++;
            }
            else {
                // Обрабатываем допустимый символ
                *pText++ = code;
                result.size++;
                if (check == IN::F) {
                    result.code[code] = IN::F;
                }
                else {
                    result.code[code] = IN::I;
                }
            }

            currentPos++;
            if (ch == IN_CODE_ENDL) {
                // Переход на следующую строку
                result.lines++;
                currentPos = 0;
                currentLine++;
            }
        }

        if (result.size == 0) {
            result.text = new unsigned char[1];
            result.text[0] = '\0';
        }
        else {
            // Определяем новый размер вставляемой строки

            result.text = new unsigned char[result.size + 1];

            // Копируем данные и добавляем завершающий нулевой символ
            std::memcpy(result.text, buffer.data(), result.size);
            result.text[result.size] = '\0';
        }

        return result;
    }
}