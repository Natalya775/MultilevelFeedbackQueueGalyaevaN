#include<stdio.h>
#include<vector>
#include <iostream>
#include "structures.h" 
using namespace std;

struct process
{
	int name;
	int AT, BT, WT, TAT, RT, CT;
};
vector <process> Q1;
vector <process> Q2;
vector <process> Q3;

//int n;
//void sortByArrival()
//{
//	struct process temp;
//	int i, j;
//	for (i = 0; i < n; i++)
//	{
//		for (j = i + 1; j < n; j++)
//		{
//			if (Q1[i].AT > Q1[j].AT)
//			{
//				temp = Q1[i];
//				Q1[i] = Q1[j];
//				Q1[j] = temp;
//			}
//		}
//	}
//}

template <typename T>
void sortByArrival(vector <T>& processes, const int& n)
{
	Q1.resize(n);
	for (int i = 0; i < n; i++)
	{
		Q1[i].AT = processes[i].arriving_time;
		Q1[i].name = processes[i].Pid;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{

			if (Q1[i].AT < Q1[j].AT)
			{
				int Na, A;
				Na = Q1[i].name;
				Q1[i].name = Q1[j].name;
				Q1[j].name = Na;

				A = Q1[i].AT;
				Q1[i].AT = Q1[j].AT;
				Q1[j].AT = A;

			}
		}
	}
//	for (int i = 0; i < 5; i++)
//	{
//		cout << num[i] << "\t";
//	}
}

template <typename T>
void MLFQ(vector <T>& processes)
{
	int i, j, k = 0, r = 0, time = 0, tq1 = 5, tq2 = 8, flag = 0;
	int c;
	const int n = processes.size();
	int total_wt = 0, total_tat = 0;
	Q1.resize(n);
	Q2.resize(n);
	Q3.resize(n);
	for (i = 0, c = 1; i < n; i++, c++)
	{
		Q1[i].name = processes[i].Pid;
		Q1[i].BT = processes[i].burst_time;;
		Q1[i].AT = processes[i].arriving_time;
		Q1[i].RT = Q1[i].BT;/*save burst time in remaining time for each process*/
	}
	sortByArrival(processes, n);
	time = Q1[0].AT;
	cout << "Multilevel Feedback Queue: " << "\n";
	//printf("Process in first queue following RR with qt=5");
	//printf("\nProcess\t\tTAT\t\t");
	for (i = 0; i < n; i++)
	{

		if (Q1[i].RT <= tq1)
		{

			time += Q1[i].RT;/*from arrival time of first process to completion of this process*/
			Q1[i].RT = 0;
			Q1[i].WT = time - Q1[i].AT - Q1[i].BT;/*amount of time process has been waiting in the first queue*/
			Q1[i].TAT = time - Q1[i].AT;/*amount of time to execute the process*/
			total_wt = total_wt + Q1[i].WT;
			total_tat = total_tat + Q1[i].TAT;
		}
		else/*process moves to queue 2 with qt=8*/
		{
			Q2[k].WT = time;
			time += tq1;
			Q1[i].RT -= tq1;
			Q2[k].BT = Q1[i].RT;
			Q2[k].RT = Q2[k].BT;
			Q2[k].name = Q1[i].name;
			k = k + 1;
			flag = 1;
			//printf("\n%d\t\t%d\t\t", Q1[i].name, Q1[i].TAT);
			cout << Q1[i].name << "\t";
			//cout << Q1[i].TAT << " " << "\n";
		}
	}
	if (flag == 1)
	{
		//printf("\nProcess in second queue following RR with qt=8");
		//printf("\nProcess\t\tTAT\t\t");
	//}
	for (i = 0; i < k; i++)
	{
		if (Q2[i].RT <= tq2)
		{
			time += Q2[i].RT;/*from arrival time of first process +BT of this process*/
			Q2[i].RT = 0;
			Q2[i].WT = time - tq1 - Q2[i].BT;/*amount of time process has been waiting in the ready queue*/
			Q2[i].TAT = time - Q2[i].AT;/*amount of time to execute the process*/
			total_wt = total_wt + Q2[i].WT;
			total_tat = total_tat + Q2[i].TAT;
			cout << Q2[i].name << "\t";
			//printf("\n%d\t\t%d\t\t", Q2[i].name, Q2[i].TAT);
			//printf("\n%d\t\t%d\t\t%d\t\t%d", Q2[i].name, Q2[i].BT, Q2[i].WT, Q2[i].TAT);
		}
		else/*process moves to queue 3 with FCFS*/
		{
			Q3[r].AT = time;
			time += tq2;
			Q2[i].RT -= tq2;
			Q3[r].BT = Q2[i].RT;
			Q3[r].RT = Q3[r].BT;
			Q3[r].name = Q2[i].name;
			r = r + 1;
			flag = 2;
		}
	}
	}
	{
		if (flag == 2)
		//printf("\nProcess in third queue following FCFS ");
		//printf("\nProcess\t\tTAT\t\t");
	//}
	for (i = 0; i < r; i++)
	{
		if (i == 0)
			Q3[i].CT = Q3[i].BT + time - tq1 - tq2;
		else
			Q3[i].CT = Q3[i - 1].CT + Q3[i].BT;
	}
	for (i = 0; i < r; i++)
	{
		Q3[i].TAT = Q3[i].CT;
		Q3[i].WT = Q3[i].TAT - Q3[i].BT;
		total_wt = total_wt + Q3[i].WT;
		total_tat = total_tat + Q3[i].TAT;
		cout << Q3[i].name << "\t";
		//printf("\n%d\t\t%d\t\t", Q3[i].name, Q3[i].TAT);
	}
	}
	a = (double)total_wt / (double)n;
	a = round(a * 100.0) / 100.0;
	b = (double)total_tat / (double)n;
	b = round(b * 100.0) / 100.0;
	cout << fixed;
	cout.precision(2);
	cout << endl << "Average waiting time = "
		<< (a);

	cout << "\nAverage turn around time = "

		<< (b);
	cout << endl;
}

