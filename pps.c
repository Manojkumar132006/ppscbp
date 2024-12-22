#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char r='y';
    char audi[5][5]={"ks","apjd","apjb"};
    int cap[5]={600,150,200};
    char avail[5][5];
    char arr[5][5];
    while(r=='y'){
        printf("Required Seats: \n>>>");
        scanf("%s",&arr[0]);
        for(int i=0;i<5;i++){
            if(cap[i]<=atoi(arr[0])){
                strcpy(avail[sizeof(avail)/sizeof(avail[0])],audi[i]);
            }
        }
        m:printf("Available Auditoriums: \n");
        for(int i=0;i<sizeof(avail)/sizeof(avail[0]);i++){
            if(avail[i]!=""){
                printf("%d. %s\n",i,avail[i]);
            }
        }
        printf("Select Auditorium: \n>>>");
        scanf("%s",&arr[1]);
        if(arr[2]||arr[3]){
            goto n;
        }
        else{
            input(&arr);
        }
        int f=0;
        n:search(arr[1],arr,&avail,&f);
        if(f==1){
            printf("Enter your Contact No: \n>>>");
            scanf("%s",&arr[5]);
            FILE fp = openfile(arr[4],arr[1],"a");
            char line[]="";
            strcat(line,arr[2]);
            strcat(line,",");
            strcat(line,arr[3]);
            strcat(line,",");
            strcat(line,arr[5]);
            strcat(line,"\n");
            fputs(line,&fp);
            printf("\nYour booking is successful.\n\n");
            printf("Do you want to continue booking?(y/n)\n>>>");
            scanf("%c",&r);
        }
        else{
            printf("Selected Auditorium is not available.\n\n");
            printf("Do you want to continue booking?(y/n)\n>>>");
            scanf("%c",&r);
            goto m;
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
    char date[8]=day;
    strcat(date,"/");
    strcat(date,month);
    strcat(date,"/");
    strcat(date,year);
    *arr[4]=date;
    *arr[2]=starttime;
    *arr[3]=endtime;
}
FILE openfile(char date,char audi[5],char mode){
    char filename[12]=".\\";
    strcat(filename,audi);
    strcat(filename,"\\");
    strcat(filename,date);
    strcat(filename,".csv");
    FILE *fp=fopen(filename,mode);
    return *fp;
}
void search(char audi[5],char arr[5][5],char*avail[5][5],int*f){
    for(int i=0;i<5;i++){
        FILE fp = openfile(arr[4],avail[i],"r");
        if(&fp==NULL&&(strcmp(*avail[i],audi)==0)){
            *f=1;
            break;
        }
        int j,ret;
        char ch;
        char data[sizeof(fp)];
        char sdata[20][20];
        if(strcmp(*avail[i],"")!=0){
            while(fgets(data,1,&fp)){
                char *token = strtok(data,",");
                j=0;
                while(token!=NULL){
                    strcpy(sdata[i],token);
                    token = strtok(NULL,",");
                    j++;
                }
                if(!(arr[2]>=sdata[0]||arr[3]<=sdata[1])){
                    strcpy(*avail[i],"");
                    break;
                }
            }
        }
    }
}
