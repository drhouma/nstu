# Практическое занятие №2: Сортировка и поиск

__CPU__

*Имя модели*:                      Intel(R) Core(TM) i5-10210U CPU @ 1.60GHz

*Степпинг*:                        12

*CPU МГц*:                         2100.000

*CPU max MHz*:                     4200,0000

*CPU min MHz*:                     400,0000

*CPU(s)*:                          8

*On-line CPU(s) list*:             0-7

*Потоков на ядро*:                 2

## Часть 1: сортировка

__*Полученные в результате опытов данные*__
Количество чисел N=1000000=1e+6

| алгоритм \ диапазон чисел |  -1000 : 1000  | -500000:500000 |
|:-------------------------:|:--------------:|:--------------:|
| std::sort                 | 0.314826       | 0.408797       |
| count_sort                | 0.0184182      | 0.126694       |

* Выводы
    * Когда есть массив, строго ограниченный малым диапазоном (-1000 : 1000), выгодно использовать count_sort
    * Когда массив ограничен диапазоном, размер которого больше или равен исходному массиву, алгоритм count_sort не выгоден