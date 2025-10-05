#include <gtest/gtest.h>
#include "../include/Three.h"

TEST(Three_Constructors, DefaultIsZero) {
    Three t;
    EXPECT_EQ(t.ToString(), "0");
}

TEST(Three_Constructors, FromSizeAndFill) {
    Three t(4, '2');
    EXPECT_EQ(t.ToString(), "2222");
}

TEST(Three_Constructors, FromInitializerList) {
    Three t({'1','0','2'});
    EXPECT_EQ(t.ToString(), "102");
}

TEST(Three_Constructors, FromString) {
    Three t(std::string("1010210"));
    EXPECT_EQ(t.ToString(), "1010210");
}

TEST(Three_Constructors, ThrowsOnInvalidDigit) {
    EXPECT_THROW(Three(std::string("203")), std::invalid_argument);
    EXPECT_THROW(Three(3, '3'), std::invalid_argument);
}

TEST(Three_Arithmetic, SumSimple) {
    Three a{"2"};
    Three b{"2"};
    auto c = a.Sum(b);
    EXPECT_EQ(c.ToString(), "11");
    // immutability
    EXPECT_EQ(a.ToString(), "2");
    EXPECT_EQ(b.ToString(), "2");
}

TEST(Three_Arithmetic, SumDifferentSizes) {
    Three a{"2"}; // 2
    Three b{"21"}; // 7
    auto c = a.Sum(b); // 9 -> 100
    EXPECT_EQ(c.ToString(), "100");
}

TEST(Three_Arithmetic, SubBorrowAndTrim) {
    Three a{"1000"}; // 27
    Three b{"1"};    // 1
    auto c = a.Sub(b); // 26 -> 222
    EXPECT_EQ(c.ToString(), "222");
}

TEST(Three_Arithmetic, SubRejectsNegative) {
    Three a{"12"};
    Three b{"21"};
    EXPECT_THROW(a.Sub(b), std::invalid_argument);
}

TEST(Three_Comparison, EqualLessMore) {
    Three a{"12"};
    Three b{"12"};
    Three c{"21"};
    EXPECT_TRUE(a.Equal(b));
    EXPECT_FALSE(a.Equal(c));

    EXPECT_TRUE(a.Less(c));   // 5 < 7
    EXPECT_FALSE(c.Less(a));

    EXPECT_TRUE(c.More(a));
    EXPECT_FALSE(a.More(c));
}
