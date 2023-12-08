#include <iostream>
#include <vector>

using namespace std;

int main() {
    int i,n,time,remain,temps = 0,time_quantum;
    int wt=0,tat=0;

    cout<<"Enter the total number of processes:"<<endl;
    cin>>n;

    remain=n;
    vector<int>at(n);
    vector<int>bt(n);
    vector<int>rt(n);

    cout<<"Enter the Arrival time, Burst time for all the processes:" << endl;
    for(i=0;i<n;i++) {
        cin >> at[i];
        cin >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter the value of time QUANTUM:" << endl;
    cin >> time_quantum;

    cout << "\n\nProcess\t:Turnaround Time:Waiting Time\n\n";
    // Initialize time, process index, and other variables
    for (time = 0, i = 0; remain != 0;) {
        // If the remaining time of the current process is less than or equal to the time quantum
        // and the process is not completed
        if (rt[i] <= time_quantum && rt[i] > 0) {
            // Execute the remaining time of the process
            time = time + rt[i];
            // Mark the process as completed
            rt[i] = 0;
            // Set a flag indicating that a process was executed
            temps = 1;
        } else if (rt[i] > 0) {
            // If the remaining time is more than the time quantum
            // Execute the process for the time quantum
            rt[i] = rt[i] - time_quantum;
            // Update the simulation time
            time = time + time_quantum;
        }

        // If the process has completed and was executed
        if (rt[i] == 0 && temps == 1) {
            // Update the remaining process count
            remain--;
            // Print the turnaround time and waiting time for the completed process
            std::cout << "Process{" << i+1 << "}\t:\t" << time - at[i] << "\t:\t" << time - at[i] - bt[i] << std::endl;
            cout << endl;

            // Update the total waiting time and total turnaround time
            wt = wt + time - at[i] - bt[i];
            tat = tat + time - at[i];
            // Reset the flag
            temps = 0;
        }

        // Update the process index for the next iteration
        if (i == n - 1)
            i = 0;
        else if (at[i + 1] <= time)
            i++;
        else
            i = 0;
    }
    cout << "Average waiting time " << wt * 1.0 / n << endl;
    cout << "Average turnaround time " << tat * 1.0 / n << endl;

    return 0;
}
