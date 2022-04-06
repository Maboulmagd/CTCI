//
// Created by Mo Aboulmagd on 4/6/22.
//

/*
 * Given two strings, write a method to decide if one is a permutation of the other.
 */

#include "include.h"

/*
 * Key idea is to use an array to keep track of characters which have already been seen, or we can use sorting.
 */

// Complexity Analysis:
// Time: O(max(256, S + T)), since both strings must have same length for them to even be permutations of each other.
// Space: O(1) since we are using a fixed array of size 256.

bool IsPermutation(string s, string t) {
    const int s_len = static_cast<int>(s.length());
    const int t_len = static_cast<int>(t.length());

    // If the strings differ in length, then it is impossible for one to be a permutation of the other
    if (s_len != t_len) {
        return false;
    }

    array<int, 256> extended_ascii;
    fill(extended_ascii.begin(), extended_ascii.end(), 0);

    for (int i = 0; i < s_len; ++i) {
        extended_ascii[s[i]]++;
        extended_ascii[t[i]]--;
    }

    bool is_permutation = true;

    for (int i = 0; i < extended_ascii.size(); ++i) {
        if (extended_ascii[i] != 0) {
            is_permutation = false;
            break;
        }
    }

    return is_permutation;
}

// Complexity Analysis:
// Time: O(s lg s), since s and t have to be the same length before we even consider if they are permutations of each other.
// Space: O(1)

bool IsPermutationWithSorting(string s, string t) {
    const int s_len = static_cast<int>(s.length());
    const int t_len = static_cast<int>(t.length());

    // If the strings differ in length, then it is impossible for one to be a permutation of the other
    if (s_len != t_len) {
        return false;
    }

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    bool is_permutation = true;

    for (int i = 0; i < s_len; ++i) {
        if (s[i] != t[i]) {
            is_permutation = false;
            break;
        }
    }

    return is_permutation;
}

TEST(IsPermutation, BasicTests) {
    ASSERT_EQ(IsPermutation("abc", "cab"), true);
    ASSERT_EQ(IsPermutation("God", "dog"), false);
    ASSERT_EQ(IsPermutation("god      ", "dog"), false);
    ASSERT_EQ(IsPermutation("GoD", "DoG"), true);

    ASSERT_EQ(IsPermutationWithSorting("abc", "cab"), true);
    ASSERT_EQ(IsPermutationWithSorting("God", "dog"), false);
    ASSERT_EQ(IsPermutationWithSorting("god      ", "dog"), false);
    ASSERT_EQ(IsPermutationWithSorting("GoD", "DoG"), true);
}