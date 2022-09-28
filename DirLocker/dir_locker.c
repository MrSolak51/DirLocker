#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void lock(char password[],char parameter_path[]){
  char cmd[]="Cacls ",cmd1[]=" /E /P everyone:n", in_file[500], pass[100], path[100];
  strcpy(pass,password);
  strcpy(path,parameter_path);
  strcat(cmd,path);
  strcat(cmd,cmd1);
  system(cmd);
  strcat(in_file,path);

  strcat(in_file," ");

  strcat(in_file,pass);
  
  FILE *file=fopen("file.txt","a");
  fprintf(file,"%s\n",in_file);
  fclose(file);
}

void unlock(char password[],char parameter_path[]){

  char cmd[]="Cacls ",cmd1[]=" /E /P everyone:f", out_file[100], pass[100], main_pass[100],main_path[100],path[100];
  strcpy(pass,password);
  strcpy(path,parameter_path);

  FILE *file=fopen("file.txt","r");
  
  if(file==NULL){
    printf("something went wrong\n");
  }
  else{
    int indis, indis1=0, indis2=0, indis3=0;
    int space=0;
    
    while(fgets(out_file,100,file)!=NULL){
      memset(main_path, 0, sizeof(main_path));
      memset(main_pass, 0, sizeof(main_pass));
      for(indis=0;indis<strlen(out_file);indis++){
        if(out_file[indis]!=' ' && space==0 && out_file[indis]!='\n'){
          main_path[indis1]=out_file[indis];
          indis1++;
        }
        else if(out_file[indis]!=' ' && out_file[indis]!='\n' && space==1){
          main_pass[indis2]=out_file[indis];
          indis2++;
        } 
        else
          space=1;
      }
      indis1=0;indis2=0;space=0;
      if(strcmp(path,main_path)==0){
        printf("path is avabile\n");
        if(strcmp(pass,main_pass)==0){
          printf("password is corrected\n");
  	   	strcat(cmd,main_path);
 		strcat(cmd,cmd1);
          system(cmd);
          break;
        }
        else{
          printf("password is incorrected\n");
          break;
        }
      }
      else{
         printf("path is unavabile\n");
      }
    }
  }
  fclose(file);
}


int main(){
  system("cls&&color 4");
  int choose;
  char path[100],password[100];
  printf("1)Lock File\n2)Unlock File\n3)Exit\nEnter your choose : ");
  scanf("%d", &choose);
  while(choose!=3){
    
    if(choose == 1){
      printf("enter path : ");
      scanf("%s",&path);
      printf("create a password : ");
      scanf("%s",&password);
      lock(password,path);
    }
    else if(choose==2){
      printf("enter path : ");
      scanf("%s",&path);
      printf("enter password : ");
      scanf("%s",&password);
      unlock(password,path);
    }
    else if(choose==3){
      break;
    }
    else{printf("incorrected....\n");
    }
    printf("1)Lock File\n2)Unlock File\n3)Exit\nEnter your choose : ");
    scanf("%d", &choose);
  }

  system("pause");
  return 0;
}
