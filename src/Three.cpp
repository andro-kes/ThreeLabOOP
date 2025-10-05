#include "Three.h"

#include <iostream>
#include <stdexcept>
#include <utility>

// ---- Ctors / Dtor ----
Three::Three() : size(1), number(new unsigned char[1]{'0'}) {}

Three::Three(std::size_t n, unsigned char fill) {
    if (n == 0) {
        size = 1;
        number = new unsigned char[1]{'0'};
        return;
    }
    if (!IsValidTernaryDigit(fill)) {
        throw std::invalid_argument("Invalid ternary digit in fill");
    }
    size = n;
    number = new unsigned char[size];
    for (std::size_t i = 0; i < size; ++i) number[i] = fill;
}

Three::Three(const std::initializer_list<unsigned char>& digits) {
    if (digits.size() == 0) {
        size = 1;
        number = new unsigned char[1]{'0'};
        return;
    }
    size = digits.size();
    number = new unsigned char[size];
    // store least significant digit at index 0
    std::size_t i = 0;
    for (auto it = digits.end(); it != digits.begin();) {
        --it;
        if (!IsValidTernaryDigit(*it)) {
            delete[] number;
            number = nullptr;
            throw std::invalid_argument("Invalid ternary digit in initializer list");
        }
        number[i++] = *it;
    }
}

Three::Three(const std::string& digits) {
    if (digits.empty()) {
        size = 1;
        number = new unsigned char[1]{'0'};
        return;
    }
    size = digits.size();
    number = new unsigned char[size];
    for (std::size_t i = 0; i < size; ++i) {
        unsigned char ch = static_cast<unsigned char>(digits[size - 1 - i]);
        if (!IsValidTernaryDigit(ch)) {
            delete[] number;
            number = nullptr;
            throw std::invalid_argument("Invalid ternary digit in string");
        }
        number[i] = ch;
    }
}

Three::Three(const Three& other) : size(other.size), number(new unsigned char[other.size]) {
    for (std::size_t i = 0; i < size; ++i) number[i] = other.number[i];
}

Three::Three(Three&& other) noexcept : size(other.size), number(other.number) {
    other.size = 0;
    other.number = nullptr;
}

Three& Three::operator=(const Three& other) {
    if (this == &other) return *this;
    unsigned char* newBuf = new unsigned char[other.size];
    for (std::size_t i = 0; i < other.size; ++i) newBuf[i] = other.number[i];
    delete[] number;
    number = newBuf;
    size = other.size;
    return *this;
}

Three& Three::operator=(Three&& other) noexcept {
    if (this == &other) return *this;
    delete[] number;
    number = other.number;
    size = other.size;
    other.number = nullptr;
    other.size = 0;
    return *this;
}

Three::~Three() { delete[] number; }

// ---- Helpers ----
unsigned char Three::CharToDigit(unsigned char c) { return static_cast<unsigned char>(c - '0'); }
unsigned char Three::DigitToChar(unsigned char d) { return static_cast<unsigned char>(d + '0'); }
std::size_t Three::GetMaxSize(const std::size_t& x, const std::size_t& y) { return x > y ? x : y; }

bool Three::IsValidTernaryDigit(unsigned char c) { return c >= '0' && c <= '2'; }

void Three::ValidateDigits(const unsigned char* data, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        if (!IsValidTernaryDigit(data[i])) {
            throw std::invalid_argument("Invalid ternary digit");
        }
    }
}

// ---- Observers ----
std::string Three::ToString() const {
    if (!number || size == 0) return std::string();
    std::string out;
    out.reserve(size);
    for (std::size_t i = size; i > 0; --i) {
        out.push_back(static_cast<char>(number[i - 1]));
    }
    return out;
}

void Three::Print() const { std::cout << ToString() << '\n'; }

// ---- Arithmetic ----
Three Three::Sum(const Three& other) const {
    std::size_t maxSize = GetMaxSize(size, other.size) + 1; // +1 for potential carry
    unsigned char* tmp = new unsigned char[maxSize]{}; // zeroed
    unsigned char carry = 0;

    for (std::size_t i = 0; i < maxSize - 1; ++i) {
        unsigned char dx = (i < size) ? CharToDigit(number[i]) : 0;
        unsigned char dy = (i < other.size) ? CharToDigit(other.number[i]) : 0;
        unsigned char s = static_cast<unsigned char>(dx + dy + carry);
        carry = static_cast<unsigned char>(s / 3);
        tmp[i] = DigitToChar(static_cast<unsigned char>(s % 3));
    }

    std::size_t resultSize = carry ? maxSize : (maxSize - 1);
    if (carry) tmp[maxSize - 1] = DigitToChar(carry);

    Three result(resultSize, '0');
    for (std::size_t i = 0; i < resultSize; ++i) result.number[i] = tmp[i];
    delete[] tmp;
    return result;
}

Three Three::Sub(const Three& other) const {
    // Ensure non-negative result
    if (other.More(*this)) {
        throw std::invalid_argument("Subtraction would lead to a negative value");
    }
    std::size_t maxSize = size;
    unsigned char* tmp = new unsigned char[maxSize]{};
    unsigned char borrow = 0;

    for (std::size_t i = 0; i < maxSize; ++i) {
        unsigned char dx = (i < size) ? CharToDigit(number[i]) : 0;
        unsigned char dy = (i < other.size) ? CharToDigit(other.number[i]) : 0;
        unsigned char val;
        if (dx < static_cast<unsigned char>(dy + borrow)) {
            dx = static_cast<unsigned char>(dx + 3);
            val = static_cast<unsigned char>(dx - dy - borrow);
            borrow = 1;
        } else {
            val = static_cast<unsigned char>(dx - dy - borrow);
            borrow = 0;
        }
        tmp[i] = DigitToChar(val);
    }

    // Trim leading zeros (most significant side)
    std::size_t resultSize = maxSize;
    while (resultSize > 1 && tmp[resultSize - 1] == '0') {
        --resultSize;
    }

    Three result(resultSize, '0');
    for (std::size_t i = 0; i < resultSize; ++i) result.number[i] = tmp[i];
    delete[] tmp;
    return result;
}

// ---- Comparison ----
bool Three::Equal(const Three& other) const {
    if (size != other.size) return false;
    for (std::size_t i = 0; i < size; ++i) {
        if (number[i] != other.number[i]) return false;
    }
    return true;
}

bool Three::Less(const Three& other) const {
    if (size != other.size) return size < other.size;
    // same size: compare from most significant digit
    for (std::size_t i = size; i > 0; --i) {
        if (number[i - 1] != other.number[i - 1]) {
            return number[i - 1] < other.number[i - 1];
        }
    }
    return false; // equal
}

bool Three::More(const Three& other) const { return !Equal(other) && !Less(other); }
