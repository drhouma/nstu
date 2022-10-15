#include <iostream>
#include <bitset>
#include <cmath>
#include <climits>

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
        double dinput;
        unsigned long long output;
    };

auto Menu(int &len) -> void {
    while (true) {
        system("clear");
        int option;
        std::cout << ".______________________________.\n";
        std::cout << "|------------------------------|\n";
        std::cout << "|             MENU             |\n";
        std::cout << "|------------------------------|\n";
        std::cout << "|1 - part 6                    |\n";
        std::cout << "|2 - part 7                    |\n";
        std::cout << "|3 - set number len(4 || 8)    |\n"; 
        std::cout << "|0 - exit                      |\n";     
        std::cout << "|______________________________|\n";
        std::cin >> option;
        switch (option)
        {
            case 1:
            {
                std::cout << "Введите число с плавающей запятой\n";
                data number;
                std::cin >> number.dinput;
                number.input = number.dinput;
                if (len == 4) {
                    std::bitset<sizeof(float) * CHAR_BIT> bits(number.output);
                    std::cout << bits << '\n';
                    number.output = bits.to_ulong();
                } else {
                    std::bitset<sizeof(double) * CHAR_BIT> bits(number.output);
                    std::cout << bits << '\n';
                    number.output = bits.to_ulong();
                }
                std::string result;
                std::cout << binaryToHex(number.output, len) << std::endl << "press enter to continue ...\n";
                break;
            }
            case 2:
            {
                std::string number;
                std::cin >> number;
                if (number.length() != len * 2) {
                    std::cout << "Неверная длина слова!\n";
                    throw std::exception();
                }
                double db;
                if (len == 4) {
                    db = hexStrToFloat(number);
                } else {
                    db = hexStrToDouble(number);
                }

                std::cout << db << '\n' << "press enter to continue ...\n";
                // double res = pow(2, db.exp) * db.mantissa / ;

                break;
            }
            case 3:
            {
                std::cout << "Введите длину слова (4 или 8)\n";
                int prevlen = len;
                std::cin >> len;
                if (len != 4 && len != 8) {
                    len = prevlen;
                    std::cout << "Неверная длина слова!\n";
                    throw std::exception();
                }
                std::cout << "Nice!\npress enter to continue...\n";
                break;
            }
            case 0:
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
    std::cin.exceptions(std::ios_base::failbit);
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
    for (int i = 1; i <= len * 2; i++) {
        quadra = number >> (4 * (len * 2 - i));
        quadra = quadra & 0b1111;
        if (quadra < 10) {
            res += std::to_string(quadra);
        } else {
            res += (char)(quadra - 10 + 'A');
        }
    }
    return res;
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

// 0100 0000 0101

// 0100 0000 0101 1110 1100 0111 1101 1111 0100 0010 1111 0110 0011 1110 1111 1010
// 0100 0000 0101 1110 1100 0111 1101 1111 0100 0010 1111 0110 0011 1110 1111 1010
// 0 10000101 11101100011111011111010
// 0 10000101 11101100011111011111010