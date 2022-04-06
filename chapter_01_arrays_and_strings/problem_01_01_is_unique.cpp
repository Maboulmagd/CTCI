//
// Created by Mo Aboulmagd on 3/5/22.
//

/*
 * Implement an algorithm to determine if a string has all unique characters.
 * What if you cannot use additional data structures?
 */

#include "include.h"

/*
 * Key idea is to use an array to keep track of characters which have already been seen.
 */

// Complexity Analysis:
// Time: O(N), where N is the length of the string.
// Space: O(1) since we are using an array of fixed size (256).

bool IsUnique(string s) {
    if (s.length() > 256) { return false; }

    array<bool, 256> extended_ascii;
    fill(extended_ascii.begin(), extended_ascii.end(), false);

    bool is_unique = true;

    for (const char& c : s) {
        if (extended_ascii[c]) {
            is_unique = false;
            break;
        }
        extended_ascii[c] = true;
    }

    return is_unique;
}

// Complexity Analysis:
// Time: O(N), where N is the length of the string.
// Space: O(1) since we are using a bit vector.

// If the string STRICTLY consists of lower-case english letters a through z, can we do better? Yes, we can simply use a bit vector.
bool IsUniqueWithBitVector(string s) {
    int checker = 0;// the bit vector

    bool is_unique = true;

    for (const char& c : s) {
        const int val = c - 'a';
        if ((checker & (1 << val)) > 0) {// val & (1 << val) will zero-out all bits to the right (lower bits) of the bit vector
            is_unique = false;
            break;
        }
        checker |= (1 << val);
    }

    return is_unique;
}

TEST(IsUnique, BasicTests) {
    ASSERT_EQ(IsUnique("abc"), true);
    ASSERT_EQ(IsUnique("abcdefghijklmnopqrstuvwxyz"), true);
    ASSERT_EQ(IsUnique("MoisaScholar"), false);
    ASSERT_EQ(IsUnique("!@#$%^&*()`abcdefghijklmnopqrstuvwxyz "), true);
    ASSERT_EQ(IsUnique("!@#$%^&*()`abcdefghijklmnopqrstuvwxyz  "), false);

    ASSERT_EQ(IsUniqueWithBitVector("abc"), true);
    ASSERT_EQ(IsUniqueWithBitVector("abcdefghijklmnopqrstuvwxyz"), true);
    ASSERT_EQ(IsUniqueWithBitVector("abcdefghijklmnopqrstuvwxyzz"), false);
}