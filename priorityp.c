#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
int n,tn;
struct process{
	int id,arr,burst,turn,wait,start,finish,priority;
}pro[100],t[100],final[100];

void idsort(){
	int i,j;
	struct process temp;
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(pro[j+1].id<pro[j].id){
				temp=pro[j];
				pro[j]=pro[j+1];
				pro[j+1]=temp;
			}
		}
	}
}

void fcfssort(){
	int i,j;
	struct process temp;
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(pro[j+1].arr<pro[j].arr){
				temp=pro[j];
				pro[j]=pro[j+1];
				pro[j+1]=temp;
			}
		}
	}
}

void copy(){
	int i;
	fcfssort();
	for(i=0;i<n;i++)
		t[i]=pro[i];
	tn=n;
}


void delete(int pos){
	int i;
	for(i=pos;i<n-1;i++)
		t[i]=t[i+1];	
	tn--;
}

int main(){
	int i,ch,j,total_wait=0,total_turn=0,minimum=0,finish_so_far=0,pos=0,k,total_time,current,times,wait_time;
	struct process temp;
	float avg_wait=0.0,avg_turn=0.0;
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Enter details for process %d\n",i+1);
		printf("Process ID : ");	
		scanf("%d",&pro[i].id);
		printf("Arrival Time : ");
		scanf("%d",&pro[i].arr);
		printf("Burst time : ");
		scanf("%d",&pro[i].burst);
		printf("Priority : ");
		scanf("%d",&pro[i].priority);
		printf("\n");
		pro[i].start=0;
		pro[i].finish=0;
		pro[i].wait=0;
		pro[i].turn=0;
	}
	ch=3;
		total_wait=0;total_turn=0;
		fcfssort();
		pro[0].wait=0;
		pro[0].turn=pro[0].burst;
		pro[0].start=pro[0].arr;
		pro[0].finish=pro[0].start+pro[0].burst;
		copy();
		for(i=0;i<n;i++){
			total_time=total_time+pro[i].burst;
		}
		minimum=99;
		for(i=0;i<total_time;i++){
				minimum=t[0].priority;
				pos=0;
				for(k=1;k<tn;k++){
					if((t[k].priority < minimum)&& (t[k].burst > 0) && (t[k].arr <= i)){
						minimum=t[k].priority;
						pos=k;
					}
				}
				final[i]=t[pos];
				t[pos].burst--;
				if(t[pos].burst==0) delete(pos);
		}
		for(i=0;i<total_time;i++){
			printf("---");
		}
		printf("\n");
		for(i=0;i<total_time;i++){
			printf("P%d|",final[i].id);
		}
		printf("\n");
		for(i=0;i<total_time;i++){
			printf("---");
		}
		for(i=0;i<n;i++){
			current=pro[i].id;
			times=0;
			wait_time=0;
			for(j=0;j<total_time;j++){
				if(final[j].id==current){
					if(times==0){
						wait_time=j-pro[i].arr;
					}
					else{
						for(k=j-1;k>=0;k--){
							if(final[k].id==final[j].id){
								wait_time=wait_time+j-k-1;
								break;
							}
						}
					}
					times++;
				}
			}
			pro[i].wait=wait_time;
			pro[i].turn=pro[i].wait+pro[i].burst;
		}
		printf("\n");
		for(i=0;i<n;i++){
			total_wait=total_wait+pro[i].wait;
			total_turn=total_turn+pro[i].turn;
		}
		float a,b;
		a=total_wait;
		b=total_turn;
		avg_wait=a/n;
		avg_turn=b/n;
		printf("\nTURNOVER,WAITING AND AVERAGE TIME\n");
		printf("ID\tARRIVAL\tBURST\tTURNAROUND WAITING\n");
		for(i=0;i<n;i++){
			printf("%d\t%d\t%d\t%d\t   %d\n",pro[i].id,pro[i].arr,pro[i].burst,pro[i].turn,pro[i].wait);
		}
		printf("AVERAGE \t\t%.2f\t %.2f\n",avg_wait,avg_turn);
		return 0;
}

