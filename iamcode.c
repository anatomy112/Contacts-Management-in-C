#include<stdio.h> 
#include<conio.h> 
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>


struct contact
{
	long ph;
	char name[20],add[20],email[30];
} list;

char query[20],name[20];
FILE *fp, *ft;

int i,n,ch,l,found;

int main()
{
	main:
	printf("\n\t **** Welcome to CONTACT MANAGER ***");
	printf("\n\n\n\t\t\t MAIN MENU\n\t\t================\n\t\t[1] Add a new Contact \n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact \n\t\t[0] Exit\n\t\t=============\n\t\t");
	printf("Enter a Choice:");
	scanf("%d",&ch);


	switch(ch)
	{
		case 0:
		printf("\n\n\t Are you sure want to exit?");
		break;

		/* *********** ADD NEW CONTACT *********** */
		case 1:

		system("cls");
		fp=fopen("contact.dll","a");
		for(;;) {
			fflush(stdin);
			printf("To exit, enter blank space in the name input\n Name (Use identical) : ");
			scanf("%[^\n],&list.name");
			if(strcmp(list.name,"")==0 || strcmp(list.name," ")==0)
				break;
			fflush(stdin);
			printf("Phone");
			scanf("%ld",&list.ph);
			fflush(stdin);
			printf("Address:");
			scanf("%[^\n]",&list.add);
			fflush(stdin);
			printf("email address:");
			gets(list.email);
			printf("\n");
			fwrite(&list,sizeof(list),1,fp);
		}
		fclose(fp);
		break;


		/* *********** LIST OF CONTACTS ******** */ 

		case 2:
		system("cls");
		printf("\n\t\t ==================\n\t\t\tLIST OF CONTACTS\n\t\t==================\n\nName\t\tPhone No\t Address\t\t E-mail ad. \n ================================\n\n");

		for(i=97;i<=122;i=i+1){
			fp=fopen("contact.dll","r");
			fflush(stdin);
			found=0;
			while(fread(&list,sizeof(list),1,fp)==1)
			{
				if(list.name[0]==i || list.name[0]==i-32)
				{
					printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nEmail\t: %s\n", list.name, list.ph,list.add,list.email);
					found++;

				}
			}
			if(found!=0)
			{
				printf("============================ [%c}-(%d)\n\n",i-32,found);
				getch();

			}
			fclose(fp);
		}
		break;


		/* ******************** SEARCH CONTACTS ************* */ 
		case 3:
		system("cls"); 
		do{
			found=0;
			printf("\n\n\t..::CONTACT SEARCH\n\t===============\n\t..::Name of Contact to search: ");
			fflush(stdin);
			scanf("%[^\n]",&query);
			l=strlen(query);
			fp=fopen("contact.dll","r");

			system("cls");
			printf("\n\n..::Search results for '%s' \n=========================\n",query);
			while(fread(&list,sizeof(list),1,fp)==1)
			{
				for(i=0;i<=1;i++)
					name[i]=list.name[i];
				name[1]='\0';
				if(strcmp(name,query)==0)
				{
					printf("\n..::Name\t: %s\n..::Phone\t: %ld\n..::Address\t: %s\n..::Email\t:%s\n",list.name,list.ph,list.add,list.email);
					found++
					if(found%4==0)
					{
						printf("..::Press any key to continue...");
						getch();

					}
				}

			}
			if(found==0)
				printf("\n..:: No match found!");
			else
				printf("\n..::%d match(s) found!",found);
			fclose(fp);
			printf("\n..::Try again?\n\n\t[1] YES\t\t[0] NO\n\t");
			scanf("%d",&ch);
		}
		while(ch==1)
			break;



		/* ***************** EDIT CONTACTS ************* */ 

		case 4:
		system("cls");
		fp=fopen("contact.dll","r");
		ft=fopen("temp.dat","w");
		fflush(stdin);
		printf("..::Edit Contact\n==============\n\n\t..:Enter the name of contact to edit: ");
		scanf("%[^\n]",name);
		while(fread(&list,sizeof(list),1,fp)==1){
			if(strcmp(name,list.name)!=0)
				fwrite(&list,sizeof(list),1,ft);

		}
		fflush(stdin);
		printf("\n\n..::Editing '%s'\n\n",name);
		printf("..::Name(Use identical): ");
		scanf("%[^\n]",&list.name);
		fflush(stdin);
		printf("..::Phone");
		scanf("%ld",&list.ph);
		fflush(stdin);
		pirntf("..:Address: ");
		scanf("%[^\n]",&list.add);
		fflush(stdin);
		printf("..:: Email Address: ");
		gets(list.email);
		printf("\n");
		fwrite(&list,sizeof(list),1,ft);
		fclose(fp);
		fclose(ft);
		remove("contact.dll");
		rename("temp.dat", "contact.dll");
		break;

		/* *************** DELETE CONTACT ************** */ 




		case 5: 
		system("cls");
		fflush(stdin);
		printf("\n\n\t..:: DELETE A CONTACT\n\t=================\n\t..::Enter the name of contact to delete:");
		scanf("%[^n]",&name);
		fp=fopen("contact.dll","r");
		ft=fopen("temp.dat","w");
		while(fread(&list,sizeof(list),1,fp)!=0)
		if(strcmp(name,list.name)!=0)
		fwrite(&list,sizeof(list),1,ft);
		fclose(fp);
		fclose(ft);
		remove("contact.dll");
		rename("temp.dat","contact.dll");
		break;


		default : 
		printf("Invalid Choice");
		break; 
		
	}
	
	printf("\n\n\n..:: Enter the Choice:\n\n\t[1] Main Menu \t\t[0] Exit\n");
	scanf("%d",&ch);
	switch(ch){
		case 1: 
		goto main;


		case 0:
		break;


		default : 
		printf("Invalid Choice");
		break; 
	}
	return 0; 
}