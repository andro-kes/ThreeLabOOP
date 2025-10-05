// Demo program using Three library
#include <iostream>
#include "../include/Three.h"

int main() {
    Three a{"12"};
    Three b{"21"};
    Three c = a.Sum(b);
    std::cout << "12 + 21 = " << c.ToString() << "\n";

    Three d{"21"};
    Three e{"12"};
    Three f = d.Sub(e);
    std::cout << "21 - 12 = " << f.ToString() << "\n";
    return 0;
}