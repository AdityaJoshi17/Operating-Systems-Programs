#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
int main() {
  int n, a[50], frame[10], no, k, avail, count = 0;
  cout << "\n Enter the number of pages :\n";
  cin >> n;
  cout << "\n Enter the value for page number \n";
  for (int i = 1; i <= n; i++) {
    cout << "Page no a[" << i << "] ";
    cin >> a[i];
  }
  cout << "\nEnter number of frames\n";
  cin >> no;
  for (int i = 0; i < no; i++) {
    frame[i] = -1;
  }
  int j = 0;
  cout << "\tRef Pg Number\t Page frames\n";
  for (int i = 1; i <= n; i++)
    {
        cout << "\t\t" << a[i];
        avail = 0;
        for (k = 0; k < no; k++) {
          if (frame[k] == a[i])
            avail = 1;
        }
        if (avail == 0) {
          frame[j] = a[i];
          j = (j + 1) % no;
          count++;
          for (k = 0; k < no; k++) {
            cout << "\t" << frame[k];
          }
        }
        cout << endl;
  }
  cout << "\nNumber of page fault : " << count;
  return 0;
}
