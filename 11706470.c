#include<stdio.h>
struct proc
{
        int id,arrivaltime,bursttime,rem,waitingtime,completiontime,turnaroundtime;
}process[10]; //structure to hold the process information
struct proc temp;
int no;
int check(int);
int next();
 void srot(int);

int main()

{
          int n;
        printf("\n \n ---SHORTEST REMAINING TIME FIRST---\n \n ");
        printf("\n \n Enter the number of processes: ");
        scanf("%d", &n);
        srot(n);


}//end of main()
int check(int s) // function to check process remaining time is zero or not
{
        int i;
        for(i = 1; i <= s; i++)
        {
                if(process[i].rem != 0)
                        return 1;
        }
        return 0;
} // end of check

int next() // function to identify the next process to be executed

{
        int min, l, i;
        min = 10000; //any limit assumed
        for(i = 1; i <= no; i++)
        {
                if( process[i].rem!=0 && process[i].rem < min)
                {
                        min = process[i].rem;
                        l = i;
                }
        }
        return l;
} // end of next

void srot(int n)

{
int i,j,k,time=0;
float ttavg,wtavg;
for(i = 1; i <= n; i++)
        {
                process[i].id = i;
                printf("\n\nEnter the arrival time for process %d: ", i);
                scanf("%d", &(process[i].arrivaltime));
                printf("Enter the burst time for process %d: ", i);
                scanf("%d", &(process[i].bursttime));
                process[i].rem = process[i].bursttime;
         }
        for(i = 1; i <= n; i++)
        {
                for(j = i + 1; j <= n; j++)
                {
                        if(process[i].arrivaltime > process[j].arrivaltime) // sort arrival time of a process
                        {
                                temp = process[i];
                                process[i] = process[j];
                                process[j] = temp;
                        }
                }
        }
        no = 0;
        j = 1;
       while(check(n) == 1)
        {
                if(process[no + 1].arrivaltime == time)//to calculate the arrival time
                {
                        no++;
                        if(process[j].rem==0)
                         process[j].completiontime=time;
                        j = next();
                }
                if(process[j].rem != 0) // to calculate the waiting time of a process
                {
                        process[j].rem--;
                        for(i = 1; i <= no; i++)
                        {
                                if(i != j && process[i].rem != 0)
                                        process[i].waitingtime++;
                        }
                }
                     else
                {

                        process[j].completiontime = time;
                        j=next();
                        time--;
                        k=j;
                }

                time++;
        }
        process[k].completiontime = time;
        printf("\n\n\t\t\t---SHORTEST REMAINING TIME FIRST---");
        printf("\n\n Process Arrival   Burst  Waiting  Finishing  turnaround   \n");
        printf("%5s %9s %7s %10s %8s\n\n", "id", "time", "time", "time", "time");
        for(i = 1; i <= n; i++)
        {
                     process[i].turnaroundtime = process[i].waitingtime + process[i].bursttime; // calc of turnaround
                     printf("%5d %8d %7d %8d %10d %9d ", process[i].id, process[i].arrivaltime,
                     process[i].bursttime, process[i].waitingtime, process[i].completiontime, process[i].turnaroundtime);
         	  ttavg=ttavg+ process[i].turnaroundtime; //sum of turnaround time
         	  wtavg=wtavg+process[i].waitingtime; // sum of waiting time
                    printf("\n\n");
        }
        ttavg=ttavg/n; // average turnaround time
        wtavg=wtavg/n; // average wait time
            printf("average turnaround time=%f\t\t average waiting time=%f\n",ttavg,wtavg);
}// end of srot

