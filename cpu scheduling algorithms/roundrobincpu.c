#include<stdio.h>
#include<stdlib.h>
#define MAX 10
struct times
{
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

void sort_arrival(struct times p[],int n);
//void print_gantt_chart(int p[], int n);
float avg_waiting_time=0,avg_turnaround_time=0;
//int c=0,ts;
//int m[50],t[50];

void main()
{
    int i,j,n,time,remain,flag=0,ts;
    struct times p[MAX];
    printf("Enter number of process: ");
    scanf("%d",&n);
    remain=n;
    printf("Enter arrival time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i);
        scanf("%d",&p[i].arrival_time);
        p[i].pid=i;
    }
    printf("Enter burst time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i);
        scanf("%d",&p[i].burst_time);
        p[i].remaining_time=p[i].burst_time;
    }

    sort_arrival(p,n);

    printf("Enter time slice:");
    scanf("%d",&ts);

    printf("\t\tGantt Chart\n");
    printf("\t\t___________\n\n");
    printf("|0|");
    for(time=0,i=0;remain!=0;)
    {
        if(p[i].remaining_time<=ts && p[i].remaining_time>0)
        {
            time=time + p[i].remaining_time;
            printf("-----P[%d]-----|%d|",p[i].pid,time);
            p[i].remaining_time=0;
            flag=1;
        }
        else if(p[i].remaining_time > 0)
        {
            p[i].remaining_time=p[i].remaining_time - ts;
            time=time+ts;
            printf("-----P[%d]-----|%d|",p[i].pid,time);
        }
        if(p[i].remaining_time==0 && flag==1)
        {
            remain--;
            p[i].turnaround_time=time-p[i].arrival_time;
            p[i].waiting_time=time-p[i].arrival_time-p[i].burst_time;
            avg_waiting_time=avg_waiting_time + time - p[i].arrival_time - p[i].burst_time;
            avg_turnaround_time=avg_turnaround_time + time - p[i].arrival_time;
            flag=0;
        }
        if(i==n-1)
            i=0;
        else if(p[i+1].arrival_time <= time)
            i++;
        else
            i=0;
    }




    printf("\n\n");
    printf("+-----+----------------+----------------+---------------+----------------------+\n");
    printf("|PID  |Arrival Time    |Burst Time      |Waiting Time   |Turnaround Time       |\n");
    printf("+-----+----------------+----------------+---------------+----------------------+\n");
    for(i=0;i<n;i++)
    {
        printf("| %d   |  %d             |  %d             |   %d           |   %d                  |\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turnaround_time);
        printf("+-----+----------------+----------------+---------------+----------------------+\n");
    }

    avg_waiting_time=avg_waiting_time/n;
    avg_turnaround_time=avg_turnaround_time/n;
    printf("Average Waiting Time: %.2f\n",avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n",avg_turnaround_time);

}

void sort_arrival(struct times p[],int n)
{
    int i,j;
    struct times temp;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].arrival_time > p[j].arrival_time)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    return;
}

