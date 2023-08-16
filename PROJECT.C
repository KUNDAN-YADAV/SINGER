#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int main()
{
	struct singer
	{
		char name[20];
		int age;
		char sex;
		int noOfsongs;
	};

	struct singer si;
	FILE *fptr,*fptrTemp;
	char singer_name[15];
	char choice,fileName[25]="c://kundan/singer.txt";
	int dataFound=0,recordNo=0;
	fptr=fopen(fileName,"r+b");
	if(fptr==NULL)
	{
		fptr=fopen(fileName,"w+b");
		if(fptr==NULL)
		{
			printf("File can not be created!!!!!\n");
			exit(1);
		}
	}
	while(1)
	{
		printf("\n\n1.Add Record\n");
		printf("2.List Record\n");
		printf("3.Modify Record\n");
		printf("4.Search Record\n");
		printf("5.Delete a Record\n");
		printf("6.Delete all Record\n");
		printf("0.Exit\n");
		printf("Enter your choice\t");
		fflush(stdin);
		choice=getchar();
		printf("\n");
		switch(choice)
		{
			case '1':
			fseek(fptr,0,SEEK_END);
			printf("Singer's Name: ");
			fflush(stdin);
			gets(si.name);
			printf("Singer's age: ");
			scanf("%d",&si.age);
			printf("\nSex of singer: ");
			fflush(stdin);
			si.sex=getchar();
			printf("\nNumber of songs: ");
			scanf("%d",&si.noOfsongs);
			fwrite(&si,sizeof(si),1,fptr);
			break;

			case '2':
			fseek(fptr,0,SEEK_SET);
			printf("Name\tAge\tSex\tnSongs\n");
			while(fread(&si,sizeof(si),1,fptr)==1)
			{
				printf("----------------------------------\n");
				printf("%s\t%d\t%c\t%d\n",si.name,si.age,si.sex,si.noOfsongs);
			}
			printf("----------------------------------\n");
			break;

			case '3':
			printf("Enter the name of singer which is to be modified: ");
			fflush(stdin);
			gets(singer_name);
			rewind(fptr);
			dataFound=0;
			recordNo=0;
			while(fread(&si,sizeof(si),1,fptr)==1)
			{
				if(strcmp(si.name,singer_name)==0)
				{
					dataFound=1;
					printf("\nThe old record is:\n");
					printf("Name\tAge\tSex\tNo of Songs\n");
					printf("---------------------------------------\n");
					printf("%s\t%d\t%c\t%d",si.name,si.age,si.sex,si.noOfsongs);
					printf("\nEnter new name, age, sex and number of songs:\t");
					gets(si.name);
					scanf("%d",&si.age);
					fflush(stdin);
					si.sex=getchar();
					fflush(stdin);
					scanf("%d",&si.noOfsongs);
					fseek(fptr,sizeof(si)*(recordNo),SEEK_SET);
					if(fwrite(&si,sizeof(si),1,fptr)==1)
					{
						printf("\nThe record has been modified!!!\n");
						break;
					}
				}
				recordNo++;
			}
			if(dataFound==0)
				printf("Matching data not found!!!");
			break;

			case '4':
			dataFound=0;
			printf("Enter the name of singer which is to be searched: ");
			fflush(stdin);
			gets(singer_name);
			fseek(fptr,0,SEEK_SET);
			while(fread(&si,sizeof(si),1,fptr)==1)
			{
				if(strcmp(si.name,singer_name)==0)
				{
					dataFound=1;
					printf("Name\tAge\tSex\tNo of Songs\n");
					printf("-------------------------------------\n");
					printf("%s\t%d\t%c\t%d\n",si.name,si.age,si.sex,si.noOfsongs);
				}
			}
			if(dataFound==0)
				printf("NO Data found\n");
			break;

			case '5':
            dataFound=0;
			printf("\nEnter name of singer to be deleted: ");
			fflush(stdin);
			scanf("%s",singer_name);
			fptrTemp=fopen("c://kundan/temp.txt","wb");
			rewind(fptr);
			while(fread(&si,sizeof(si),1,fptr)==1)
			{
				if(strcmp(si.name,singer_name)!=0)
				{
					fwrite(&si,sizeof(si),1,fptrTemp);
					printf("\nWriting..........\n");
				}
				else
                    dataFound=1;
			}
			fclose(fptr);
			fclose(fptrTemp);
			remove(fileName);
			rename("c://kundan/temp.txt",fileName);
			fptr=fopen(fileName,"r+b");
			if(dataFound==0)
				printf("NO Data found\n");
            else
                printf("\nSuccessfully deleted......\n");
			break;

			case '6':
            fptrTemp=fopen("c://kundan/temp.txt","wb");
            fclose(fptr);
            fclose(fptrTemp);
			remove(fileName);
			rename("c://kundan/temp.txt",fileName);
			fptr=fopen(fileName,"r+b");
			printf("\nSuccessfully deleted......\n");
			break;

			case '0':
			fclose(fptr);
			printf("\nExiting...........\n");
			//getch();
			exit(1);
			break;

			default:
			printf("\n Invalid Character!!!!!");
		}
	}

}
