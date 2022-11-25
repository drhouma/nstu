#include <iostream>
#include <bitset>
#include <cmath>
#include <climits>
#include <iomanip>
#include <limits>
#include <numbers>
#include <iostream>
#include <cstdint>
#include <cstring>

struct myDouble
{
    int sign;
    int exp;
    long long mantissa; // 52 symbols
};

auto binaryView(int sign, int exp, int mantissa) -> std::string; 
auto reverse(std::string const &s) -> std::string;
auto binaryToHex(unsigned long long number, int len) -> std::string; // len 4 || 8
auto hexStrToDouble(const std::string &str) -> double;
auto hexStrToFloat(const std::string &str) -> float;






union data
    {
        float input; // assumes sizeof(float) == sizeof(int)
        long double dinput;
        unsigned long long output;
    };

auto getBinaryView(float number) -> unsigned int {
    int i{0};
    int exp{0};
    int sign = (number >= 0 ? 0 : 1);
    unsigned mantissa_bits{0};
    unsigned long long bias{127};
    double mantissa;

    number = fabs(number);
    bool ex{true};
    while (ex)
    {
        if (number <= 1) {
            if (number >= pow(2, exp)) {
                ex = false;
            } else {
                exp--;
            }
        } else {
            if (number <= pow(2, exp + 1)) {
                ex = false;
            } else {
                exp++;
            }
        }
    }
    mantissa = number / pow(2, exp) - 1;
    std::cout << mantissa << '\n';
    for (int i = 1; i <= 23; i++) {
        if (mantissa >= pow(2, -i)) {
            mantissa -= pow(2, -i);
            mantissa_bits += 1 << (23 - i);
        }
    }

    
    return (sign << 31) + ((exp + bias) << 23) + mantissa_bits;

}

auto getBinaryViewDouble(double number) -> unsigned long long {
    int i{0};
    unsigned long long exp{0};
    unsigned long long sign = (number >= 0 ? 0 : 1);
    unsigned long long mantissa_bits{0};
    unsigned long long bias{1023};
    long double mantissa;
    number = fabs(number);

    bool ex{true};
    while (ex)
    {
        if (number <= 1) {
            if (number >= pow(2, exp)) {
                ex = false;
            } else {
                exp--;
            }
        } else {
            if (number <= pow(2, exp + 1)) {
                ex = false;
            } else {
                exp++;
            }
        }
    }
    mantissa = number / powl(2, exp) - 1;
    for (int i = 1; i <= 52; i++) {
        if (mantissa >= powl(2, -i)) {
            mantissa -= powl(2, -i);
            mantissa_bits += 1ULL << (52 - i);
        }
    }
    
    return (sign << 63) + ((exp + bias) << 52) + mantissa_bits;

}
// 4629700416936869888
// 4629700415863225086

auto Menu(int &len) -> void {
    while (true) {
        // std::cin.exceptions(std::ios_base::failbit);
        system("clear");
        std::string option;
        std::cout << ".______________________________.\n";
        std::cout << "|------------------------------|\n";
        std::cout << "|             MENU             |\n";
        std::cout << "|------------------------------|\n";
        std::cout << "|1 - part 6                    |\n";
        std::cout << "|2 - part 7                    |\n";
        std::cout << "|3 - set number len(4 || 8)    |\n"; 
        std::cout << "|0 - exit                      |\n";     
        std::cout << "|______________________________|\n";
        std::cout << ">>> enter option\n";
        
        try
        {
            std::cin >> option;
        }
        catch(const std::exception& e)
        {
            std::cin.clear();
            std::cerr << e.what() << '\n';
            Menu(len);
        }
        
        
        switch (option[0])
        {
            case '1':
            {
                std::cout << "Введите число с плавающей запятой\n";
                std::string number;
                std::cin >> number;
                std::cout << number << '\n';
                unsigned long long output;
                // number.input = number.dinput;
                if (len == 4) {

                    output = getBinaryView(std::stof(number));
                } else {
                    output = getBinaryViewDouble(std::stod(number));
                }
                std::cout << binaryToHex(output, len) << std::endl << "press enter to continue ...\n";
                break;
            }
            case '2':
            {
                std::cout << "Введите биты числа в двоично-десятичной\n";
                std::string number;
                std::cin >> number;
                if (number.length() != len * 2) {
                    std::cout << "Неверная длина слова!\n";
                    throw std::exception();
                }
                long double db;
                if (len == 4) {
                    db = hexStrToFloat(number);
                } else {
                    db = hexStrToDouble(number);
                }

                std::cout << std::setprecision(16) << db << '\n' << "press enter to continue ...\n";
                // double res = pow(2, db.exp) * db.mantissa / ;

                break;
            }
            case '3':
            {
                if (len == 8) len = 4;
                else len = 8;
                std::cout << "current length = " << len << '\n';
                std::cout << "Nice!\npress enter to continue...\n";
                break;
            }
            case '0':
                exit(0);
            default: 
            {
                std::cout << "incorrect option\n";
                std::cin.clear();
                system("sleep 1");
            }
        }
        system("read REPLY");
    }
}


int main () {
    // std::cin.exceptions(std::ios_base::failbit);
    int len = 4;
    try {
        Menu(len);
    } catch (std::exception( &e)) {
        std::cout << "error!\npress enter to continue...\n";
        system("read REPLY");
        std::cin.clear();
        Menu(len);
    }
}

auto binaryView(int sign, int exp, int mantissa) -> std::string {
    std::string sExp, sMantissa;
    while (exp > 0) {
        sExp += std::to_string(exp & 1);
        exp >> 1;
    }
    sExp = reverse(sExp);
    while (mantissa > 0) {
        sMantissa += std::to_string(mantissa & 1);
        mantissa >> 1;
    }
    sMantissa = reverse(sMantissa);
    return std::to_string(sign >> 31) + sExp + sMantissa;
}

auto binaryToHex(unsigned long long number, int len) -> std::string {
    int quadra;
    std::string res;
    for (int i = 0; i < len * 2; i++) {
        quadra = number >> (4 * i);
        quadra = quadra & 0b1111;
        if (quadra < 10) {
            res += std::to_string(quadra);
        } else {
            res += (char)(quadra - 10 + 'A');
        }
    }
    return reverse(res);
}

auto reverse(std::string const &s) -> std::string {
    std::string rev;
    for (int i = s.size() - 1; i >= 0; i--) {
        rev = rev.append(1, s[i]);
    };
    return rev;
}

auto hexStrToDouble(const std::string &str) -> double {
    double mantissa;
    int i{0};
    int exp{0};
    int sign{0};
    int bias{1023};
    std::string rev = reverse(str), bstr;
    for (int i = 0; i < str.length(); i++) {
        int quadra;
        if (rev[i] >= '0' && rev[i] <= '9') {
            quadra = (int)(rev[i] - '0') & 0b1111;
        } else if (rev[i]  <= 'F') {
            quadra = (int)(rev[i] - 'A' + 10) & 0b1111;
        } else {
            throw std::exception();
        }
        for (int j{0}; j < 4; j++) {
            bstr += std::to_string((quadra & (0b1 << j)) == 0 ? 0 : 1);
        }
    }

    for (int i{0}, power{-52}; i < bstr.length(); i++, power++) {
        if (i < 52) {
            mantissa += (bstr[i] == '0' ? 0 : pow(2, power));
        } else if (i < 63) {
            exp += (bstr[i] == '0' ? 0 : 1) << (power);
        } else {
            sign = (bstr[i] == '0' ? 1 : -1);
        }
        
    }
    mantissa += 1;
    

    return sign * (mantissa * pow(2, exp - bias));
}

auto hexStrToFloat(const std::string &str) -> float {
    int bias{127};
    int exp{0};
    int sign{0};
    double mantissa{0};
    std::string rev = reverse(str), bstr;

    for (int i = 0; i < str.length(); i++) {
        int quadra;
        if (rev[i] >= '0' && rev[i] <= '9') {
            quadra = (int)(rev[i] - '0') & 0b1111;
        } else if (rev[i]  <= 'F') {
            quadra = (int)(rev[i] - 'A' + 10) & 0b1111;
        } else {
            throw std::exception();
        }
        for (int j{0}; j < 4; j++) {
            bstr += std::to_string((quadra & (0b1 << j)) == 0 ? 0 : 1);
        }
    }

    for (int i{0}, power{-23}; i < bstr.length(); i++, power++) {
        if (i < 23) {
            mantissa += (bstr[i] == '0' ? 0 : pow(2, power));
        } else if (i < 31) {
            exp += (bstr[i] == '0' ? 0 : 1) << (power);
        } else {
            sign = (bstr[i] == '0' ? 1 : -1);
        }
        
    }
    mantissa += 1;
    return sign * (mantissa * pow(2, exp - bias));
}

/*
6)
a) -501,063   24,375
b) -222,477   76,9141 0.05
7)
a) C2A0C000   4395A800
b) C07B1D6000000000     4075830000000000

C0715D0000000000 -277,8125
43BDF800 379,9375

-277,812
*/