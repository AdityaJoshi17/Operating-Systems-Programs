#include <iostream>
#include <algorithm>
using namespace std;

bool search(int key, int fr[], int fn) {
    for (int i = 0; i < fn; i++)
        if (fr[i] == key)
            return true;
    return false;
}

int predict(int pg[], int fr[], int pn, int fn, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < fn; i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        if (j == pn)
            return i;
    }

    res = std::max(0, res);
    return res;
}

void optimalPage(int pg[], int pn, int fn) {
    int fr[fn] = { -1 };
    int hit = 0;

    for (int i = 0; i < pn; i++) {
        if (search(pg[i], fr, fn)) {
            hit++;
            continue;
        }

        if (fr[fn - 1] == -1)
            fr[i] = pg[i];
        else {
            int j = predict(pg, fr, pn, fn, i + 1);
            fr[j] = pg[i];
        }
    }

    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

int main() {
    int pg[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 , 1, 2, 0,1,7,0,1 };
    int pn = sizeof(pg) / sizeof(pg[0]);
    int fn = 4;
    optimalPage(pg, pn, fn);
    return 0;
}
