
#include <bitmap.h>

// Класс для работы с битмапом

// функция отрисовки битмапа в консоли
void Bitmap::print_bitmap() const {
    
    for (size_t row = 0; row < static_cast<size_t>(m_info_header.height); row++) {
        for (size_t col = 0; col < static_cast<size_t>(m_info_header.width); col++) {                
            auto x_pos = col;
            auto y_pos = (m_info_header.width - row - 1) * m_info_header.width;

            Pixel pixel{};
            // поскольку значения цветов идут в обратном порядке
            // используются первые три байта в обратном порядке
            // альфа канал идет четвертым и игнорируется
            pixel.r = m_data[(y_pos + x_pos) * m_byte_num + 2];
            pixel.g = m_data[(y_pos + x_pos) * m_byte_num + 1];
            pixel.b = m_data[(y_pos + x_pos) * m_byte_num + 0];
            std::cout << set_color(pixel);

        }                
        std::cout << '\n';
    }
    std::cout << '\n';

}
    
// функция для окрашивания фона в разные цвета
std::string Bitmap::set_color(const Pixel &pixel) const {
    if (pixel.is_black()) {
        return "\033[0;40;30m \033[0m";
    }
    else if (pixel.is_white()) {
        return "\033[0;47;37m \033[0m";
    }
    else {
        return "\033[0;42;32m \033[0m";
    }
}


// функция для отрисовки линии по двум точкам
// алгоритм описан здесь - https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
bool Bitmap::draw_line(const Point2D &start_pos, const Point2D &end_pos, const Pixel &color) {
    
    int32_t x0 = start_pos.x;
    int32_t x1 = end_pos.x;
    int32_t y0 = start_pos.y;
    int32_t y1 = end_pos.y;
    
    int32_t max_x = m_info_header.width;
    int32_t max_y = m_info_header.height;
    
    if (
        (x0 >= max_x || x1 >= max_x) || 
        (y0 >= max_y || y1 >= max_y) || 
        (x0 < 0 || x1 < 0) || 
        (y0 < 0 || y1 < 0) 
    ) return false;

    int32_t dx = abs(x1 - x0);
    int32_t sx = x0 < x1 ? 1 : -1;
    int32_t dy = -abs(y1 - y0);
    int32_t sy = y0 < y1 ? 1 : -1;
    int32_t error = dx + dy;
    
    while (true) {
        set_pixel({x0, y0}, color);
        int32_t e2 = 2 * error;
        if (e2 >= dy) {
            if (x0 == x1) break;
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) break;
            error = error + dx;
            y0 = y0 + sy;
        }
    }
    std::cout << '\n';
    return true;
}


// функция для окрашивания пикселя
bool Bitmap::set_pixel(const Point2D &pos, const Pixel &color) {

    if (
        (pos.x >= static_cast<int32_t>(m_info_header.width)) || (pos.x < 0) ||
        (pos.y >= static_cast<int32_t>(m_info_header.height)) || (pos.y < 0)
    ) return false;

    auto x_pos = pos.x;
    auto y_pos = (m_info_header.width - pos.y - 1) * m_info_header.width;

    m_data[(y_pos + x_pos) * m_byte_num + 2] = color.r; 
    m_data[(y_pos + x_pos) * m_byte_num + 1] = color.g; 
    m_data[(y_pos + x_pos) * m_byte_num + 0] = color.b; 

    return true;

}

// загрузка битмапа из файла
void Bitmap::load_file(const std::string &filename) {

    m_filename = filename;

    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open()) {
        throw std::runtime_error{ "[Error] Unable to open file" };
    }

    if (!file.read(reinterpret_cast<char*>(&m_header), sizeof(m_header))) {
        throw std::runtime_error{ "[Error] failed to read header" };
    }
    if (!file.read(reinterpret_cast<char*>(&m_info_header), sizeof(m_info_header))) {
        throw std::runtime_error{ "[Error] failed to read info header" };
    }

    m_data.resize(m_info_header.image_size);
    if (!file.read(reinterpret_cast<char*>(m_data.data()), m_info_header.image_size)) {
        throw std::runtime_error{ "[Error] failed to read image" };
    }
    // запомним количество каналов
    m_byte_num = m_info_header.bits_per_pixel / 8;

    file.close();

}

// сохранение битмапа в файл
void Bitmap::save_file(const std::string &filename)  {

    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open()) {
        throw std::runtime_error{ "[Error] Unable to create file" };
    }

    if (!file.write(reinterpret_cast<char*>(&m_header), sizeof(m_header))) {
        throw std::runtime_error{ "[Error] failed to write header" };
    }
    if (!file.write(reinterpret_cast<char*>(&m_info_header), sizeof(m_info_header))) {
        throw std::runtime_error{ "[Error] failed to write info header" };
    }
    if (!file.write(reinterpret_cast<char*>(m_data.data()), m_info_header.image_size)) {
        throw std::runtime_error{ "[Error] failed to write image" };
    }
    
    std::cout << "[+] File successfully saved to: " << filename << std::endl;

    file.close();

}

// функция для вывода основной информации из заголовков
void Bitmap::print_header_info() const {
    std::cout << "filename: " << m_filename << std::endl;
    std::cout << "filesize: " << m_header.filesize << std::endl;
    std::cout << "bits_per_pixel: " << m_info_header.bits_per_pixel << std::endl;
    std::cout << "width: " << m_info_header.width << std::endl;
    std::cout << "height: " << m_info_header.height << std::endl;
    std::cout << "size: " << m_info_header.image_size << std::endl;
    std::cout << "planes: " << m_info_header.planes << std::endl;
    std::cout << "channels: " << m_byte_num << std::endl;
}
