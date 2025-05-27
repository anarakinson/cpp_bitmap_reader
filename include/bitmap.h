#pragma once 

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

#include <cstdint>



// класс для хранения значений трехканального пикселя
class Pixel {
public:
    uint8_t b{255};
    uint8_t g{255};
    uint8_t r{255};

    // функция, отвечающая, является ли пиксель полностью белым
    bool is_white() const {
        return (b == 255 && g == 255 && r == 255);
    }
    // функция, отвечающая, является ли пиксель полностью черным
    bool is_black() const {
        return (b == 0 && g == 0 && r == 0);
    }
};


// класс для хранения значений четырехканального пикселя
class Pixel32 : public Pixel {
public:
    uint8_t a{255};
};


// класс для работы с координатами точек битмапа
class Point2D {
public:
    int32_t x = 0;
    int32_t y = 0;
};



// Класс для работы с битмапом
class Bitmap {
public:
    // конструктор позволяет создавать битмап только из файла.
    explicit Bitmap(std::string filename) {
        load_file(filename);
    }

    ~Bitmap() = default;

    // функция отрисовки битмапа в консоли
    void print_bitmap() const;

    // функция для окрашивания фона в разные цвета
    std::string set_color(const Pixel &pixel) const;

    // функция для отрисовки линии по двум точкам
    // алгоритм описан здесь - https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    bool draw_line(const Point2D &start_pos, const Point2D &end_pos, const Pixel &color);

    // функция для окрашивания пикселя
    bool set_pixel(const Point2D &pos, const Pixel &color);

    // загрузка битмапа из файла
    void load_file(const std::string &filename);

    // сохранение битмапа в файл
    void save_file(const std::string &filename);

    // функция для вывода основной информации из заголовков
    void print_header_info() const;

    // ширина и высота изображения
    uint32_t width() const { return m_info_header.width; }
    uint32_t height() const { return m_info_header.height; }

private:

    // структура заголовков описана здесь - https://en.wikipedia.org/wiki/BMP_file_format 
    // нужно выставить выравнивание по единице, 
    // чтобы не потерять данные 
    // при выгруске последовательности байт
#pragma pack(push, 1)
    struct Header {
        uint16_t sygnature{};
        uint32_t filesize{};
        uint32_t reserved{};
        uint32_t data_offset{};    
    };
    
    struct InfoHeader {
        uint32_t size{};
        uint32_t width{};
        uint32_t height{};
        uint16_t planes{};
        uint16_t bits_per_pixel{};
        uint32_t compression{};
        uint32_t image_size{};
        uint32_t x_pixels_per_meter{};
        uint32_t y_pixels_per_meter{};
        uint32_t colors_used{};
        uint32_t colors_importanse{};
    };
#pragma pack(pop)

    // переменная, указывающая количество каналов
    int m_byte_num = 0;

    // экземпляры заголовков
    Header m_header{};
    InfoHeader m_info_header{};

    // само изображение
    std::vector<uint8_t> m_data{};
    // название файла
    std::string m_filename;

    class FileHandler {
    public:
        FileHandler(std::fstream &file) : m_file{std::move(file)} {}
        ~FileHandler() {
            if (m_file.is_open()) m_file.close();
        }
    private:
        std::fstream m_file;
    };
};

