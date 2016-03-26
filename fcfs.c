#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
int n;
struct process{
	int id,arr,burst,turn,wait,start,finish;
}pro[100];

void idsort(int n){
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

void fcfssort(int n){
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

int main(){
	int i,ch,j,total_wait=0,total_turn=0,maximum=0,finish_so_far=0,pos=0,total_time=0;
	struct process temp;
	float avg_wait,avg_turn;
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
		printf("\n");
		pro[i].start=0;
		pro[i].finish=0;
		pro[i].wait=0;
		pro[i].turn=0;
	}
	printf("1.First come first serve scheduling\n");
	ch=1;
	if(ch==1){
		fcfssort(n);
		for(i=0;i<n;i++){
			if(i==0){
				pro[i].wait=0;
				pro[i].turn=pro[i].burst;
				pro[i].start=pro[i].arr;
				pro[i].finish=pro[i].start+pro[i].burst;
			}
			else{
				pro[i].wait=pro[i-1].finish-pro[i].arr;
				pro[i].turn=pro[i].wait+pro[i].burst;
				pro[i].start=pro[i-1].finish;
				pro[i].finish=pro[i].start+pro[i].burst;
			}
		}
		printf("GANTT CHART\n");
		for(i=0;i<n;i++){
			for(j=0;j<pro[i].finish-pro[i].start;j++){
				printf("----");
			}
		}
		printf("\n");
		for(i=0;i<n;i++){
			for(j=0;j<pro[i].finish-pro[i].start;j++){
				printf("P%d|",pro[i].id);
			}
		}
		printf("\n");
		for(i=0;i<n;i++){
			for(j=0;j<pro[i].finish-pro[i].start;j++){
				printf("----");
			}
		}
			//printf("Process %d starts at %d and ends at %d\n",pro[i].id,pro[i].start,pro[i].finish);
		//printf("\n");
		idsort(n);
		printf("\nTURNOVER,WAITING AND AVERAGE TIME\n");
		printf("ID\tARRIVAL\tBURST\tTURNAROUND WAITING\n");
		for(i=0;i<n;i++){
			printf("%d\t%d\t%d\t%d\t   %d\n",pro[i].id,pro[i].arr,pro[i].burst,pro[i].turn,pro[i].wait);
			total_wait+=pro[i].wait;
			total_turn+=pro[i].turn;
		}
		avg_wait=total_wait/n;
		avg_turn=total_turn/n;
		printf("AVERAGE \t\t%.2f\t   %.2f\n",avg_turn,avg_wait);
	}
	return 0;
}
