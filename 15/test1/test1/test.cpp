#include <iostream>
#include <vector>
#include <algorithm> // ��� std::copy

int main() {
    std::vector<unsigned char> buffer = { 1, 2, 3, 4, 5 };
    size_t n = 3; // ���������� ����, ������� ����� �����������

    unsigned char* destination = new unsigned char[n];

    // �������� ������ n ���� �� buffer � destination
    std::copy(buffer.data(), buffer.data() + n, destination);

    // ������� ������������� �����
    for (size_t i = 0; i < n; ++i) {
        std::cout << static_cast<int>(destination[i]) << " "; // ����������� � int ��� �������� ������
    }
    std::cout << std::endl;

    delete[] destination; // ����������� ������
    return 0;
}
