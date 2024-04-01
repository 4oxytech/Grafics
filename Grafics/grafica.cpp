#include <iostream>
#include <windows.h> // ��� ������ � �������� �������� � Windows

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    setlocale(LC_ALL, "Rus");
    // ������ ����� ����� ����������� � ������������
    std::string filename;
    std::cout << "������� ���� �����������: ";
    std::cin >> filename;

    // ��������� ���� � ������� ������� ����������
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::string current_directory(buffer);

    // ���������� ���� � ����������� � ������� ������� �����������
    std::string image_path = filename; // ���������� ������ ��� �����, ��� ���������� ������� ����������

    std::cout << "���� � �����������: " << image_path << std::endl;

    // �������� �����������
    int width, height, channels;
    unsigned char* image_data = stbi_load(image_path.c_str(), &width, &height, &channels, 0);
    if (!image_data) {
        std::cerr << "�� ������� ��������� �����������" << std::endl;
        return 1;
    }

    // ������� ������� �����������
    std::cout << "������: " << width << ", ������: " << height << ", ������: " << channels << std::endl;

    // ���������� ������� (������� ������: �������� ������)
    for (int i = 0; i < width * height * channels; ++i) {
        // ����������� �������� ������� ������ �����
        image_data[i] = 255 - image_data[i];
    }

    // ���������� ����������
    stbi_write_jpg("output_image.jpg", width, height, channels, image_data, 100);

    std::cout << "��������� ����������� ���������" << std::endl;

    // ������������ ������
    stbi_image_free(image_data);

    return 0;
}
