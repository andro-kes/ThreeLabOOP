#include "../src/three.h"
#include <gtest/gtest.h>

TEST(ThreeTest, InitializerList) {
    Three objList = Three({'1', '0', '2'});
    EXPECT_EQ(objList.Get(), "102");
}

TEST(ThreeTest, ZeroValue) {
    Three objEmpty = Three();
    EXPECT_EQ(objEmpty.Get(), "0");
}

TEST(ThreeTest, CharValue) {
    Three objChar = Three(1, '2');
    EXPECT_EQ(objChar.Get(), "2");
}

TEST(ThreeTest, StringConstructor) {
    Three objString = Three("1010210");
    EXPECT_EQ(objString.Get(), "1010210");
}

TEST(ThreeTest, CopyConstructor) {
    Three original = Three("102");
    Three copy = Three(original);
    EXPECT_EQ(copy.Get(), "102");
}

TEST(ThreeTest, SumOperation) {
    Three num1 = Three("12");
    Three num2 = Three("21");
    Three result = num1.Sum(num2);
    EXPECT_EQ(result.Get(), "110");
}

TEST(ThreeTest, SumWithCarry) {
    Three num1 = Three("222"); 
    Three num2 = Three("111"); 
    Three result = num1.Sum(num2);
    EXPECT_EQ(result.Get(), "1110"); 
}

TEST(ThreeTest, SubOperation) {
    Three num1 = Three("21");
    Three num2 = Three("12");
    Three result = num1.Sub(num2);
    EXPECT_EQ(result.Get(), "2");
}

TEST(ThreeTest, SubWithBorrow) {
    Three num1 = Three("100"); 
    Three num2 = Three("1");  
    Three result = num1.Sub(num2);
    EXPECT_EQ(result.Get(), "22"); 
}

TEST(ThreeTest, EqualTrue) {
    Three num1 = Three("102");
    Three num2 = Three("102");
    EXPECT_TRUE(num1.Equal(num2));
}

TEST(ThreeTest, EqualFalse) {
    Three num1 = Three("102");
    Three num2 = Three("101");
    EXPECT_FALSE(num1.Equal(num2));
}

TEST(ThreeTest, LessTrue) {
    Three num1 = Three("101");
    Three num2 = Three("102");
    EXPECT_TRUE(num1.Less(num2));
}

TEST(ThreeTest, LessFalse) {
    Three num1 = Three("102");
    Three num2 = Three("101");
    EXPECT_FALSE(num1.Less(num2));
}

TEST(ThreeTest, MoreTrue) {
    Three num1 = Three("102");
    Three num2 = Three("101");
    EXPECT_TRUE(num1.More(num2));
}

TEST(ThreeTest, MoreFalse) {
    Three num1 = Three("101");
    Three num2 = Three("102");
    EXPECT_FALSE(num1.More(num2));
}

TEST(ThreeTest, CompareDifferentLength) {
    Three num1 = Three("1000"); // 27 в десятичной
    Three num2 = Three("222");  // 26 в десятичной
    EXPECT_TRUE(num1.More(num2));
    EXPECT_FALSE(num1.Less(num2));
    EXPECT_FALSE(num1.Equal(num2));
}

TEST(ThreeTest, EdgeCaseZeroResult) {
    Three num1 = Three("10");
    Three num2 = Three("10");
    Three result = num1.Sub(num2);
    EXPECT_EQ(result.Get(), "0");
}