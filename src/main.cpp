/*

***
Название: Консольное приложение, для работы с BMP файлами.

***
Выполнено:
Кроссплатформенное консольное приложение. 
После запуска требует ввести адрес файла формата BMP
а также координаты двух линий в формате x0, y0, x1, y1.
В случае правильно введенных координат отрисовывает прямые линии от точек {x0, y0} до точек {x1, y1}
Линии могут быть любой длины и наклона, но не выходящими за границы изображения. 
В конце требует ввести название файла, в который будет сохранено полученное изображение.
Файл будет сохранен в директорию ./output 
В случае невозможности открыть или сохранить файл бросается исключение и программа завершается.
В случае некорректных координат (выходящих за границы изображения) приложение просит ввести их заново. 
Программа одинаково хорошо работает с 24 и 32 битными изображениями и распознает формат автоматически.
Протестирвоно на Windows 10 и Ubuntu 22

*/

#include <bitmap.h>
#include <string>
#include <iostream>
#include <cstdint>


// утилитарная функция для отрисовки линии
bool draw_line(Bitmap &bmp);


int main(int, char**) {

    std::cout << "[start]" << std::endl;
    std::string filename{};

    std::cout << "Please, enter path to input BMP file: " << std::endl;
    std::cin >> filename;
    try {
        auto bmp = Bitmap(filename);
        std::cout << '\n';
        // выведем информацию о битмапе
        bmp.print_header_info();
        bmp.print_bitmap();
        
        // пока координаты не будут введены верно
        // цикл будет повторяться для каждой линии отдельно
        bool result = false;
        std::cout << "Lets draw cross!" << std::endl;
        do {
            std::cout << "input first line coordinates" << std::endl;
            result = draw_line(bmp);
        } while (!result);
        result = false;
        do {
            std::cout << "input second line coordinates" << std::endl;
            result = draw_line(bmp);
        } while (!result);

        // отрисуем результат
        bmp.print_bitmap();

        // сохраним файл
        std::cout << "Please, input filename to save new BMP file:" << std::endl;
        std::cin >> filename;
        bmp.save_file("output/" + filename + ".bmp");

    // вывод исключений
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    // успешное завершение программы
    std::cout << "[end]" << std::endl;
    return 0;

}


bool draw_line(Bitmap &bmp) {
    int32_t x0, x1, y0, y1;
    std::cout << "Coordinats must be integer" << std::endl;
    std::cout << "(0 <= x < " << bmp.width() << ")\n";
    std::cout << "(0 <= y < " << bmp.height() << ")\n";
    std::cout << "x0: ";
    std::cin >> x0;
    std::cout << "y0: ";
    std::cin >> y0;
    std::cout << "x1: ";
    std::cin >> x1;
    std::cout << "y1: ";
    std::cin >> y1;
    return bmp.draw_line({x0, y0}, {x1, y1}, {0, 0, 0});
}

