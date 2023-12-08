#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], ar[n], bt[n], ct[n], ta[n], wt[n];
    float avgwt = 0, avgta = 0;

    for (int i = 0; i < n; i++) {
        cout << "Enter process " << (i + 1) << " arrival time: ";
        cin >> ar[i];
        cout << "Enter process " << (i + 1) << " burst time: ";
        cin >> bt[i];
        pid[i] = i + 1;
    }

    // Sorting according to arrival times
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - (i + 1); j++) {
            if (ar[j] > ar[j + 1]) {
                swap(ar[j], ar[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    // Finding completion times
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            ct[i] = ar[i] + bt[i];
        } else {
            if (ar[i] > ct[i - 1]) {
                ct[i] = ar[i] + bt[i];
            } else {
                ct[i] = ct[i - 1] + bt[i];
            }
        }
        ta[i] = ct[i] - ar[i];
        wt[i] = ta[i] - bt[i];
        avgwt += wt[i];
        avgta += ta[i];
    }

    cout << "\npid  arrival  burst  complete turn waiting\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "    " << ar[i] << "       " << bt[i] << "       " << ct[i] << "       " << ta[i] << "       " << wt[i] << endl;
    }

    cout << "\nAverage waiting time: " << (avgwt / n) << endl;
    cout << "Average turnaround time: " << (avgta / n) << endl;

    return 0;
}

//Enter number of processes: 4
//Enter process 1 arrival time: 0
//Enter process 1 burst time: 3
//Enter process 2 arrival time: 2
//Enter process 2 burst time: 5
//Enter process 3 arrival time: 4
//Enter process 3 burst time: 2
//Enter process 4 arrival time: 6
//Enter process 4 burst time: 4
//
//pid  arrival  burst  complete turn waiting
//1    0       3       3       3       0
//2    2       5       8       6       1
//3    4       2       10       6       4
//4    6       4       14       8       4
//
//Average waiting time: 2.25
//Average turnaround time: 5.75
