# lab1
## part2
N=1000000
M=1000000

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

|               | vector, сек   | list, сек     | set, сек       |
|:--------------:|:--------------:|:--------------:|:--------------:|
| push_back     | 0.0171718     | 0.126355      |      ---       |
| insert        | 63.4408       | 0.0988142     | 0.182593       |
| find          | 0.0978987     | 0.07205       | 0.0816526      |


__*Сложность алгоритмов*__

|               | vector, O(N)  | list, O(N)    | set, O(N)      |
|:--------------:|:--------------:|:--------------:|:--------------:|
| push_back     |      O(1)     |      O(N)     |      ---       |
| insert        |      O(N)     |      O(1)     |  O(n * log n)  |
| find          |      O(N)     |      O(N)     |  O(n* log n)    |


## part2

N=50000


|                      | random         | identical    | no duplicate      |
|:--------------------:|:--------------:|:--------------:|:--------------:|
| has_duplicates       |      0.0172462 |    0.0111919   |  0.0132957    |
| has_duplicates_naive |      14.3769   |    1.7959e-05  |  4.0248e-05   |
| get_duplicates       |      0.0149418 |    0.0110989   |  0.0130227    |
| get_duplicates_naive |      7.52986   |    72.8844     |  72.9706      |

|                      | random         | identical    | no duplicate      |
|:--------------------:|:--------------:|:--------------:|:--------------:|
| has_duplicates       |    O(N log N)  |      O(1)    |      O(N log N)   |
| has_duplicates_naive |      O(N^2)    |      O(1)    |      O(N^2)       |
| get_duplicates       |    O(N Log n)  |  O(N Log N)  |      O(N log N)         |
| get_duplicates_naive |      O(N^2)    |  O(N^2 + N)  |      O(N^2)       |