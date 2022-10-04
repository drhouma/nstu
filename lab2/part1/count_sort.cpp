#include "count_sort.h"
#include <cmath>


/**
 * @brief сортировка подсчетом
 * 
 * @param array сортируемый вектор
 * @param min минимальное значение числа в вектора
 * @param max максимальное значение числа в векторе - 1 (0 : 100) - 99 max
 */
auto count_sort(std::vector<int> &array, int min, int max) -> void {
    std::vector<int> counters(abs(max - min));
    for (int elem : array) {
        counters[elem - min]++;
    }
    for (int k{0}, c{0};c < counters.size(); c++) {
        for (int i = 0; i < counters[c]; i++, k++) {
            array[k] = c + min;
        }
    }
}