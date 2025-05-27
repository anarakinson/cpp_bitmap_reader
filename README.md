

***
## Name:
### Console application for working with BMP files.

***
### Was done:

Cross-platform console application.

After launching, it requires entering the address of the BMP file

as well as the coordinates of two lines in the format x0, y0, x1, y1.

If the coordinates are entered correctly, it draws straight lines from the points {x0, y0} to the points {x1, y1}

The lines can be of any length and slope, but not extending beyond the boundaries of the image.

At the end, it requires entering the name of the file in which the resulting image will be saved.

The file will be saved in the ./output directory

If it is impossible to open or save the file, an exception is thrown and the program terminates.

In case of incorrect coordinates (outside the image boundaries), the application asks to enter them again.

The program works equally well with 24 and 32 bit images and recognizes the format automatically.

Tested on Windows 10 and Ubuntu 22

---

***
## Название: 
### Консольное приложение, для работы с BMP файлами.

***
### Выполнено:
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
