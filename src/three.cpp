#include "three.h"
#include <stdexcept>

Three::Three() {
    size = 1;
    number = new unsigned char[size]{ '0' };
}

Three::Three(const size_t &n, unsigned char t) {
    if (!isValidTernaryDigit(t)) {
        throw std::invalid_argument("Число должно быть троичным");
    }
    size = n;
    number = new unsigned char[n]{ t };
    Print();
}

Three::Three(const std::initializer_list<unsigned char> &t) {
    size = t.size();
    if (size > 0) {
        number = new unsigned char[size]{};
        for (size_t i = 0; i < size; i++) {
            if (!isValidTernaryDigit(*(t.end() - 1 - i))) {
                throw std::invalid_argument("Число должно быть троичным");
            }
            number[i] = *(t.end() - 1 - i);
        }
    } else {
        size = 1;
        number = new unsigned char[size]{ '0' };
    }
    Print();
}

Three::Three(const std::string &t) {
    size = t.length();
    if (size > 0) {
        number = new unsigned char[size]{};
        for (size_t i = 0; i < size; i++) {
            if (!isValidTernaryDigit(t[size - 1 - i]) ){
                throw std::invalid_argument("Число должно быть троичным");
            }
            number[i] = t[size - 1 - i];
        }
    } else {
        size = 1;
        number = new unsigned char[size]{ '0' };
    }
    Print();
}

Three::Three(const Three &t) {
    size = t.size;
    number = new unsigned char[size]{};
    for (size_t i = 0; i < size; i++) {
        number[i] = t.number[i];
    }
    Print();
}

Three::Three(Three &&other) noexcept {
    size = other.size;
    number = other.number;
    other.size = 0;
    other.number = nullptr;
}

Three::~Three() {
    delete[] number;
}

void Three::Print() {
    // Print in reverse order
    for (size_t i = size; i > 0; i--) {
        std::cout << number[i-1];
    }
    std::cout << "\n";
}

std::string Three::Get() {
    std::string result {};
    for (size_t i = size; i > 0; i--) {
        result += number[i-1];
    }
    return result;
}

// helpers
unsigned char Three::charToDigit(unsigned char c) {
    return c - '0';
}

unsigned char Three::digitToChar(unsigned char d) {
    return d + '0';
}

size_t Three::getMaxSize(const size_t &x, const size_t &y) {
    if (x > y) {
        return x;
    }
    return y;
}

bool Three::isValidTernaryDigit(unsigned char c) {
    return c >= '0' && c <= '2';
}

// obj + t
Three Three::Sum(const Three &t) {
    size_t maxSize = getMaxSize(this->size, t.size) + 1;
    unsigned char *result = new unsigned char[maxSize]{};
    unsigned char carry = 0;
    
    for (size_t i = 0; i < maxSize - 1; i++) {
        unsigned char dX = (i < this->size) ? charToDigit(this->number[i]) : 0;
        unsigned char dY = (i < t.size) ? charToDigit(t.number[i]) : 0;
        
        unsigned char sum = dX + dY + carry;
        carry = sum / 3;
        result[i] = digitToChar(sum % 3);
    }
    
    size_t resultSize;
    if (carry > 0) {
        result[maxSize - 1] = digitToChar(carry);
        resultSize = maxSize;
    } else {
        resultSize = maxSize - 1;
    }
    
    Three resultObj;
    delete[] resultObj.number; 
    resultObj.size = resultSize;
    resultObj.number = new unsigned char[resultSize];
    for (size_t i = 0; i < resultSize; i++) {
        resultObj.number[i] = result[i];
    }
    
    delete[] result;
    return resultObj;
}

Three Three::Sub(const Three &t) {
    size_t maxSize = this->size;
    unsigned char *result = new unsigned char[maxSize]{};
    unsigned char borrow = 0;
    
    for (size_t i = 0; i < maxSize; i++) {
        unsigned char dX = (i < this->size) ? charToDigit(this->number[i]) : 0;
        unsigned char dY = (i < t.size) ? charToDigit(t.number[i]) : 0;
        
        if (dX < dY + borrow) {
            dX += 3;
            result[i] = digitToChar(dX - dY - borrow);
            borrow = 1;
        } else {
            result[i] = digitToChar(dX - dY - borrow);
            borrow = 0;
        }
    }
    
    // Remove zeros
    size_t resultSize = maxSize;
    while (resultSize > 1 && result[resultSize - 1] == '0') {
        resultSize--;
    }
    
    Three resultObj;
    delete[] resultObj.number;
    resultObj.size = resultSize;
    resultObj.number = new unsigned char[resultSize];
    for (size_t i = 0; i < resultSize; i++) {
        resultObj.number[i] = result[i];
    }
    
    delete[] result;
    return resultObj;
}

bool Three::Equal(const Three &t) {
    if (size != t.size) {
        return false;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (number[i] != t.number[i]) {
            return false;
        }
    }

    return true;
}

bool Three::Less(const Three &t) {
    if (size < t.size) {
        return true;
    } else if (size > t.size) {
        return false;
    } else if (size == t.size) {
        for (size_t i = 0; i < size; i++) {
            if (number[i] > t.number[i]) {
                return false;
            }
        }
    }

    return !Equal(t);
}

bool Three::More(const Three &t) {
    return !Less(t);
}
