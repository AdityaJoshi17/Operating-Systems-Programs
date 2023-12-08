//Implementation fo SHORTEST JOB FIRST Using C++ in Non-premptive

#include <iostream>
#include <algorithm>
using namespace std;

int ab;

typedef struct schedule
{
	string pro_id;
	int at,bt,ct,ta,wt;

	/*
	artime = Arrival time,
	bt = Burst time,
	ct = Completion time,
	ta = Turn around time,
	wt = Waiting time
	*/

}schedule;

bool compare(schedule a,schedule b)
{
	return a.at < b.at;
	/* This process will always return TRUE
	if above condition comes*/
}

bool compare2(schedule a,schedule b)
{
	return a.bt < b.bt && a.at <= ab;
	/* This process will always return TRUE
	if above condition comes*/
}

int main()
{
	schedule pro[10];
	//An array of Processes
	int n,i,j;
	//n = number of processes, i= iteration variable

	cout<<"Enter the number of schedule::";
	cin>>n;
	cout<<"Enter the schedule id arrival time burst time :::";

	for(i=0;i<n;i++)
	{
		cin>>pro[i].pro_id;
		cin>>pro[i].at;
		cin>>pro[i].bt;
	}

	/*sort is a predefined funcion  defined in algorithm.h header file,
	it will sort the processes according to their arrival time*/

	sort(pro,pro+n,compare);

	// initial values

	pro[0].ct=pro[0].bt+pro[0].at;
	pro[0].ta=pro[0].ct-pro[0].at;
	pro[0].wt=pro[0].ta-pro[0].bt;

	for(i=1;i<n;i++)
	{
		ab=pro[i-1].ct;
		sort(pro+i,pro+n,compare2);
		if(pro[i-1].ct<pro[i].at)
		{
			pro[i].ct=pro[i-1].ct+pro[i].bt+(pro[i].at-pro[i-1].ct);
		}
		else
		{

			pro[i].ct=pro[i-1].ct+pro[i].bt;

		}
		pro[i].ta=pro[i].ct-pro[i].at;
		pro[i].wt=pro[i].ta-pro[i].bt;
	}

	for(i=0;i<n;i++)
	{
		//before executing make it in one statement
		cout<<pro[i].pro_id<<"\t"<<pro[i].at<<"\t"<<pro[i].bt<<"\t"<<pro[i].ct<<"\t"<<pro[i].ta<<"\t"<<pro[i].wt;

		cout<<endl;
	}

	return 0;
}

/*
Enter the number of schedule::5
Enter the schedule id arrival time burst time :::0 0 5
1 2 3
2 4 2
3 6 4
4 7 1
0       0       5       5       5       0
2       4       2       7       3       1
4       7       1       8       1       0
1       2       3       11      9       6
3       6       4       15      9       5

Process returned 0 (0x0)   execution time : 32.522 s
Press any key to continue.



*/
