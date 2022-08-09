#include <iostream>
#include <random>
#include <iterator>
#include <string>
#include <cmath>
#include "cdarray.h"

int main (int argc, char ** argv) {

// Тестирование методов

    constexpr size_t arr_size = 10;

    CDArray<double> arr(arr_size);

    for (size_t i = 0; i < arr_size; ++i) {
        arr.Add( i + i/10.0 );
    }

    std::cout << "Number = " << arr.Number() << std::endl;
    std::cout << "Size = " << arr.Size() << std::endl;

    for (size_t i = 0; i < arr.Number(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "---------------------------" << std::endl;

    arr.Delete(5);
    std::cout << "arr.Delete(5)" << std::endl;
    std::cout << "Number = " << arr.Number() << std::endl;
    std::cout << "Size = " << arr.Size() << std::endl;

    for (size_t i = 0; i < arr.Number(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "---------------------------" << std::endl;

    arr.Modify(5, -5.5);
    std::cout << "arr.Modify(5, -5.5)" << std::endl;
    std::cout << "Number = " << arr.Number() << std::endl;
    std::cout << "Size = " << arr.Size() << std::endl;

    for (size_t i = 0; i < arr.Number(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "---------------------------" << std::endl;

    auto tmp = arr[ arr.Number() ];
    std::cout << "arr[ arr.Number() ]" << std::endl;
    std::cout << tmp << std::endl;
    std::cout << "---------------------------" << std::endl;

    /*
    // Тут должно броситься исключение
    auto tmp2 = arr[ arr.Number()+1 ];
    */

    arr[5] = 10.10;
    std::cout << "arr[5] = 10.10" << std::endl;
    std::cout << arr[5] << std::endl;
    std::cout << "---------------------------" << std::endl;

    for(CDArray<double>::iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << "*it = " << *it << std::endl;
    }
    std::cout << "---------------------------" << std::endl;

// ================================================================
// Массив с не числовыми объектами

    CDArray<std::string> str_arr;
    str_arr.Add(std::string("quick"));
    str_arr.Add(std::string("brown"));
    str_arr.Add(std::string("fox"));
    str_arr.Add(std::string("jumps"));
    str_arr.Add(std::string("over"));
    str_arr.Add(std::string("the"));
    str_arr.Add(std::string("lazy"));
    str_arr.Add(std::string("dog"));

    for (size_t i = 0; i < str_arr.Number(); ++i) {
        std::cout << str_arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "---------------------------" << std::endl;

// ================================================================
// Тестирование из задания

    constexpr size_t second_array_size = 700;
    constexpr double lower_border = 1.0;
    constexpr double upper_border = 100.0;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(lower_border, upper_border);

    CDArray<double> array(second_array_size);

    for (size_t i = 0; i < second_array_size; ++i) {
        array.Add(dist(rng));
    }

    for (size_t i = 0; i < array.Number() - 1; i++)
    {
        for (size_t j = 0; j < array.Number() - i - 1; j++) {
            if (array[j] > array[j + 1]){
                std::swap(array[j], array[j + 1]);
            }
                
        }
            
    }

    double sum = 0;

    for(auto it = array.begin(); it != array.end(); ++it) {
        sum += *it;
    }

    double avg = sum/array.Number();

    double sigma = 0;

    for(auto it = array.begin(); it != array.end(); ++it) {
        sigma += pow((*it - avg), 2);
    }
    sigma = sigma / (array.Number() - 1);
    sigma = sqrt(sigma);

    std::cout << "Expected value = " << avg << std::endl;
    std::cout << "Standard deviation = " << sigma << std::endl;
    
    return 0;
}