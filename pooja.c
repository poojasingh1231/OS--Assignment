#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t rr,pq,fcfs;
int time_quantum;
struct que_data
{
    int priority;
    int burst_time;
    int remain_time;
    int ar_time;
};

void round_robin_process();
void priority_process();
void flsm_process();

struct que_data que1[4],que2[4],que3[4];
int min_ar[3],total_burst[3],remain_total_burst[3];
int n[3];
    

void input_data(struct que_data a[],int size,int loc)
{
    int sum=0,min=10000;
    for(int i=0;i<size;i++)
    {
        printf("for process no. %d :- ",i+1);
        scanf("%d %d %d",&a[i].priority,&a[i].ar_time,&a[i].burst_time);
        a[i].remain_time=a[i].burst_time;
        sum+=a[i].burst_time;
        if(a[i].ar_time<min)
        {
            min=a[i].ar_time;
        }
    }
    total_burst[loc]=sum;
    remain_total_burst[loc]=total_burst[loc];
    min_ar[loc]=min;
    printf("%d %d",total_burst[loc],min_ar[loc]);

}

void print_data(struct que_data a[],int size)
{

for(int i=0;i<size;i++)
    {
        printf("%d %d %d\n",a[i].priority,a[i].ar_time,a[i].burst_time);
    }


}

int rtime=0,rcount;
int rremain;
void round_robin_process()
{
    
    int flag=0;
    //int wait_time=0;
    //int turnaround_time=0;
    int min=1000;
    if(rtime==0)
    for(int i=0;i<n[0];i++)
    {
        if(que1[i].ar_time<min)
        {
            min=que1[i].ar_time;
            rcount=i;
        }
    }
    

    if(rremain!=0) 
    { 
        if(que1[rcount].remain_time<=time_quantum && que1[rcount].remain_time>0) 
        { 
            remain_total_burst[0]+=time_quantum-que1[rcount].remain_time;
        
        rtime+=que1[rcount].remain_time; 
        que1[rcount].remain_time=0; 
        flag=1; 
        } 
        else if(que1[rcount].remain_time>0) 
        { 
        que1[rcount].remain_time-=time_quantum; 
        rtime+=time_quantum; 
        } 

        if(que1[rcount].remain_time==0 && flag==1) 
        { 
        rremain--; 
       // printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
        //wait_time+=time-at[count]-bt[count]; 
        //turnaround_time+=time-at[count]; 
        flag=0; 
        } 

        printf("pro%d\t\t %d \n",rcount+1,que1[rcount].remain_time);
        
        //printf("%d\n",rcount+1);

        if(rcount==n[0]-1) 
        {
            rcount=0;
            while(que1[rcount].remain_time==0)
                {
                    rcount++;

                }    

        }else if(que1[rcount+1].ar_time<=rtime) 
            {
                rcount++;
                
                while(que1[rcount].remain_time==0)
                rcount++; 
            }
            else 
            rcount=0;
        
        //printf("%d\n",rcount+1);
    } 
    //printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
    //printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
    




}

int ptime,pcount,premain;
void priority_process()
{
    //printf("in process priority\n");
    int flag=0;
    int prty=1000;
    for(int i=0;i<n[1];i++)
    {
        if(que2[i].priority<prty && que2[i].remain_time>0)
        {
            prty=que2[i].priority;
            pcount=i;
        }
    }
    if(premain!=0) 
    { 
        if(que2[pcount].remain_time<=time_quantum && que2[pcount].remain_time>0) 
        { 
            ptime+=que2[pcount].remain_time; 
            que2[pcount].remain_time=0; 
            flag=1; 
        } 
        else if(que2[pcount].remain_time>0) 
        { 
            que2[pcount].remain_time-=time_quantum; 
            ptime+=time_quantum; 
        } 

        if(que2[pcount].remain_time==0 && flag==1) 
        { 
            premain--; 
        // printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
            //wait_time+=time-at[count]-bt[count]; 
            //turnaround_time+=time-at[count]; 
            flag=0; 
        } 

        printf("pro%d\t\t %d \n",pcount+4,que2[pcount].remain_time);
        
        //printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
        //printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
        
    }
    
}

int ftime,fcount,fremain;
void flsm_process()
{
    //printf("in process flsm\n");
    int flag=0;
    for(int i=0;i<n[2];i++)
    {
        if(que3[i].remain_time>0)
        {
            fcount=i;
            break;
        }
    }
    if(fremain!=0) 
    { 
        if(que3[fcount].remain_time<=time_quantum && que3[fcount].remain_time>0) 
        { 
            ftime+=que3[fcount].remain_time; 
            que3[fcount].remain_time=0; 
            flag=1; 
        } 
        else if(que3[fcount].remain_time>0) 
        { 
            que3[fcount].remain_time-=time_quantum; 
            ftime+=time_quantum; 
        } 

        if(que3[fcount].remain_time==0 && flag==1) 
        { 
            premain--; 
        // printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
            //wait_time+=time-at[count]-bt[count]; 
            //turnaround_time+=time-at[count]; 
            flag=0; 
        } 
        printf("pro%d\t\t %d \n",fcount+7,que3[fcount].remain_time);
        
        //printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
        //printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
        
    }




}

void main_round_robin()
{
    int time=0,flag=0,count=0;
    int r_time=3;
    int wait_time=0;
    int turnaround_time=0;
    printf("\n\nque_no\t|total remaining Time\t|process no\t|process remaining time\n\n"); 

    if(min_ar[0]<=min_ar[1]&& min_ar[0]<=min_ar[2])
    {
        count=0;
    }
    else if(min_ar[1]<=min_ar[2])
    {
        count=1;
    }
    else
    count=2;

    for(time=0;r_time!=0;) 
    { 
        if(remain_total_burst[count]<=time_quantum && remain_total_burst[count]>0) 
        { 
        time+=remain_total_burst[count]; 
        remain_total_burst[count]=0; 
        flag=1; 
        } 
        else if(remain_total_burst[count]>0) 
        { 
        remain_total_burst[count]-=time_quantum; 
        time+=time_quantum; 
        } 
        if(remain_total_burst[count]==0 && flag==1) 
        { 
        r_time--; 
        //printf("\nP[%d]\t|\t%d\t|\t%d\n",count+1,time-min_ar[count],time-min_ar[count]-total_burst[count]); 
        wait_time+=time-min_ar[count]-total_burst[count]; 
        turnaround_time+=time-min_ar[count]; 
        flag=0; 
        } 

        printf("que %d\t\t %d\t\t",count+1,remain_total_burst[count]);
        
        if(count==0)
        {
            round_robin_process();
        }
        else if(count==1)
        {
            priority_process();
        }
        else
        {
            flsm_process();
        }



        if(count==2) 
        {
            count=0;
            printf("------------------------------------------------------------------------------------------------\n") ;
        }
        else if(min_ar[count+1]<=time) 
        count++; 
        else 
        count=0; 
    } 
}

int main()
{
    printf("Enter max elements for queue 1\n");
    scanf("%d",&n[0]);
    printf("Enter priority( 1(max) to 3(min)) ,arrival time and burst time\n");
    input_data(que1,n[0],0);
    rremain=n[0];

    printf("Enter max elements for queue 2\n");
    scanf("%d",&n[1]);
    printf("Enter priority( 3(max) to 6(min)) ,arrival time and burst time\n");
    input_data(que2,n[1],1);
    premain=n[1];

    printf("Enter max elements for queue 3\n");
    scanf("%d",&n[2]);
    printf("Enter priority( 6(max) to 9(min)) ,arrival time and burst time\n");
    input_data(que3,n[2],2);
    fremain=n[2];

    printf("Enter Time Quantum:\t"); 
    scanf("%d",&time_quantum);

    main_round_robin();


    //print_data(que1,n[0]);
   // print_data(que2,n[1]);
    //print_data(que3,n[2]);
    
}
