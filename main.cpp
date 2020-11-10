#include <iostream>
#include "solve.h"

int main() {
    int t = 1;
    for (int i = 0; i < t; i++) {
        std::string s;
        char x;
        int k;
        std::cin >> s >> x >> k;
        int ans = solve(s, x, k);
        if (ans == INF)
            std::cout << "INF" << std::endl;
        else
            std::cout << ans << std::endl;
    }
    return 0;
}
// baac...caaab....+ a 4                 ans = INF
// baac...caaab....+ a 2                 ans = 4
// ab+c.aba.*.bac.+.+* b 2               ans = 4
// acb..bab.c.*.ab.ba.+.+*a. b 3         ans = 7
