#include "three.h"

int main() {
    // Use all ways for initializing number
    Three objList = Three({'1', '0', '2'});
    Three objEmpty = Three();
    Three objChar = Three(1, '2');
    Three objString = Three("1010210");
    Three objCopy = Three(objString);

    std::cout << "Сложение\n";
    Three num1 = Three("12"); 
    Three num2 = Three("21");  
    
    Three sumResult = num1.Sum(num2);
    std::cout << "Результат сложения: ";
    sumResult.Print();

    std::cout << "\nВычитание\n";
    Three num3 = Three("21");
    Three num4 = Three("12"); 
    
    Three subResult = num3.Sub(num4);
    std::cout << "Результат вычитания: ";
    subResult.Print();

    return 0;
}