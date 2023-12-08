#include <iostream>
using namespace std;

int main() {
    int n, m, i, j, k;

    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter the number of resources: ";
    cin >> m;

    int alloc[n][m], max[n][m], avail[m];

    cout << "Enter the allocation matrix:\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    cout << "Enter the maximum matrix:\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (i = 0; i < m; i++) {
        cin >> avail[i];
    }

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < 5; k++) {
        // Outer loop runs for a fixed number of iterations (5 in this case)
        for (i = 0; i < n; i++) {
            // Inner loop iterates through each process 'i' in the system
            if (f[i] == 0) {
                // Check if process 'i' is not yet processed

                int flag = 0;
                // Initialize a flag to 0, indicating that the process 'i' is currently considered safe

                for (j = 0; j < m; j++) {
                    // Nested loop checks each resource 'j' for the process 'i'
                    if (need[i][j] > avail[j]) {
                        // Check if the resource need of process 'i' is greater than the available resource
                        flag = 1;
                        // If true, set flag to 1 and break out of the innermost loop
                        break;
                    }
                }

                if (flag == 0) {
                    // If flag is 0, process 'i' can be executed safely

                    ans[ind++] = i;
                    // Add the index of the safe process 'i' to the answer array

                    for (y = 0; y < m; y++)
                        // Update the available resources by adding the allocated resources of process 'i'
                        avail[y] += alloc[i][y];

                    f[i] = 1;
                    // Mark process 'i' as processed
                }
            }
        }
    }

    int flag = 1;

    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            cout << "The system is not safe." << endl;
            break;
        }
    }

    if (flag == 1) {
        cout << "The Safe Sequence is: \n";
        for (i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
    }

    return 0;
}

/*
Enter the number of processes: 5
Enter the number of resources: 3
Enter the allocation matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter the maximum matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the available resources:
3 3 2
The Safe Sequence is:
 P1 -> P3 -> P4 -> P0 -> P2

Process returned 0 (0x0)   execution time : 65.712 s
Press any key to continue.


*/

