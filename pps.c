#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char r='y';
    char audi[5][5]={"ks","apjd"};
    int capacities[5]={600,150};
    int available[5];
    char arr[10][10];
    while(r=='y'){
        printf("Required Seats: ");
        scanf("%d",&arr[4]);
        for(int i=0;i<5;i++){
            if(capacities[i]<=arr){
                available[sizeof(available)/sizeof(available[0])]=audi[i];
            }
        }
        input(arr);
        char filename="";
        strcat(filename,arr[0]);
        strcat(filename,".csv");
        FILE *fp = fopen(filename,"r");
        if(fp==NULL){//checking if the file exists
            FILE *fpn = fopen(filename,"a");
            fprintf(fpn,"%s,%d,%d,%d\n",arr[0],arr[1],arr[2]);
            fcloseall();
        }else{
            if(checkavail(arr[0],arr[1],arr[2],arr[3],fp)==0){
                printf("\nAn event already exists in the calendar.");
                printf("\nDo you want to continue booking?(y/n): ");
                scanf("%c",&r);
            }
            else{
                char line[]="";
                strcat(line,arr[0]);
                strcat(line,",");
                strcat(line,arr[1]);
                strcat(line,",");
                strcat(line,arr[2]);
                strcat(line,"\n");
                fputs(line,fp);
            }
        }
    }
}
void input(char *arr[10][10]){
    char day[2],month[2],year[4],starttime[5],endtime[5];
    int starttime,endtime,a,lines,i;
    //taking inputs for setting time slot
    printf("Enter Day: ");
    scanf("%s",day);
    printf("\nEnter Month: ");
    scanf("%s",month);
    printf("\nEnter year: ");
    scanf("%s",year);
    printf("\nEnter your start time in hhmm format: ");
    scanf("%s",&starttime);
    printf("\nEnter your end time in hhmm format: ");
    scanf("%s",&endtime);
    //defining date variable to check for file names with it.
    char filename[12]=day,date[8];
    strcat(filename,"/");
    strcat(filename,month);
    strcat(filename,"/");
    strcat(filename,year);
    strcpy(date,filename);
    *arr[0]=date;
    *arr[1]=starttime;
    *arr[2]=endtime;
    *arr[3]=itoa(a);
}
FILE openfile(char date,char audi[5],char mode){
    char filename[12]=audi;
    strcat(filename,"\\");
    strcat(filename,date);
    strcat(filename,".csv");
    FILE *fp=fopen(filename,mode);
    return *fp;
}
int checkavail(char date,int starttime,int endtime,int audi,FILE *fp){
    int i,ret;
    char ch;
    char data[sizeof(*fp)];
    char sdata[20][20];
    while(fgets(data,1,fp)){
        char *token = strtok(data,",");
        i=0;
        while(token!=NULL){
            strcpy(sdata[i],token);
            token = strtok(NULL,",");
            i++;
        }
        if((strcmp(sdata[0],date)&&(!(starttime>=sdata[2]||endtime<=sdata[1]) && (int)sdata[3]==audi))){
            ret = 0;
            break;
        }
        else{
            ret=1;
        }
    }
    return ret;
}