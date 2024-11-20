#include <iostream>
#include <vector>
#include <algorithm> // Для std::copy

int main() {
    std::vector<unsigned char> buffer = { 1, 2, 3, 4, 5 };
    size_t n = 3; // Количество байт, которые нужно скопировать

    unsigned char* destination = new unsigned char[n];

    // Копируем первые n байт из buffer в destination
    std::copy(buffer.data(), buffer.data() + n, destination);

    // Выводим скопированные байты
    for (size_t i = 0; i < n; ++i) {
        std::cout << static_cast<int>(destination[i]) << " "; // Преобразуем в int для удобства вывода
    }
    std::cout << std::endl;

    delete[] destination; // Освобождаем память
    return 0;
}
