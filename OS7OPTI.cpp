#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
int main(){
int l;
cout << "\nENTER THE LENGTH OF REFERENCE STRING :";
cin >> l;
int arr[l], pf = 0, ph = 0, flag1 = 0, flag2 = 0, flag3 = 0, count1 = 0,
            count2 = 0, count3 = 0;
cout << "\nENTER THE REFERENCE STRING:\n";
for (int i = 0; i < l; i++) {
  cout << "-> ";
  cin >> arr[i];
}
cout << endl;
int a = -1, b = -1, c = -1, d = 0, i = 0, f1 = 0, f2 = 1, f3 = 1;
while (i < l) {
  d = arr[i];
  if (a == -1) {
    a = d;
    pf++;
    cout << a << endl;
  } else if (b == -1) {
    b = d;
    pf++;
    cout << a << "\t" << b << endl;
  } else if (c == -1) {
    c = d;
    pf++;
    cout << a << "\t" << b << "\t" << c << endl;
  }
  if (i > 2) {
    if (d == a || d == b || d == c) {
      ph++;
      cout << endl;
    } else {
      flag1 = 0, flag3 = 0, flag2 = 0;
      count1 = 0, count2 = 0, count3 = 0;
      for (int k = i; k < l; k++) {
        if (arr[k] == a && flag1 == 0) {
          flag1 = 1;
        } else if (arr[k] == b && flag2 == 0) {
          flag2 = 1;
        } else if (arr[k] == c && flag3 == 0) {
          flag3 = 1;
        }
        if (flag1 == 0) {
          count1++;
        }
        if (flag2 == 0) {
          count2++;
        }
        if (flag3 == 0) {
          count3++;
        }
        if (flag1 == 1 && flag2 == 1 && flag3 == 1) {
          break;
        }
      }
      if (count1 > count2 && count1 > count3) {
        a = d;
        pf++;
      } else if (count2 > count1 && count2 > count3) {
        b = d;
        pf++;
      } else if (count3 > count2 && count3 > count1) {
        c = d;
        pf++;
      } else {
        if (flag1 == 0) {
          a = d;
        } else if (flag2 == 0) {
          b = d;
        } else {
          c = d;
        }
        pf++;
      }
      cout << a << "\t" << b << "\t" << c << endl;
    }
  }
  i++;
}
cout << "\nPAGE FAULTS:" << pf;
cout << "\nPAGE HITS:" << ph << endl;
}
