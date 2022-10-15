# lab1
## part2

__CPU__

*Имя модели*:                      Intel(R) Core(TM) i5-10210U CPU @ 1.60GHz

*Степпинг*:                        12

*CPU МГц*:                         2100.000

*CPU max MHz*:                     4200,0000

*CPU min MHz*:                     400,0000

*CPU(s)*:                          8

*On-line CPU(s) list*:             0-7

*Потоков на ядро*:                 2

__*Полученные в результате опытов данные*__

N=10000
M=100

|               | vector, сек   | list, сек     | set, сек       |
|:--------------:|:--------------:|:--------------:|:--------------:|
| push_back     | 0.000226245   | 0.00090317      |      ---       |
| insert        | 0.00491401       | 0.000821805     | 0.00657484      |
| find          |  0.114498    | 0.299183      | 0.512316       |


N=100000
M=1000

|               | vector, сек   | list, сек     | set, сек       |
|:--------------:|:--------------:|:--------------:|:--------------:|
| push_back     | 0.00195867    | 0.00845513      |      ---       |
| insert        | 0.438709       | 0.00768259     | 0.0747281      |
| find          | 1.1223     | 2.68504       | 4.61167       |

N=1000000
M=10000

|               | vector, сек   | list, сек     | set, сек       |
|:--------------:|:--------------:|:--------------:|:--------------:|
| push_back     | 0.0171718     | 0.126355      |      ---       |
| insert        | 63.4408       | 0.0988142     | 0.500066      |
| find          | 5.10048     | 14.2994       | 14.4059        |


__*Сложность алгоритмов*__

|               | vector, O(N)  | list, O(N)    | set, O(N)      |
|:--------------:|:--------------:|:--------------:|:--------------:|
| push_back     |      O(1)     |      O(N)     |      ---       |
| insert        |      O(N)     |      O(1)     |  O(log n)  |
| find          |      O(N)     |      O(N)     |  O(log n)      |

* Выводы
    * __Для vector вставка в конец - эффективнее всего, вставка в начало не эффективная, тк приходится копировать весь массив__
    * __Для list эффективнее вставка в начало__
    * __Поиск элементов эффективнее всего в vector__


## part2


N=500

|                      | random         | identical      | no duplicate  |
|:--------------------:|:--------------:|:--------------:|:--------------:|
| has_duplicates       |      0.000105023 |    7.5141e-05   |  7.8719e-05    |
| has_duplicates_naive |     0.000787884    |    0.000832989      |  0.000824037       |
| get_duplicates       |      0.000108143 |    7.3758e-05   |  8.0691e-05    |
| get_duplicates_naive |      0.000939096   |    0.0083046     |  0.00886016      |



N=5000

|                      | random         | identical      | no duplicate  |
|:--------------------:|:--------------:|:--------------:|:--------------:|
| has_duplicates       |      0.00146256 |    0.00105682   |  0.00114755    |
| has_duplicates_naive |     0.0909349    |    0.089992      |  0.0832064       |
| get_duplicates       |      0.00197475 |    0.0010616   |  0.0010185    |
| get_duplicates_naive |      0.0989021   |    0.884381     |  0.817797      |

N=50000


|                      | random         | identical      | no duplicate  |
|:--------------------:|:--------------:|:--------------:|:--------------:|
| has_duplicates       |      0.0172462 |    0.0111919   |  0.0132957    |
| has_duplicates_naive |     7.70364    |    6.7524      |  6.7524       |
| get_duplicates       |      0.0149418 |    0.0110989   |  0.0130227    |
| get_duplicates_naive |      7.52986   |    72.8844     |  72.9706      |

|                      | random         | identical      | no duplicate     |
|:--------------------:|:--------------:|:--------------:|:--------------:|
| has_duplicates       |    O(N log N)  |     O(N log N) |      O(N log N)  |
| has_duplicates_naive |      O(N^2)    |     O(N^2)     |      O(N^2)      |
| get_duplicates       |    O(N Log n)  |  O(N Log N)    |      O(N log N)  |
| get_duplicates_naive |      O(N^2)    |  O(N^2)        |      O(N^2)      |

* __Выводы__
    * __Алогритм через метод sort гораздно эффективнее, особенно это заметно на больших данных (50000 операций против 2,500,000,000 соответственно)__