#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int completion_time;
    int turnaround_time;
}Process;

void sortProcess(Process p[],int n);
void print_table(Process p[],int n);
void print_gantt_chart(Process p[],int n);
void avg_TAT_WT(Process p[],int n);
float sum_waiting_time,sum_turnaround_time;

int main()
{
    Process p[MAX],m[MAX];
    int i,j,n;
    printf("Enter total no. of processes: ");
    scanf("%d",&n);
    printf("Enter arrival time of each process:\n");
    for(i=0;i<n;i++)
    {
        p[i].pid=i;
        printf("p[%d]:",i);
        scanf("%d",&p[i].arrival_time);
        p[i].waiting_time=p[i].turnaround_time=0;
    }
    printf("Enter burst time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("p[%d]:",i);
        scanf("%d",&p[i].burst_time);
    }


    printf("Enter priority of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i);
        scanf("%d",&p[i].priority);
    }
    sortProcess(p,n);
    p[0].turnaround_time=p[0].completion_time=p[0].burst_time;
    for(i=1;i<n;i++)
    {
        int c=0;
        for(j=i;j>=0;j--)
        {
            c=c+p[j].burst_time;
        }
        p[i].completion_time=c;
        p[i].waiting_time=p[i-1].completion_time-p[i].arrival_time;
        p[i].turnaround_time=p[i].waiting_time+p[i].burst_time;
    }



    //print table
    printf("\n");
    print_table(p,n);
    printf("\n");
    //print gantt chart
    printf("        GANTT CHART\n");
    printf("        ___________\n");
    print_gantt_chart(p,n);
    avg_TAT_WT(p,n);
    return 0;
}

void print_table(Process p[],int n)
{
    int i;
    printf("+-----+----------------+----------------+---------------+----------------------+---------------+\n");
    printf("|PID  |Arrival Time    |Burst Time      |Waiting Time   |Turnaround Time       |Priority       |\n");
    printf("+-----+----------------+----------------+---------------+----------------------+---------------+\n");
    for(i=0;i<n;i++)
    {
        printf("| %2d  |  %2d            |  %2d            |   %2d          |   %2d                 |   %2d          |\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turnaround_time,p[i].priority);
        printf("+-----+----------------+----------------+---------------+----------------------+---------------+\n");
    }
}

void print_gantt_chart(Process p[],int n)
{
    int i,j;
    //print top bar
    printf(" ");
    for(i=0;i<n;i++)
    {
        for(j=0;j<p[i].burst_time;j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    //printing process id
    for(i=0;i<n;i++)
    {
        for(j=0;j<p[i].burst_time-1;j++)
            printf(" ");
        printf("P%d",p[i].pid);
        for(j=0;j<p[i].burst_time-1;j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    //printing bottom bar
    for(i=0;i<n;i++)
    {
        for(j=0;j<p[i].burst_time;j++)
            printf("--");
        printf(" ");
    }
    printf("\n");
    //printing the time line
    printf("0");
    for(i=0;i<n;i++)
    {
        for(j=0;j<p[i].burst_time;j++)
            printf("  ");
        printf("%d",p[i].completion_time);
    }
    printf("\n");
}

void avg_TAT_WT(Process p[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        sum_waiting_time+=p[i].waiting_time;
        sum_turnaround_time+=p[i].turnaround_time;
    }
    printf("Total Waiting Time: %.2f\n",sum_waiting_time);
    printf("Average Waiting Time: %.2f\n",(sum_waiting_time/n));
    printf("Total Turnaround Time: %.2f\n",sum_turnaround_time);
    printf("Average Turnaround Time: %.2f\n",(sum_turnaround_time/n));
}

void sortProcess(Process p[],int n)
{
    int i,j,pos,temp;
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(p[j].priority<p[pos].priority)
                pos=j;
        }

        temp=p[i].priority;
        p[i].priority=p[pos].priority;
        p[pos].priority=temp;

        temp=p[i].burst_time;
        p[i].burst_time=p[pos].burst_time;
        p[pos].burst_time=temp;

        temp=p[i].pid;
        p[i].pid=p[pos].pid;
        p[pos].pid=temp;

        temp=p[i].arrival_time;
        p[i].arrival_time=p[pos].arrival_time;
        p[pos].arrival_time=temp;
    }
}

