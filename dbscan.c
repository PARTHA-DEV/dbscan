#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NOISE 0
int no_points;
int no_attr;
int **arr;
int k=0;
int nb_count=0;
int *neighbour,*visited,*cluster;
int distance(int p,int k){
	int i,temp=0;
	for(i=0;i<no_attr;i++){
		temp+=pow((arr[p][i]-arr[k][i]),2);
	}
	temp=pow(temp,0.5);
	return temp;
}
void findNeighbour(int point){
	int i,j,dist,count=0;
	for(i=0;i<no_points;i++){
		if(i!=point){
			dist=distance(point,i);
			printf("Distance : %d\n",dist);
		if(dist<=100){
			neighbour[nb_count++]=i;
		}
	}
  }
}
void dbScan(){
	int cluster_id=1;
	int i,j,k;
	for(i=0;i<no_points;i++){
		nb_count=0;
		if(visited[i]!=1){
			printf("visited[%d]: %d\n",i,visited[i]);
			visited[i]=1;
			printf("visited[%d]: %d\n",i,visited[i]);
			findNeighbour(i);
/*
			printf("\nNeighbour of %d: ",i);
			for(j=0;j<nb_count;j++)
				printf("%d ",neighbour[j]);
*/
		if(nb_count>3){
			expandCluster(cluster_id,i);
			cluster_id++;		
		}
					
		}	
		
	}
}
void expandCluster(int cluster_id,int point){
	int i,count=nb_count,current;
	cluster[point]=cluster_id;
	for(i=0;i<nb_count;i++){
		current=neighbour[i];
		if(visited[current]==0){
			visited[current]=1;
			findNeighbour(current);
			if((nb_count-count)<3){
				nb_count=count;
			}
		}
		if(cluster[current]==0){
			cluster[current]=cluster_id;
		}
	}
}
int main(int argc,char *argv[]){
	int i,j,k;	
	FILE *fp;
	fp=fopen(argv[1],"r");
	//printf("Enter number of points: ");
	fscanf(fp,"%d",&no_points);
	//printf("Enter number of attributes: ");
	fscanf(fp,"%d",&no_attr);
	arr=(int **)malloc(no_points*sizeof(int*));
	neighbour=(int*)malloc(no_points*no_attr*sizeof(int));
	visited=(int*)malloc(no_points*sizeof(int));
	cluster=(int *)malloc(no_points*sizeof(int));
	for(i=0;i<no_points;i++){
		arr[i]=(int *)malloc(no_attr*sizeof(int));
		visited[i]=0;
		cluster[i]=0;
	}
	for(i=0;i<no_points;i++)
		for(j=0;j<no_attr;j++)
			fscanf(fp,"%d",&arr[i][j]);
	for(i=0;i<no_points;i++){
		for(j=0;j<no_attr;j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
	dbScan();
	for(i=0;i<no_points;i++){
		printf("Point %d : %d\n",i,cluster[i]);
	}
	fclose(fp);
	return 0;
}
