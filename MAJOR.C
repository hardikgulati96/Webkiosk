#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<malloc.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>

typedef struct login
{
   long long int id;
   char password[20];

}login;

typedef struct subject
{
   char sub_name[30];
   float att;
   struct subject * next;

}subject;

typedef struct stud
{
   long long int s_id;
   char s_name[30];
   char batch[3];
   int sem;
   subject * shead;
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
void admin();
void password(int,master_stud * , master_teacher *);
void loading();
void stud_menu(long long int,master_stud *);
//void fac_menu(long long int,master_teacher *);
void admin_menu(long long int);
void page1(stud* temp);
void page2(stud* temp);
void page2a(stud* temp);
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
	fp=fopen("stud.txt","r");
	m=(master_stud *)malloc(sizeof(master_stud));
	m->head=NULL;
	m->end=NULL;
	//m->count=0;
	while(!feof(fp))
	{
		fscanf(fp,"%lld",id);
                fscanf(fp,"%d",sem);

		fgets(batch,80,fp);
                fgets(name,80,fp);

		if(!feof(fp))
		{
			temp=(stud *)malloc(sizeof(stud));
			temp->next=NULL;
			temp->id=id;
			strcpy(temp->sname,name);
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
				m->end=m->end->next;
			}
		//m->count++;
		}
	}
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
   puts(fac->fname);

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

			 exit(0);
		      }
		}

   }


}

void pagef2(master_stud *m,teacher * fac)
{
   int b,sem,x=28,y=14,i; char att,ch,date[12],batch[3],sub[30],fname[30],n;
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

   gotoxy(28,14);
   gets(date);

   gotoxy(61,14);
   scanf("%d",sem);

   fflush(stdin);

   gotoxy(28,16);
   gets(batch);

   gotoxy(61,16);
   gets(sub);

   if(strcmpi(sub,"Data Structures")==0)
	n='1';
   else if(strcmpi(sub,"Electronics")==0)
	n='2';
   else if(strcmpi(sub,"Personality Development")==0)
	n='3';
   else if(strcmpi(sub,"Physics")==0)
	n='4';
   else if(strcmpi(sub,"Maths")==0)
	n='5';

   gotoxy(25,18);
   printf("Name");

   gotoxy(60,18);
   printf("Present/Absent");
   x=25,y=20;
   while(temp!=NULL)
    {
       if(strcmpi(temp->batch,batch)==0 && temp->sem==sem)
	{
	     gotoxy(x,y++);
	     puts(temp->sname);

	     gotoxy(x+35,y);
	     scanf("%c",&att);

	     sprintf(fname,"%lld",temp->s_id);
	     strcat(fname,n);
	     strcat(fname,".txt");

	     fptr=fopen(fname,"a");
	     fprintf("%s %s %c\n",date,fac->fname,att);
	     fclose(fname);
	}
	temp=temp->next;
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

			 exit(0);
		      }
		}

   }


}



void push(char fname[],mstack *p,stud * temp)
{
  stack *new1;

  FILE *fp=fopen(fname,"r");

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
}


void display(mstack *p,char sname[],stud* temp)
{  stack *s=p->top;
   int b;
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
    { printf("%s\t%s\t%c\n\n",s->date,s->facname,s->att);
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
   printf("Name           : ");

   gotoxy(20,17);
   printf("Enrollment No. : ");

   gotoxy(20,20);
   printf("Batch          : ");

   gotoxy(20,23);
   printf("Semester       : ");

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
   int x=198,y=150,x1,y1,b;
   cleardevice();

   setcolor(BLUE);
   settextstyle(3,0,7);
   outtextxy(125,20,"Student Kiosk");

   settextstyle(1,0,2);
   setcolor(YELLOW);
   outtextxy(198,150,"Subject Wise Attendance");

   settextstyle(1,0,2);
   setcolor(WHITE);
   outtextxy(198,200,"Overall Attendance");

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

			 exit(0);
		      }

		     if(y1==208 && b==80)
		      {
			  sound(350);
			  delay(50);
			  nosound();

			 goto up;
		      }

		     if(b==80)
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
			  outtextxy(198,150,"Subject Wise Attendance");

			  settextstyle(1,0,2);
			  setcolor(YELLOW);
			  outtextxy(198,200,"Overall Attendance");


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

		      if(b==72)
			{


			   sound(450);
			   delay(50);
			   nosound();
			   up:
			   cleardevice();
			   setcolor(BLUE);
			   settextstyle(3,0,7);
			   outtextxy(125,20,"Student Kiosk");

			   settextstyle(1,0,2);
			   setcolor(YELLOW);
			   outtextxy(198,150,"Subject Wise Attendance");

			   settextstyle(1,0,2);
			   setcolor(WHITE);
			   outtextxy(198,200,"Overall Attendance");

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



			 }
		     if(b==13)
		      {
			 if(y1==158)
			   page2a(temp);

			 if(y1==208)
			  page2b(temp);
		      }

	       }


   }

}
void page2a(stud* temp)
{
   int x=198,y=150,x1,y1,b;
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
			     push(fname,ms,temp);
			     display(ms,"Data Structure",temp);
			}

			else if(y1==208)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"2");
			     strcat(fname,".txt");
			     ms=NULL;
			     push(fname,ms,temp);
			     display(ms,"Electronics",temp);
			}

			else if(y1==258)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"3");
			     strcat(fname,".txt");
			     ms=NULL;
			     push(fname,ms,temp);
			     display(ms,"Personality Development",temp);
			}

			else if(y1==308)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"4");
			     strcat(fname,".txt");
			     ms=NULL;
			     push(fname,ms,temp);
			     display(ms,"Physics",temp);
			}

			else if(y1==358)
			{
			     sprintf(fname,"%lld",temp->s_id);
			     strcat(fname,"5");
			     strcat(fname,".txt");
			     ms=NULL;
			     push(fname,ms,temp);
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

void page2b(stud *temp)
{
	FILE *f;
	int i,j;
	char n[1];
	int lx,rx,ly,ry;
	int pr=0;
	int ab=0;
	char str1[30],str2[30];
	char c;
	int att=0;
	char fileName[30];
	ly=380;
	ry=385;

	line(3,3,3,480);
	line(3,3,640,3);
	for(i=0;i<=100;i+=10)
	{
		outtextxy(i,1,i);
	}
	for(i=10;i<=100;i++)
		outtextxy(1,480-i);
	for(i=0;i<5;i++)
	{
		pr=0;
		ab=0;
		itoa(i,n,10);
		strcat(fileName,temp->s_id);
		strcat(fileName,n);
		strcat(fileName,".txt");
		f=fopen(fileName,"r");
		while(!feof(f))
		{
			fscanf(fp,"%s %s %c",str1,str2,c);
			if(!feof(f))
			{
				if(c=='p' || c=='P')
					pr++;
				else
					ab++;
			}
			att=((pr+ab)/pr)*100;

		}
		rx=att;

		switch(i)
		{
			case 1:
				printf("Data Structures");
				bar3d(3,ly,rx,ry,10,0);
			case 2:
				ry+=10;
				ly+=10;
				printf("Electronics");
				bar3d(3,ly,rx,ry,10,0);
			case 3:
				ry+=10;
				ly+=10;
				printf("Personality Development");
				bar3d(3,ly,rx,ry,10,0);
			case 4:
				ry+=10;
				ly+=10;
				printf("Physics");
				bar3d(3,ly,rx,ry,10,0);
			case 5:
				ry+=10;
				ly+=10;
				printf("Maths");
				bar3d(3,ly,rx,ry,10,0);
		}
	}
}

void triangle(int x1,int y1,int x2,int y2,int x3,int y3)
{
   setcolor(GREEN);
   line(x1,y1,x2,y2);
   line(x2,y2,x3,y3);
   line(x1,y1,x3,y3);
   setcolor(BLACK);
}

/*void Motion(int xrad, int yrad, int midx, int midy, int x[60], int y[60])
{
      int i, j = 0;
      for (i = 360; i > 0; i = i - 6)
	{
		x[j] = midx - (xrad * cos((i * 3.14) / 180));
		y[j] = midy - (yrad * sin((i * 3.14) / 180));
		j++;
	}
     return;
} */

void loading()
  {
    /* int i = 0, midx, midy;
     int xrad, yrad, x[9][60], y[9][60];
     int pos[9], ir, tmp;

     midx=300;
     midy=400;
     ir = 7;

     for (i = 0; i < 9; i++)
	{
		pos[i] = i * 6;
	}

     xrad = 20, yrad = 20;

     for (i = 0; i < 9; i++)
       {
	  Motion(xrad, yrad, midx, midy, x[i], y[i]);
       }

     while (!kbhit())
	{
		setcolor(CYAN);
		setfillstyle(SOLID_FILL, CYAN);
		pieslice(x[0][pos[0]], y[0][pos[0]], 0, 360, ir);

		setcolor(GREEN);
		setfillstyle(SOLID_FILL, GREEN);
		pieslice(x[1][pos[1]], y[1][pos[1]], 0, 360,ir);


		setcolor(BLUE);
		setfillstyle(SOLID_FILL, BLUE);
		pieslice(x[2][pos[2]], y[2][pos[2]], 0, 360, ir);


		setcolor(RED);
		setfillstyle(SOLID_FILL, RED);
		pieslice(x[3][pos[3]], y[3][pos[3]], 0, 360, ir);


		setcolor(BROWN);
		setfillstyle(SOLID_FILL, BROWN);
		pieslice(x[4][pos[4]], y[4][pos[4]], 0, 360, ir);


		setcolor(LIGHTGRAY);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		pieslice(x[5][pos[5]], y[5][pos[5]], 0, 360, ir);


		setcolor(BROWN);
		setfillstyle(SOLID_FILL, BROWN);
		pieslice(x[6][pos[6]], y[6][pos[6]], 0, 360, ir);


		setcolor(LIGHTBLUE);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		pieslice(x[7][pos[7]], y[7][pos[7]], 0, 360, ir);


		setcolor(LIGHTRED);
		setfillstyle(SOLID_FILL, LIGHTRED);
		pieslice(x[8][pos[8]], y[8][pos[8]], 0, 360, ir);


		for (i = 0; i < 9; i++)
		{
		   if (pos[i] <= 0)
		    {
		      pos[i] = 59;
		    }
		   else
		    {
		      pos[i] = pos[i] - 1;
		    }
		}
		delay(10);

	} */
	    int x,y,i;

	   for(i=0;i<2;i++)
	    {
	       x=280; y=378;
	       setfillstyle(SOLID_FILL , WHITE);
	       bar(x,y+22,x+20,y+42);
	       delay(300);
	       bar(x,y,x+20,y+20);
	       delay(300);
	       bar(x+22,y,x+42,y+20);
	       delay(300);
	       bar(x+22,y+22,x+42,y+42);
	       delay(300);

	       setfillstyle(SOLID_FILL , BLACK);
	       bar(x,y+22,x+20,y+42);
	       delay(300);
	       bar(x,y,x+20,y+20);
	       delay(300);
	       bar(x+22,y,x+42,y+20);
	       delay(300);
	       bar(x+22,y+22,x+42,y+42);
	       delay(300);

	   }

     }

int password_check(long long int id, char * password,int n)
{
    FILE *fptr;
    login l;
    int flag =0;

    if(n==1)
     fptr=fopen("spasswords.txt","r");

    else if(n==2)
      fptr=fopen("fpasswords.txt","r");

    else
      fptr=fopen("apasswords.txt","r");

    if(fptr==NULL)
     printf("\n\n Cannot Open File..!! ");

    while(!feof(fptr))
     {
	fread(&l,sizeof(l),1,fptr);

	if(strcmp(l.id==id && l.password,password)==0)
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
   teacher *tea=NULL;
   long long int num;
   int size=0,status,ch1;
  // while(1)
  // {
  // if(kbhit())
  // {
  // ch1=getch();
  // if(ch1==27)
  // exit(0);


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

 loading();

 status=password_check(num,pass,n);

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
	 while(tm!=NULL)
	{
	while(tea!=NULL)
	{
	if(tm->head->f_id==tea->f_id)
	    {
	    f_menu(sm,tea);
	    }
	    tea=tea->next;
	    }
	     tm->head=tm->head->next;
	     }
	}

  }



}

/*void admin(master_stud *sm, master_teacher * tm)
{
   int ch2;
   int i,n=3;
   cleardevice();

   setcolor(WHITE);
   settextstyle(0,HORIZ_DIR,2);
   outtextxy(200,90,"ADMIN LOGIN");
   setbkcolor(BLACK);
   setcolor(WHITE);
   rectangle(230,130,390,290);
   floodfill(340,140,WHITE);
   setcolor(BLACK);
   triangle(310,145,240,270,384,270);
   triangle(310,158,254,262,368,262);

   for(i=0;i<8;i++)
    {
       line(307+i,170,307+i,240);
    }

   circle(310,250,4);
   triangle(60,200,60,220,40,210);
   triangle(50,200,50,220,30,210);
   while(1)
   {
   if(kbhit())
   {
   ch2=getch();

   if(ch2==75)
    {
       setcolor(WHITE);
       rectangle(20,190,70,230);
       delay(300);
       getch();
       faculty(sm,tm);
    }

  else if(ch2==13)
    {
       setcolor(WHITE);
       rectangle(210,115,410,305);
       getch();
       password(n,sm,tm);
    }
    else if(ch2==27)
    exit(0);
    }
    }      */



//}

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

       while(temp->s_id!=n)
	 temp=temp->next;

       s_menu(temp);
}
void main()
{
   int gd=DETECT,gm;
   master_stud *sm;
   master_teacher * tm;
   initgraph(&gd,&gm,"..\\BGI");
   student(sm,tm);

   getch();
   closegraph();

}

