#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <new>
#include <cstdlib>

class Three {
public:
    Three();
    Three(const size_t &n, unsigned char t = 0);
    Three(const std::initializer_list<unsigned char> &t);
    Three(const std::string &t);
    Three(const Three &t);
    Three(Three &&other);
    ~Three();

    void Print();
    std::string Get();
    
    Three Sum(const Three &t);
    Three Sub(const Three &t);

    bool Equal(const Three &t);
    bool Less(const Three &t);
    bool More(const Three &t);

private:
    size_t size;
    unsigned char *number = nullptr;
    unsigned char charToDigit(unsigned char c);
    unsigned char digitToChar(unsigned char d);
    size_t getMaxSize(const size_t &x, const size_t &y);
    bool isValidTernaryDigit(unsigned char c);
};