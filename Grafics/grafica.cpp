#include <iostream>
#include <windows.h> // Для работы с файловой системой в Windows

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    setlocale(LC_ALL, "Rus");
    // Запрос имени файла изображения у пользователя
    std::string filename;
    std::cout << "Введите путь изображения: ";
    std::cin >> filename;

    // Получение пути к текущей рабочей директории
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::string current_directory(buffer);

    // Склеивание пути к изображению с текущей рабочей директорией
    std::string image_path = filename; // Используем только имя файла, без добавления текущей директории

    std::cout << "Путь к изображению: " << image_path << std::endl;

    // Загрузка изображения
    int width, height, channels;
    unsigned char* image_data = stbi_load(image_path.c_str(), &width, &height, &channels, 0);
    if (!image_data) {
        std::cerr << "Не удалось загрузить изображение" << std::endl;
        return 1;
    }

    // Выводим размеры изображения
    std::cout << "Ширина: " << width << ", Высота: " << height << ", Каналы: " << channels << std::endl;

    // Применение фильтра (простой пример: инверсия цветов)
    for (int i = 0; i < width * height * channels; ++i) {
        // Инвертируем значение каждого канала цвета
        image_data[i] = 255 - image_data[i];
    }

    // Сохранение результата
    stbi_write_jpg("output_image.jpg", width, height, channels, image_data, 100);

    std::cout << "Обработка изображения завершена" << std::endl;

    // Освобождение памяти
    stbi_image_free(image_data);

    return 0;
}
