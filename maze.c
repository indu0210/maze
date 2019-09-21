#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>

#define MA 256
#define n 16
// MA is the maximum size of the stack
// n is the size of the array

int stack[MA], top = -1;
void print(int a[n][n], int);

//push function
void push(int item){
  top = top + 1;
  stack[top] = item;
}

//pop function
int pop(){
 int item;
 item = stack[top];
 top = top - 1;
 return(item);
}

//MAIN starts here
int main(){
 int m = 1;
 int i, j;
 srand(time(NULL));
 int a[n][n] = {0};
 for(i = 0; i < n; i++){
  for(j = 0;j< n;j++){
   a[i][j] = (rand()* ((i+j) %2))%2;
  }
 }
 print(a,0);
 i = j = 0;
// condition to check if first box is blocked

 if(a[i][j] != 0){
  print(a,1);
  exit(0);
 }
 push (i);
 push (j);
 a[i][j] = 2;

 // Path finding starts here
 while(m < 2000){
  m++;
  // checking right
  if(a[i][j+1] == 0&&j < n -1){
   j++;
   a[i][j] = 2;
   push(i);
   push(j);
   print(a,0);
  }
  //checking down
  else if(a[i+1][j] == 0&&i < n-1){
   i++;
   a[i][j] = 2;
   push(i);
   push(j);
   print(a,0);
  }
  //checking left
  else if(a[i][j-1] == 0 && j > 0){
   j--;
   a[i][j] = 2;
   push(i);
   push(j);
   print(a,0);
  }
  //checking up
  else if(a[i-1][j] == 0 && i > 0){
   if(i == 0 && j == 0){
   print(a,0);
    printf("No path\n");
    print(a,1);
    break;
   }
   i--;
   a[i][j] = 2;
   push(i);
   push(j);
   print(a,0);
  }
  //backtraking starts here
  else if ((a[i][j+1]!= 0 && a[i+1][j] != 0 && a[i-1][j] != 0 && a[i][j-1] != 0) || i != 0 || j != 0){
   j = pop();
   i = pop();
   a[i][j] = 3;
   print(a,0);
  }
  //when it reaches first position
  else if(i <= 0 && j <= 0){
    print(a,0);
    printf("No path found \n");
    print(a,1);
    exit(0);  
  }
  //printing final maze
  if(i >= n-1 && j >= n-1){
   print(a,2);
   exit(0);
  }
 }
 if(i >= n-1 && j >= n-1){
 print(a,2);
 exit(0);
 }
}
void print(int a[n][n], int done){
 int gd = DETECT,gm,left=10,top=30,right=25,bottom=45;
 initgraph(&gd,&gm,NULL);
 int i, j, N = n;
 for(i =0; i < N; i++){
 for(j = 0; j < N; j++){
      if(a[i][j] == 0){
        setcolor(WHITE);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(5);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }else if(a[i][j] == 1){
        setcolor(RED);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(13);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }else if(a[i][j] == 2){
        setcolor(1);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(5);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
      else if(a[i][j] == 3){
        setcolor(14);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(5);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
  }
 }
  if(done == 1){
    outtextxy(left, 10, "NO PATH FOUND");
    delay(9000);
  }else if(done == 2){
    outtextxy(left, 10, "PATH FOUND");
    delay(10000);
  }else{
    outtextxy(left, 10, "PROCESSING.....");
    delay(250);
  }

  closegraph();
}
