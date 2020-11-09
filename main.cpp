#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9 + 7;

vector<vector<int>> add_char_to_stack(char c, char x, int k) {
    vector<vector<int>> a = vector<vector<int>> (k + 1, vector<int> (3, INF));
    int t = (c == x);
    a[0][0] = a[0][1] = a[0][2] = 1;
    a[t][0] = a[t][1] = a[t][2] = 1;
    return a;
}

vector<vector<int>> get_neutral(int k) {
    vector<vector<int>> a = vector<vector<int>> (k + 1, vector<int> (3, INF));
    a[0][0] = a[0][1] = a[0][2] = 0;
    return a;
}

void sum_of_langs_on_stack(vector<vector<vector<int>>> &dp) {
    vector<vector<int>> a = dp.back();
    dp.pop_back();
    vector<vector<int>> b = dp.back();
    dp.pop_back();
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < 3; j++)
            a[i][j] = min(a[i][j], b[i][j]);
    dp.push_back(a);
}

void mul_of_langs_on_stack(vector<vector<vector<int>>> &dp) {
    vector<vector<int>> b = dp.back();
    dp.pop_back();
    vector<vector<int>> a = dp.back();
    dp.pop_back();
    int k = a.size() - 1;
    vector<vector<int>> c = vector<vector<int>> (k + 1, vector<int> (3, INF));
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k; j++) {
            c[i][0] = min(c[i][0], a[i][0] + b[j][0]);
            c[j][0] = min(c[j][0], a[i][0] + b[j][0]);
            c[min(i + j, k)][0] = min(c[min(i + j, k)][0], a[i][1] + b[j][2]);
            for (int t = 0; t < 3; t++) {
                c[i][2] = min(c[i][2], a[i][2] + b[j][t]);
                c[j][1] = min(c[j][1], a[i][t] + b[j][1]);
            }
            if (a[i][0] == i)
                c[min(i + j, k)][2] = min(c[min(i + j, k)][2], a[i][0] + b[j][2]);
            if (b[j][0] == j)
                c[min(i + j, k)][1] = min(c[min(i + j, k)][2], a[i][1] + b[j][0]);
        }
    for (int i = k - 1; i >= 0; i--) {
        c[i][0] = min(c[i + 1][0], c[i][0]);
        c[i][1] = min(c[i + 1][1], c[i][1]);
        c[i][2] = min(c[i + 1][2], c[i][2]);
    }
    dp.push_back(c);
}

void klini_lang(vector<vector<vector<int>>> &dp) {
    vector<vector<int>> a = dp.back();
    dp.pop_back();
    int k = a.size() - 1;
    vector<vector<int>> e = get_neutral(k);
    dp.push_back(e);
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < i; j++)
            dp.push_back(a);
        for (int j = 0; j < i - 1; j++)
            mul_of_langs_on_stack(dp);
    }
    for (int i = 0; i < k; i++)
        sum_of_langs_on_stack(dp);
}

void solve(string s, char x, int k) {
    vector<vector<vector<int>>> dp;
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
    if (dp[0][k][0] == INF)
        cout << "INF" << endl;
    else
        cout << dp[0][k][0] << endl;
}

int main() {
    int t = 1;
    for (int i = 0; i < t; i++) {
        string s;
        char x;
        int k;
        cin >> s >> x >> k;
        solve(s, x, k);
    }
    return 0;
}
// baac...caaab....+ a 4                 ans = INF
// baac...caaab....+ a 2                 ans = 4
// ab+c.aba.*.bac.+.+* b 2               ans = 4
// acb..bab.c.*.ab.ba.+.+*a. b 3         ans = 7