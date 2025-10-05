#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

class Three {
public:
    Three();
    Three(std::size_t n, unsigned char fill = '0');
    Three(const std::initializer_list<unsigned char>& digits);
    explicit Three(const std::string& digits);

    Three(const Three& other);
    Three(Three&& other) noexcept;
    Three& operator=(const Three& other);
    Three& operator=(Three&& other) noexcept;
    ~Three();

    // Observers
    std::string ToString() const;
    void Print() const;

    // Arithmetic
    Three Sum(const Three& other) const;
    Three Sub(const Three& other) const; // throws if result would be negative

    // Comparison
    bool Equal(const Three& other) const;
    bool Less(const Three& other) const;
    bool More(const Three& other) const;

    // Validation helper
    static bool IsValidTernaryDigit(unsigned char c);

private:
    static unsigned char CharToDigit(unsigned char c);
    static unsigned char DigitToChar(unsigned char d);
    static std::size_t GetMaxSize(const std::size_t& x, const std::size_t& y);
    static void ValidateDigits(const unsigned char* data, std::size_t n);

    std::size_t size {0};
    unsigned char* number {nullptr};
};
