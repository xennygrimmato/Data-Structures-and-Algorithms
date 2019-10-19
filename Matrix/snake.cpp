/*******************************************************
*     MYCPLUS Sample Code - http://www.mycplus.com     *
*                                                     *
*   This code is made available as a service to our   *
*      visitors and is provided strictly for the      *
*               purpose of illustration.              *
*                                                     *
* Please direct all inquiries to saqib at mycplus.com *
*******************************************************/

//Name: Usman Shahzada
//Email: usmanshahzada@hotmail.com
//Language: C\C++ 
//Category: Games\Graphics 
//Description: its a game .a snake is moving you have to use it to eat some food . 
//as you eat food your tail becomes longer and point count. 



#include<stdlib.h> 
#include<ctype.h> 
#include<conio.h> 
#include<stdio.h> 
#include<time.h> 
#include<dos.h> 


#define ESC 27 
#define UPARR 72 
#define LEFTARR 75 
#define DOWNARR 80 
#define RIGHTARR 77 
#define SAVE 60 
#define LOAD 61 


main() 
{ 
void starting(void); 
void make_xy(char **,char **); 
void getrand(char *,char *,char *,char *,char *,int,char); 
char getkey(char,char); 
void savegame(char *,char *,int,char); 
int loadgame(char *,char *,char *); 
void win_message(void); 


char *x,*y,pos_x,pos_y,num,out=0,old_ch=0,ch=0,new_ch,new_x,new_y,old_num=0; 
int i,length=6; 


starting(); 
make_xy(&x,&y); 
getrand(&pos_x,&pos_y,&num,x,y,length,ch); 


while(!out){ 
if((new_ch=getkey(old_ch,ch))==ESC) 
out=2; 
if(out) 
break; 
if(new_ch==SAVE) 
savegame(x,y,length,old_ch); 
else if(new_ch==LOAD){ 
length=loadgame(x,y,&ch); 
getrand(&pos_x,&pos_y,&num,x,y,length,ch); 
} 
else 
ch=new_ch; 
new_x=x[0]; 
new_y=y[0]; 
if(ch==UPARR) 
new_y=y[0]-1; 
else if(ch==LEFTARR) 
new_x=x[0]-1; 
else if(ch==DOWNARR) 
new_y=y[0]+1; 
else if(ch==RIGHTARR) 
new_x=x[0]+1; 
old_ch=ch; 
if((new_x<2)|(new_y<2)|(new_x>79)|(new_y>22)) 
out=1; /* HIGHEST POSSIBLE SCORE ÷ (78*21-6)*5 = 8160 ÷ 10,000 */ 
for(i=1;i<length-!old_num;i++) /* NOT "length": TAIL-END MAY MOVE AWAY! */ 
if((new_x==x[i])&(new_y==y[i])){ 
out=1; 
break; 
} 
if((pos_x==new_x)&(pos_y==new_y)){ 
old_num+=num; 
/* x=(char *)realloc(x,(score+6)*sizeof(char)); 
y=(char *)realloc(y,(score+6)*sizeof(char)); */ 
/* if((x==0)|(y==0)) */ /* PROBLEM IS NOT HERE */ 
/* x=x;*//* SOMEHOW realloc ISN'T COPYING PROPERLY */ 
getrand(&pos_x,&pos_y,&num,x,y,length,ch); 
} 
if(!old_num){ 
gotoxy(x[length-1],y[length-1]); 
putchar(' '); 
} 
else{ 
length++; 
if(length==1638){ 
win_message(); 
return 0; 
} 
gotoxy(67,25); 
printf("Score = %5d",length-6); 
old_num--; 
x[i+1]=x[i]; 
y[i+1]=y[i]; 
} 
for(i=length-1;i>0;i--){ 
x[i]=x[i-1]; 
y[i]=y[i-1]; 
if(i==1){ 
gotoxy(x[i],y[i]); 
putchar('Û'); 
} 
} 
x[0]=new_x; 
y[0]=new_y; 
gotoxy(x[0],y[0]); 
printf("\b"); /* USE THE FUNCTION _setcursortype() */ 
if(out) 
break; 
delay(99); 
} 
if(out==1){ 
gotoxy(1,24); 
printf("The snake collided with the wall or with itself!\n" 
"GAME OVER!!\t\t(Press 'q' to terminate...)"); 
gotoxy(x[0],y[0]); 
while(toupper(getch())!='Q'); 
} 
clrscr(); 
printf("Hope you enjoyed the game\n\n\t\tBye!\n"); 
return 0; 
} 


/*-------------------------------------------------------------------------*/ 


void starting() 
{ 
char i; 


clrscr(); /* FIRST TO DRAW A BOUNDARY for THE GAME */ 
putchar('É'); 
for(i=0;i<78;i++) 
putchar('Í'); 
putchar('»'); 
gotoxy(1,23); 
putchar('È'); 
for(i=0;i<78;i++) 
putchar('Í'); 
putchar('Œ'); 
window(1,2,1,23); 
for(i=0;i<21;i++) 
cprintf("º"); 
window(80,2,80,23); 
for(i=0;i<21;i++) 
cprintf("º"); /* THE BOUNDARY IS DRAWN */ 
window(1,1,80,25); 
gotoxy(38,12); 
printf("ÛÛÛÛÛ"); /* THE "SNAKE" IS PUT for THE FIRST TIME */ 
gotoxy(1,24); 
printf("Welcome to the game of SNAKE!\n(Press any arrow key to start now," 
" Escape to leave at any time...)"); /* WELCOME MESSAGE */ 
gotoxy(43,12); 
while(!kbhit()); 
gotoxy(30,24); 
delline();delline(); /* REMOVING MESSAGE */ 
cprintf("\n( EAT THE NUMBER !! ) Score = 0"); 
gotoxy(43,12); /* GO TO THE HEAD OF THE SNAKE */ 
} 


void make_xy(char **px,char **py) 
{ 
char i; 


*px=(char *)malloc(1638*sizeof(char)); /*EARLIER IT WAS 6, NOT 1638; BUT*/ 
*py=(char *)malloc(1638*sizeof(char)); /*realloc IS NOT COPYING PROPERLY*/ 
for(i=0;i<6;i++){ 
(*px)[i]=43-i; 
(*py)[i]=12; 
} /* THE TWO ARRAYS for COORDINATES OF THE SNAKE ARE SIMULATED */ 
} 


void getrand(char *px,char *py,char *pn,char *x,char *y,int length,char ch) 
{ 
int allowed=0,i; /* i AND length MUST BE int */ 


while(!allowed){ 
allowed=1; 
srand((unsigned)time(0)); 
*px=rand()%78+2; /* GENERATING RANDOM POSITIONAL COORDINATES for */ 
srand((unsigned)time(0)); 
*py=rand()%21+2; /* PUTTING A RANDOM NUMBER */ 
if(ch==UPARR){ 
if((*px==x[0])&(*py==y[0]-1)) 
allowed=0; 
} 
else if(ch==DOWNARR){ 
if((*px==x[0])&(*py==y[0]+1)) 
allowed=0; 
} 
else if(ch==LEFTARR){ 
if((*px==x[0]-1)&(*py==y[0])) 
allowed=0; 
} 
else if((ch==RIGHTARR)&(*px==x[0]+1)&(*py==y[0])) 
allowed=0; 
for(i=0;(i<length)&&allowed;i++) 
if((*px==x[i])&(*py==y[i])) 
allowed=0; 
} /* THE RANDOM NUMBER GENERATED SHOULD NOT BE PUT ON SNAKE'S BODY */ 
srand((unsigned)time(0)); 
*pn=rand()%9+1; /* THE NUMBER */ 
gotoxy(*px,*py); 
putchar(*pn+48); 
gotoxy(x[0],y[0]); 
} 


char getkey(char old_ch,char ch) 
{ 
char i; 


if(kbhit()) 
for(i=0;i<5;i++){ /* if i too low, takes too many keystrokes */ 
while((ch=getch())==0); 
if(ch==27){ 
/* out=2; 
i=5; 
break;*/return ch; 
} 
if((ch!=LOAD)&(ch!=SAVE)&(ch!=UPARR)&(ch!=DOWNARR)& 
(ch!=LEFTARR)&(ch!=RIGHTARR)) 
continue; 
if((ch!=old_ch)|(!kbhit())) 
break; 
} 
else 
for(i=0;(i<12)&(!kbhit());i++) 
delay(100); 
return ch; 
} 


void savegame(char *px,char *py,int length,char ch) 
{ 
FILE *fp; 
int i; 


rename("snake.sav","snake.bak"); 
fp=fopen("snake.sav","wb"); 
fprintf(fp,"%d %c",length,ch); 
for(i=0;i<length;i++) 
fprintf(fp,"%c%c",px[i],py[i]); 
fclose(fp); 
} 


int loadgame(char *px,char *py,char *pch) 
{ 
FILE *fp; 
int length,i; 


fp=fopen("snake.sav","rb"); 
if(!fp){ 
clrscr(); 
puts("ERROR: no saved game found in current directory!!!\n\n\t\t" 
"Exiting...\n"); 
sleep(3); 
exit(1); 
} 
window(2,2,79,22); 
clrscr(); 
/* fscanf(fp,"%d %c ",&length,pch);*/ 
fscanf(fp,"%d %c",&length,pch); 
for(i=0;i<length;i++){ 
/* fscanf(fp,"%d %d ",&px[length],&py[length]);*/ 
fscanf(fp,"%c%c",&px[i],&py[i]); 
gotoxy(px[i]-1,py[i]-1); 
putchar('Û'); 
} 
window(1,1,80,25); 
gotoxy(30,24); 
delline();delline(); /* REMOVING MESSAGE */ 
cprintf("\n( EAT THE NUMBER !! ) Score = %5d",length-6); 
gotoxy(px[0],py[0]); 
printf("\b"); 
fclose(fp); 
return length; 
} 


void win_message() 
{ 
window(1,1,80,25); 
gotoxy(1,24); 
delline();delline(); 
textcolor(14); 
cprintf("CONGRATULATION!! YOU HAVE COMPLETED THE GAME!!\r\n" 
"(Press any key to terminate...)"); 
clrscr(); 
textcolor(7); 
} 
//cscanf: WHEN YOU PRESS ENTER, CURSOR MOVES TO BEGINNING OF current LINE!!
