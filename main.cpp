#include <iostream>

class ArraySizeError :public std::bad_alloc 
{
public:
    const char* what() const noexcept override 
    {
        return  "Ошибка! Логический размер массива не может превышать фактический!";
    }
};

void checkArraySize(int* array, int log_size, int act_szie) 
{
    if (log_size > act_szie)
        throw ArraySizeError();
}

void append_to_dynamic_array(int*& array, int& log_size, int& act_size, int el, int& last)
{
    if (log_size < act_size) 
    {
        last += 1;
    }
    if (log_size >= act_size) 
    {
        int* new_array = new int[act_size * 2] {0};
        for (int i = 0; i < act_size; ++i) 
        {
            new_array[i] = array[i];
        }
        array = new_array;
        last += 1;
        act_size *= 2;
    }
    array[last] = el;
    log_size += 1;
}

void print_array(int* array, int log_size, int act_size) 
{
    for (int i = 0; i < log_size; ++i)
    {
        std::cout << array[i] << " ";
    }
    for (int i = log_size; i < act_size; ++i)
    {
        std::cout << "_ ";
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    static int log_size = 0, act_size = 0, el = 0, last = -1;
    int* array = new int[act_size];
    do {
        std::cout << "Введите фактичеcкий размер массива: ";
        std::cin >> act_size;
        std::cout << "Введите логический размер массива: ";
        std::cin >> log_size;
        try
        {
            checkArraySize(array, log_size, act_size);
        }
        catch (ArraySizeError& ex) 
        {
            std::cout << ex.what() << std::endl;
        }
    } while (log_size > act_size);

    int i = log_size;
    int count = 0;
    log_size = 0;

    while (count < i) 
    {
        std::cout << "Введите arr[" << count << "]: ";
        std::cin >> el;
        append_to_dynamic_array(array, log_size, act_size, el, last);
        count++;
    }

    do 
    {
        std::cout << "Динамический массив: ";
        print_array(array, log_size, act_size);
        std::cout << "\nВведите элемент для добавления: ";
        std::cin >> el;
        append_to_dynamic_array(array, log_size, act_size, el, last);

    } while (el != 0);

    std::cout << "Спасибо! Ваш массив: ";
    print_array(array, log_size, act_size);
    delete[] array;
}