#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<malloc.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<string.h>

typedef struct login
{
   long long int id;
   int pin;

}login;


typedef struct stud
{
   long long int s_id;
   char s_name[30];
   char batch[3];
   int sem;

   struct stud * next;

}stud;

typedef struct teacher
{
   long long int f_id;
   char f_name[30];
   struct teacher * next;
}teacher;

typedef struct master_stud
{
    stud * head;
    stud * end;

}master_stud;

typedef struct master_teacher
{
   teacher * head;
   teacher * end;

}master_teacher;


typedef struct stack
{
  char date[10];
  char facname[30];
  char att;
  struct stack *next;
}stack;

typedef struct mstack
{
  stack *top;
}mstack;



void student();
void faculty();

void password(int,master_stud * , master_teacher *);
void loading();
void stud_menu(long long int,master_stud *);

void page1(stud* temp);
void page2(stud* temp);
void page2a(stud* temp);
void page2b(stud* temp);
void pagef1(master_stud *m,teacher * fac);
void pagef2(master_stud *m,teacher * fac);

master_stud *InsertNode()
{
	FILE *fp;
	stud *temp;
	master_stud *m;
	long long int id;
	char name[30];
	char batch[3];
	int sem;
	fp=fopen("STUD.txt","r");
	m=(master_stud *)malloc(sizeof(master_stud));
	m->head=NULL;
	m->end=NULL;
	//m->count=0;
	while(!feof(fp))
	{
		fscanf(fp,"%lld  %d %s ",&id,&sem,batch);
		fgets(name,30,fp);
	      //	if(!feof(fp))
	       //	{
			temp=(stud *)malloc(sizeof(stud));
			temp->next=NULL;
			temp->s_id=id;
			strcpy(temp->s_name,name);
			temp->sem=sem;
			strcpy(temp->batch,batch);
			if(m->head==NULL)
			{
				m->head=temp;
				m->end=temp;
			}
			else
			{
				m->end->next=temp;
				m->end=temp;
			}
		//m->count++;
	    //	}

	}
	fclose(fp);

	return m;
}

master_teacher *InsertNodeT()
{
	FILE *fp;
	teacher *temp;
	master_teacher *m;
	long long int id;
	char name[30];

	fp=fopen("FDATA.txt","r");
	m=(master_teacher *)malloc(sizeof(master_teacher));
	m->head=NULL;
	m->end=NULL;
	//m->count=0;
	while(!feof(fp))
	{
		fscanf(fp,"%lld ",&id);
		fgets(name,30,fp);

	      //	if(!feof(fp))
	       //	{
			temp=(teacher *)malloc(sizeof(teacher));
			temp->next=NULL;
			temp->f_id=id;
			strcpy(temp->f_name,name);


			if(m->head==NULL)
			{
				m->head=temp;
				m->end=temp;
			}
			else
			{
				m->end->next=temp;
				m->end=temp;
			}
		//m->count++;
	    //	}
       //	printf(" a ");
	}
	fclose(fp);

	return m;
}

void f_menu(master_stud *m,teacher * fac)
{
   int gd=DETECT,gm;
   clrscr();
   initgraph(&gd,&gm,"..\\BGI");
   settextstyle(6,0,5);
   outtextxy(195,20,"Faculty Kiosk");
   pagef1(m,fac);
   getch();
   closegraph();
}

void pagef1(master_stud *m,teacher*fac)
{
   int b;
   cleardevice();
   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Faculty Kiosk");

   setcolor(RED);
   settextstyle(3,0,4);
   outtextxy(220,120," Faculty Details");

   gotoxy(20,14);
   printf("Name         : ");
   puts(fac->f_name);

   gotoxy(20,17);
   printf("Employee No. : %lld",fac->f_id);


    while(1)
   {
	     if(kbhit())
	       {
		     b=getch();

		     if(b==77)
		      {
			sound(400);
			delay(50);
			nosound();
			pagef2(m,fac);
		      }
		     if(b==75)
		      {

			sound(300);
			delay(50);
			nosound();
			pagef2(m,fac);

		      }
		     if(b==27)
		      {  sound(100);
			 delay(100);
			 nosound();

			 delay(80);

			 sound(200);
			 delay(100);
			 nosound();

			  cleardevice();
			 settextstyle(3,0,5);
			 outtextxy(120,160,"\n\n\n  LOGGING OUT..!!  ");
			 loading();
			 cleardevice();
			 settextstyle(GOTHIC_FONT,0,7);
			 outtextxy(120,160,"Thank You");
			 delay(1000);
			 exit(0);

			}
		}

   }


}

void pagef2(master_stud *m,teacher * fac)
{
   int b,sem,x=28,y=14,i; char att,ch,date[12],batch[3],sub[30],fname[30],n[5];
   stud *temp=m->head;  FILE *fptr;

   cleardevice();
   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Faculty Kiosk");

   setcolor(RED);
   settextstyle(3,0,4);
   outtextxy(170,120," Update Attendance");

   gotoxy(20,14);
   printf("Date  : ");

   gotoxy(50,14);
   printf("Semester : ");

   gotoxy(20,16);
   printf("Batch : ");

   gotoxy(50,16) ;
   printf("Subject  : ");
   fflush(stdin);
   gotoxy(28,14);
   gets(date);

   gotoxy(61,14);
   scanf("%d",&sem);

   fflush(stdin);

   gotoxy(28,16);
   gets(batch);
   fflush(stdin);
   gotoxy(61,16);
   gets(sub);

   if(strcmpi(sub,"Data Structure")==0)
       strcpy (	n,"1");
   else if(strcmpi(sub,"Electronics")==0)
       strcpy  (n,"2");
   else if(strcmpi(sub,"Personality Development")==0)
       strcpy  (n,"3");
   else if(strcmpi(sub,"Physics")==0)
       strcpy(	n,"4");
   else if(strcmpi(sub,"Maths")==0)
       strcpy (	n,"5");

   gotoxy(25,18);
   printf("Name");

   gotoxy(60,18);
   printf("Present/Absent");
   x=25,y=20;

   while(temp!=NULL)
    {
       if(strcmpi(temp->batch,batch)==0 && temp->sem==sem)
	{
	     gotoxy(x,y);
	     puts(temp->s_name);
	     fflush(stdin);
	     gotoxy(x+35,y++);
	     scanf("%c",&att);

	     sprintf(fname,"%lld",temp->s_id);
	     strcat(fname,n);
	     strcat(fname,".txt");

	     fptr=fopen(fname,"a");

	     fprintf(fptr,"%s %s %c\n",date,fac->f_name,att);

	     fclose(fptr);
	}
	temp=temp->next;
    }

   if(temp==NULL)
    {

       printf("\n\t\t\t\t  Attendance Updated..!! ");
       getch();
       pagef1(m,fac);

    }

  while(1)
   {
	     if(kbhit())
	       {
		     b=getch();

		     if(b==77)
		      {
			sound(400);
			delay(50);
			nosound();
			pagef1(m,fac);
		      }
		     if(b==75)
		      {

			sound(300);
			delay(50);
			nosound();
			pagef1(m,fac);

		      }
		     if(b==27)
		      {  sound(100);
			 delay(100);
			 nosound();

			 delay(80);

			 sound(200);
			 delay(100);
			 nosound();

			 pagef1(m,fac);
		      }
		}

   }


}



int push(char fname[],mstack *p,stud * temp)
{
  stack *new1;

  FILE *fp=fopen(fname,"r");

  if(fp==NULL)
   return 0;

  while(!feof(fp))
  { new1=(struct stack *)malloc(sizeof(struct stack));
    new1->next=NULL;
    fscanf(fp,"%s %s %c\n",new1->date,new1->facname,&new1->att);

    if(p->top==NULL)
    {
      p->top=new1;
    }

    else
    {
     new1->next=p->top;
     p->top=new1;
    }
  }
  fclose(fp);
  return 1;
}


void display(mstack *p,char sname[],stud* temp)
{  stack *s=p->top;
   int b,l=0;
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"..\\BGI");
   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Student Kiosk");

   settextstyle(1,0,2);
   setcolor(YELLOW);
   outtextxy(198,150,sname);

   gotoxy(25,18);
  if(p->top!=NULL)
  {
    while(s!=NULL)
    {
	l++;
	gotoxy(25,18+l);
	printf("%s\t%s\t%c",s->date,s->facname,s->att);
      s=s->next;
    }

  }

   while(1)
   {
      if(kbhit())
	       {
		     b=getch();

		     if(b==27)
		       {
			 sound(100);
			 delay(100);
			 nosound();

			 delay(80);

			 sound(200);
			 delay(100);
			 nosound();

			 page2a(temp);

		      }
	       }
    }


}


void s_menu(stud* temp)
{
   int gd=DETECT,gm;
   clrscr();
   initgraph(&gd,&gm,"..\\BGI");
   settextstyle(6,0,5);
   outtextxy(195,20,"Student Menu");
   page1(temp);
   getch();
   closegraph();
}

void page1(stud * temp)
{
   int b;
   cleardevice();
   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Student Kiosk");

   setcolor(RED);
   settextstyle(3,0,4);
   outtextxy(220,120,"Student Details");

   gotoxy(20,14);
   printf("Name           : "); puts(temp->s_name);

   gotoxy(20,17);
   printf("Enrollment No. : %lld",temp->s_id);

   gotoxy(20,20);
   printf("Batch          : ");puts(temp->batch);

   gotoxy(20,23);
   printf("Semester       : %d",temp->sem);

    while(1)
   {
	     if(kbhit())
	       {
		     b=getch();

		     if(b==77)
		      {
			sound(400);
			delay(50);
			nosound();
			page2(temp);
		      }
		     if(b==75)
		      {

			sound(300);
			delay(50);
			nosound();
			page2(temp);

		      }
		     if(b==27)
		      {  sound(100);
			 delay(100);
			 nosound();

			 delay(80);

			 sound(200);
			 delay(100);
			 nosound();

			 exit(0);
		      }
		}

   }


}

void page2(stud * temp)
{
   int x1,y1,b;
   cleardevice();

   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Student Kiosk");

   settextstyle(1,0,2);
   setcolor(YELLOW);
   outtextxy(198,150,"Subject Wise Attendance");
  /*
   settextstyle(1,0,2);
   setcolor(WHITE);
   outtextxy(198,200,"Overall Attendance");
  */
   x1=145,y1=158;
   setcolor(YELLOW);
   line(x1,y1,x1+10,y1);
   line(x1+10,y1,x1+10,y1-5);
   line(x1+10,y1-5,x1+16,y1-5);
   line(x1+16,y1-5,x1+16,y1);
   line(x1+16,y1,x1+40,y1);
   line(x1+40,y1,x1+40,y1+6);
   line(x1+40,y1+6,x1+23,y1+6);
   line(x1+33,y1+6,x1+33,y1+12);
   line(x1+33,y1+12,x1+23,y1+12);
   line(x1+29,y1+12,x1+29,y1+18);
   line(x1+29,y1+18,x1+10,y1+18);
   line(x1+10,y1+18,x1+10,y1+16);
   line(x1+10,y1+16,x1,y1+16);
   line(x1,y1+16,x1,y1);
   setfillstyle(SOLID_FILL,YELLOW);
   bar(x1+4,y1,x1+6,y1+16);
   while(1)
   {
      if(kbhit())
	       {
		     b=getch();

		     if(b==77)
		      {
			sound(400);
			delay(50);
			nosound();
			page1(temp);
		      }
		     if(b==75)
		      {
			sound(300);
			delay(50);
			nosound();
			 page1(temp);
		      }
		     if(b==27)
		       {  sound(100);
			 delay(100);
			 nosound();

			 delay(80);

			 sound(200);
			 delay(100);
			 nosound();

			 cleardevice();
			 settextstyle(3,0,5);
			 outtextxy(120,160,"\n\n\n  LOGGING OUT..!!  ");
			 loading();
			 cleardevice();
			 settextstyle(GOTHIC_FONT,0,7);
			 outtextxy(120,160,"Thank You");
			 delay(1000);
			 exit(0);
		      }

		     if(b==13)
		      {
			 if(y1==158)
			   page2a(temp);

		 }

	       }


   }

}
void page2a(stud* temp)
{
   int x=198,y=150,x1,y1,b,status;
   char fname[30];
   mstack *ms;
   cleardevice();

   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Student Kiosk");

   settextstyle(1,0,2);
   setcolor(YELLOW);
   outtextxy(198,150,"Data Structure");

   settextstyle(1,0,2);
   setcolor(WHITE);
   outtextxy(198,200,"Electronics");

   settextstyle(1,0,2);
   setcolor(WHITE);
   outtextxy(198,250,"Personality Development");

   settextstyle(1,0,2);
   setcolor(WHITE);
   outtextxy(198,300,"Physics");

   settextstyle(1,0,2);
   setcolor(WHITE);
   outtextxy(198,350,"Maths");



   x1=145,y1=158;
   setcolor(YELLOW);
   line(x1,y1,x1+10,y1);
   line(x1+10,y1,x1+10,y1-5);
   line(x1+10,y1-5,x1+16,y1-5);
   line(x1+16,y1-5,x1+16,y1);
   line(x1+16,y1,x1+40,y1);
   line(x1+40,y1,x1+40,y1+6);
   line(x1+40,y1+6,x1+23,y1+6);
   line(x1+33,y1+6,x1+33,y1+12);
   line(x1+33,y1+12,x1+23,y1+12);
   line(x1+29,y1+12,x1+29,y1+18);
   line(x1+29,y1+18,x1+10,y1+18);
   line(x1+10,y1+18,x1+10,y1+16);
   line(x1+10,y1+16,x1,y1+16);
   line(x1,y1+16,x1,y1);
   setfillstyle(SOLID_FILL,YELLOW);
   bar(x1+4,y1,x1+6,y1+16);

    while(1)
   {
      if(kbhit())
	       {
		     b=getch();

		     if(b==27)
		       {
			 sound(100);
			 delay(100);
			 nosound();

			 delay(80);

			 sound(200);
			 delay(100);
			 nosound();

			 page2(temp);

		      }

		   else if(b==13)
		   {
			if(y1==158)
			{    sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"1");
			     strcat(fname,".txt");
			     ms=NULL;
			     status= push(fname,ms,temp);
			     if(status==0)
			     {
				gotoxy(20,25);
				printf("No Records Found..!! ");
				getch();
				page2a(temp);

			     }
			    else
			     display(ms,"Data Structure",temp);

			}

			else if(y1==208)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"2");
			     strcat(fname,".txt");
			     ms=NULL;
			       status= push(fname,ms,temp);
			     if(status==0)
			     {
				gotoxy(20,25);
				printf("No Records Found..!! ");
				getch();
				page2a(temp);

			     }
			    else
			     display(ms,"Electronics",temp);
			}

			else if(y1==258)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"3");
			     strcat(fname,".txt");
			     ms=NULL;
			       status= push(fname,ms,temp);
			     if(status==0)
			     {
				gotoxy(20,25);
				printf("No Records Found..!! ");
				getch();
				page2a(temp);

			     }
			    else
			     display(ms,"Personality Development",temp);
			}

			else if(y1==308)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"4");
			     strcat(fname,".txt");
			     ms=NULL;
			       status= push(fname,ms,temp);
			     if(status==0)
			     {
				gotoxy(20,25);
				printf("No Records Found..!! ");
				getch();
				page2a(temp);

			     }
			    else
			     display(ms,"Physics",temp);
			}

			else if(y1==358)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"5");
			     strcat(fname,".txt");
			     ms=NULL;
			       status= push(fname,ms,temp);
			     if(status==0)
			     {
				gotoxy(20,25);
				printf("No Records Found..!! ");
				getch();
				page2a(temp);

			     }
			    else
			     display(ms,"Maths",temp);

			}
		   }

		   else  if(b==80 && y1==158)
		       {

			  x1=145,y1=208;

			  sound(350);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");



			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }
		    else  if(b==80 && y1==208)
		       {

			  x1=145,y1=258;

			  sound(350);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");



			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }

		    else  if(b==80 && y1==258)
		       {

			  x1=145,y1=308;

			  sound(350);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");

			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }

		 else if(b==80 && y1==308)
		       {

			  x1=145,y1=358;

			  sound(350);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,350,"Maths");


			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }

		   else if(b==80 && y1==358)
		       {

			  x1=145,y1=158;

			  sound(350);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");


			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }


		else if(b==72 && y1==358)
		       {

			  x1=145,y1=308;

			  sound(450);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");


			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }
		  else if(b==72 && y1==308)
		       {

			  x1=145,y1=258;

			  sound(450);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");


			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }
		   else if(b==72 && y1==258)
		       {

			  x1=145,y1=208;

			  sound(450);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structures");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");


			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }
		 else  if(b==72 && y1==208)
		       {

			  x1=145,y1=158;

			  sound(450);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personoality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");

			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }
		  else if(b==72 && y1==158)
		       {

			  x1=145,y1=358;

			  sound(450);
			  delay(50);
			  nosound();

			  cleardevice();

			  setcolor(BLUE);
			  settextstyle(3,0,7);
			  outtextxy(125,20,"Student Kiosk");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,150,"Data Structure");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,200,"Electronics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,250,"Personality Development");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,300,"Physics");

			  settextstyle(1,0,2);
			  setcolor(WHITE);
			  outtextxy(198,350,"Maths");

			  setcolor(YELLOW);
			  line(x1,y1,x1+10,y1);
			  line(x1+10,y1,x1+10,y1-5);
			  line(x1+10,y1-5,x1+16,y1-5);
			  line(x1+16,y1-5,x1+16,y1);
			  line(x1+16,y1,x1+40,y1);
			  line(x1+40,y1,x1+40,y1+6);
			  line(x1+40,y1+6,x1+23,y1+6);
			  line(x1+33,y1+6,x1+33,y1+12);
			  line(x1+33,y1+12,x1+23,y1+12);
			  line(x1+29,y1+12,x1+29,y1+18);
			  line(x1+29,y1+18,x1+10,y1+18);
			  line(x1+10,y1+18,x1+10,y1+16);
			  line(x1+10,y1+16,x1,y1+16);
			  line(x1,y1+16,x1,y1);
			  setfillstyle(SOLID_FILL,YELLOW);
			  bar(x1+4,y1,x1+6,y1+16);




		       }


	       }


   }

}
/*
void page2b(stud *temp)
{
	FILE *f;
	int i,j;
	int gd=DETECT,gm;
	char n[1],text[12][4]={"0","10","20","30","40","50","60","70","80","90","100"};
	int lx,rx,ly,ry;
	int pr=0;
	int ab=0;
	char str1[30],str2[30];
	char c;
	int att=0;
	char fileName[30];
	initgraph(&gd,&gm,"..//BGI");
	ly=380;
	ry=385;

	line(3,3,3,480);
	line(3,3,640,3);
	for(i=0;i<=10;i++)
	{
	     outtextxy(i*10,1,text[i]);
	}

	for(i=10;i<=100;i++)
	    outtextxy(1,480-(i*10),text[i]);

	for(i=0;i<5;i++)
	{
		pr=0;
		ab=0;
		itoa(i,n,10);
		sprintf(fileName,"%lld",temp->s_id);
		strcat(fileName,n);
		strcat(fileName,".txt");
		f=fopen(fileName,"r");
		if(f==NULL)
		att=0;
	       else
		while(!feof(f))
		{
			fscanf(f,"%s %s %c",str1,str2,c);
			if(!feof(f))
			{
				if(c=='p' || c=='P')
					pr++;
				else
					ab++;
			}
			if(pr==0 )
			att=0;
			else
			att=(pr/(pr+ab))*100;

		}
		rx=att*10;

		switch(i)
		{
			case 1:
				printf("Data Structures");
				bar(3,ly,rx,ry);
			case 2:
				ry+=10;
				ly+=10;
				printf("Electronics");
				bar(3,ly,rx,ry);
			case 3:
				ry+=10;
				ly+=10;
				printf("Personality Development");
				bar(3,ly,rx,ry);
			case 4:
				ry+=10;
				ly+=10;
				printf("Physics");
				bar(3,ly,rx,ry);
			case 5:
				ry+=10;
				ly+=10;
				printf("Maths");
				bar(3,ly,rx,ry);
		}
	}
}
*/
void triangle(int x1,int y1,int x2,int y2,int x3,int y3)
{
   setcolor(GREEN);
   line(x1,y1,x2,y2);
   line(x2,y2,x3,y3);
   line(x1,y1,x3,y3);
   setcolor(BLACK);
}

void loading()
  {
	    int x,y,i;

	   for(i=0;i<2;i++)
	    {
	       x=280; y=378;
	       setfillstyle(SOLID_FILL , WHITE);
	       bar(x,y+22,x+20,y+42);
	       delay(200);
	       bar(x,y,x+20,y+20);
	       delay(200);
	       bar(x+22,y,x+42,y+20);
	       delay(200);
	       bar(x+22,y+22,x+42,y+42);
	       delay(200);

	       setfillstyle(SOLID_FILL , BLACK);
	       bar(x,y+22,x+20,y+42);
	       delay(200);
	       bar(x,y,x+20,y+20);
	       delay(200);
	       bar(x+22,y,x+42,y+20);
	       delay(200);
	       bar(x+22,y+22,x+42,y+42);
	       delay(200);

	   }

     }

int password_check(long long int id, int password,int n)
{
    FILE *fptr;
    login l;
    int flag =0;

    if(n==1)
     fptr=fopen("SPASS.txt","r");

    else if(n==2)
      fptr=fopen("FPASS.txt","r");

    else
      fptr=fopen("apasswords.txt","r");

    if(fptr==NULL)
     printf("\n\n Cannot Open File..!! ");

    while(!feof(fptr))
     {

       fscanf(fptr,"%lld %d",&l.id,&l.pin);

	if((l.id==id) && l.pin==password)
	  {

	     flag=1; break;

	  }

     }

  fclose(fptr);
  return flag;

}

void password(int n,master_stud *sm, master_teacher *tm)
{

   char ch,pass[30];
   teacher *tmp=tm->head;
   long long int num;
   int size=0,status,ch1,pin;


   up:

   cleardevice();

   setcolor(RED);
   settextstyle(0,HORIZ_DIR,3);
   outtextxy(235,40,"Login");

   setbkcolor(BLACK);
   setcolor(WHITE);

   setcolor(WHITE);
   rectangle(250,140,330,200);

   arc(290,140,0,180,34);
   arc(290,140,0,180,30);
   setcolor(RED);

   rectangle(230,270,390,300);

   rectangle(230,318,390,350);

   settextstyle(0,HORIZ_DIR,1);
   outtextxy(40,270,"Enter Unique ID : ");

   settextstyle(0,HORIZ_DIR,1);
   outtextxy(40,320,"Enter Password  : ");

   gotoxy(30,18);
   scanf("%lld",&num);
   while(1)
     {

	ch=getch();
	if(ch==8)
	  {
	    if(size!=0)
	     {
	       printf("\b \b");
	       size--;
	     }
	    else
	     {
	       printf("\a");
	     }
	   }
	 else if(ch==13)
	   {
	      pass[size]='\0';
	      break;
	   }
	   else if(ch==27)
	   exit(0);
	 else
	   {
	      pass[size++]=ch;
	      gotoxy(30+size,21);
	      printf("*");
	   }
     }
  pin=atoi(pass);

  loading();

 status=password_check(num,pin,n);

 if(status==0)
   {
       printf("\n\n Invalid Login Details..!! Press Any Key To Try Again.. ");
       getch();
       goto up;

   }
 else
  {
      if(n==1)
	{
	    stud_menu(num,sm);

	}
      else if(n==2)
	{
	 while(tmp!=NULL)
	   {

		if(tmp->f_id==num)
		 {
		   break;
		 }
	       tmp=tmp->next;

	    }
	  f_menu(sm,tmp);

	}

  }



}

void faculty(master_stud *sm, master_teacher * tm)
{
   int ch1;
   int n=2;
   cleardevice();

   setcolor(WHITE);
   settextstyle(0,HORIZ_DIR,2);
   outtextxy(200,70,"Faculty Login");
   setbkcolor(BLACK);
/*   setcolor(WHITE);
   rectangle(230,130,390,290);
   floodfill(340,140,WHITE);
   setcolor(BLACK);
   circle(310,183,34);

   circle(310,290,70);
   */
   circle(300,160,40);
floodfill(300,160,WHITE);
setfillstyle(SOLID_FILL,WHITE);
pieslice(300,300,0,180,90);
//floodfill(210,290,WHITE);
  // triangle(550,200,550,220,570,210);
 //  triangle(560,200,560,220,580,210);
   triangle(60,200,60,220,40,210);
   triangle(50,200,50,220,30,210);

 //  ch1=getch();
 while(1)
 {
   if(kbhit())
   {
      ch1=getch();
   if(ch1==75)
    {
      setcolor(WHITE);
      rectangle(20,190,70,230);
      delay(300);
     // getch();
      student(sm,tm);
    }
 /* else if(ch1==77)
    {
      setcolor(WHITE);
      rectangle(540,190,590,230);
      getch();
   //   admin(sm,tm);

    } */

   else if(ch1==13)
    {
      setcolor(WHITE);
      rectangle(200,115,410,310);
     // getch();
      password(n,sm,tm);
    }
    else if(ch1==27)
    exit(0);
    }
    }

}

void student(master_stud *sm, master_teacher * tm)
{
    int ch;
    int n=1;
    cleardevice();

    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(200,70,"Student Login");
    setbkcolor(BLACK);
   /* setcolor(WHITE);
    rectangle(230,130,390,290);
    floodfill(340,140,WHITE);
    setcolor(BLACK);
    circle(310,183,34);
    circle(310,290,70);
    circle(310,227,7);
    line(308,230,300,260);
    line(312,230,320,260);
    line(300,260,310,290);
    line(320,260,310,290);*/

    circle(300,160,40);
floodfill(300,160,WHITE);
setfillstyle(SOLID_FILL,WHITE);
pieslice(300,300,0,180,90);
setcolor(RED);
circle(300,220,10);
line(298,222,288,270);
line(288,270,300,300);
line(303,222,315,270);
line(315,270,300,300);
//floodfill(210,290,WHITE);
    triangle(550,200,550,220,570,210);
    triangle(560,200,560,220,580,210);

   // ch=getch();
   while(1)
  {

    if(kbhit())
    {

      ch=getch();

       if(ch==77)
      {
	 setcolor(WHITE);
	 rectangle(540,190,590,230);
       //	 getch();
	 faculty(sm,tm);
      }

    else if(ch==13)
      {
	 setcolor(WHITE);
	 rectangle(200,115,410,310);
	 //getch();
	 password(n,sm,tm);
      }
      else if(ch==27)
      exit(0);
    }

  }
}

void stud_menu(long long int n,master_stud *m)
{
       stud * temp=m->head;

       while(temp->s_id!=n && temp!=NULL)
	 temp=temp->next;

       getch();
       s_menu(temp);
}
void main()
{
   int gd=DETECT,gm;

   master_stud * sm=InsertNode();
   master_teacher * tm=InsertNodeT();
   initgraph(&gd,&gm,"..\\BGI");
   student(sm,tm);

   getch();
   closegraph();

}

