#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "solve.h"

using std::string;
using std::vector;
using std::min;

struct i_count_of_x_status {
    int x_containing = 0;
    int x_ending = 0;
    int x_begining = 0;
};

using lang_status = vector<i_count_of_x_status>;
using stack_of_langs = vector<lang_status>;

lang_status add_char_to_stack(char c, char x, int k) {
    lang_status new_lang = vector<i_count_of_x_status>(k + 1, {INF, INF, INF});
    int t = (c == x);
    new_lang[0] = {1, 1, 1};
    new_lang[t] = {1, 1, 1};
    return new_lang;
}

lang_status get_neutral(int k) {
    lang_status e = vector<i_count_of_x_status>(k + 1, {INF, INF, INF});
    e[0] = {0, 0, 0};
    return e;
}

void sum_of_langs_on_stack(stack_of_langs &dp) {
    lang_status first_lang = dp.back();
    dp.pop_back();
    lang_status second_lang = dp.back();
    dp.pop_back();
    for (int i = 0; i < first_lang.size(); i++)
        first_lang[i] = {min(first_lang[i].x_containing, second_lang[i].x_containing),
                         min(first_lang[i].x_ending, second_lang[i].x_ending),
                         min(first_lang[i].x_begining, second_lang[i].x_begining)};
    dp.push_back(first_lang);
}

void mul_of_langs_on_stack(stack_of_langs &dp) {
    lang_status first_lang = dp.back();
    dp.pop_back();
    lang_status second_lang = dp.back();
    dp.pop_back();
    int k = first_lang.size() - 1;
    lang_status new_lang = vector<i_count_of_x_status>(k + 1, {INF, INF, INF});
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k; j++) {
            // containing i or j number of x, not counting one of langs
            new_lang[i].x_containing = min(new_lang[i].x_containing,
                                           first_lang[i].x_containing + second_lang[j].x_containing);
            new_lang[j].x_containing = min(new_lang[j].x_containing,
                                           first_lang[i].x_containing + second_lang[j].x_containing);
            // containing i + j number of x, cluing suffix and prefix
            new_lang[min(i + j, k)].x_containing = min(new_lang[min(i + j, k)].x_containing,
                                                       first_lang[i].x_ending + second_lang[j].x_begining);
            // prefix and suffix of x, not counting one of langs
            new_lang[i].x_begining = min(new_lang[i].x_begining,
                                         first_lang[i].x_begining +
                                         min({second_lang[j].x_containing, second_lang[j].x_ending,
                                              second_lang[j].x_begining}));
            new_lang[j].x_begining = min(new_lang[j].x_ending,
                                         second_lang[j].x_ending +
                                         min({first_lang[i].x_containing, first_lang[i].x_ending,
                                              first_lang[i].x_begining}));
            // prefix of x if the first word consists of only x
            if (first_lang[i].x_containing == i)
                new_lang[min(i + j, k)].x_begining = min(new_lang[min(i + j, k)].x_begining,
                                                         first_lang[i].x_containing + second_lang[j].x_ending);
            // suffix of x if the first word consists of only x
            if (second_lang[j].x_containing == j)
                new_lang[min(i + j, k)].x_ending = min(new_lang[min(i + j, k)].x_ending,
                                                       first_lang[i].x_ending + second_lang[j].x_containing);
        }
    for (int i = k - 1; i >= 0; i--) {
        new_lang[i] = {min(new_lang[i].x_containing, new_lang[i + 1].x_containing),
                       min(new_lang[i].x_ending, new_lang[i + 1].x_ending),
                       min(new_lang[i].x_begining, new_lang[i + 1].x_begining)};

    }
    dp.push_back(new_lang);
}

void klini_lang(stack_of_langs &dp) {
    lang_status kliniing_lang = dp.back();
    dp.pop_back();
    int k = kliniing_lang.size() - 1;
    lang_status e = get_neutral(k);
    dp.push_back(e);
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < i; j++)
            dp.push_back(kliniing_lang);
        for (int j = 0; j < i - 1; j++)
            mul_of_langs_on_stack(dp);
    }
    for (int i = 0; i < k; i++)
        sum_of_langs_on_stack(dp);
}

int solve(string s, char x, int k) {
    stack_of_langs dp;
    //vector<vector<vector<int>>> dp;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c >= 'a' && c <= 'c') {
            dp.push_back(add_char_to_stack(c, x, k));
        } else if (c == '+') {
            sum_of_langs_on_stack(dp);
        } else if (c == '*') {
            klini_lang(dp);
        } else { // c == '.'
            mul_of_langs_on_stack(dp);
        }
    }
    return dp[0][k].x_containing;
}