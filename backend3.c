#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend3.h"

// record structure
struct record {
  char name[3];
  char number[4];
  struct record * next;
};

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);

#define POOL_SIZE 7

// pool of memory
struct record pool[POOL_SIZE]; //pool[0~6] 구조체 배열이용, 최대 7개의 주소록을 가진다.
struct record * top=pool; // pool is constant, a pointer to the stack top.
                           // pool은 상수이다? 스택의 top부분임.

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; //사용중인 주소록에서 head pointer


void init_pool()  // 그림으로 그려서 이해해보자.
{
  int i;
  struct record *r=pool;  //pool이라는 원소 7개를 가진 배열을 r이 가르키고 있는상황
  struct record *s;

  pool[POOL_SIZE-1].next=NULL;

  for(i=1;i<POOL_SIZE;i++) {
    s=r++;         //???  이렇게 하면 pool을 본딴 리스트가 생성되는 건가?
    s->next=r;     //???  pool의 주소를 node생성할 때 빌려준다.
  }
}


                           // Get a node from the pool.  Returns NULL if pool is empty.
struct record * new_node(){

  struct record *r;
    if(top==NULL){           //overflow test
     // pritnf(" Can’t add. The address book is full!\n ”);
      return NULL;
    }
   r = top;
   top = r->next;
   return r;
}

// Push a node to the pool.
void free_node(struct record *r) //이건 이미 구현되어 있음.
{
  r->next=top;
  top=r;
}


void add(char *name, char *number){
//    data라는 head pointer is existed;

  if(top == NULL)          //            1. 리스트가 꽉차있을 때
     printf("Can't add. The address book is full!\n");
                             //          2. 중복확인 하기 -> 먼저 검색하기 그 후 이름 발견 or ~발견으로 나누자
    struct record *temp =new_node();
    struct record *r;
     r = data;                        //r이 밑에 있다가 다시 맨 위로 올라가게 해준다.

     while(r != NULL){
         if('r->name[0]' <= 'name[0]')    //3. 이름이 더 빠르다면 앞에 삽입 해주기.
            if('r->name[0]' == 'name[0]' && 'r->name[1] <= name[1]')
              if('r->name[0] == name[0]' && 'r->name[1] == name[1] && r->name[2] <= name[2]'){

                  struct record *s = r++;
                  s->next = r;

                  strcpy(temp->name,name); strcpy(temp->number,number);

                  s->next = temp;
                  r->next = temp->next;
                  temp->next = r;
                }
        r = r->next;
     }
     strcpy(r->name,name); strcpy(r->number,number);
}




void search(char name[3])
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))>0)
    r=r->next;
  if(r==NULL || result<0)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
  struct record *s;
  struct record *r = data;

  while(r != NULL){
    s = r++;
    s->next = r;

    if(strcmp(r->name, name)==0){
        s->next = r->next;
        r = top;
    }
    r->next = r;
  }

}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
  if (r==NULL)
    return -1;
  else
    return strncmp(key, r->name, 3);
}

// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list(){
 struct record *r = pool;

  while(r != NULL){
   printf_name(r);
   printf_number(r);
  r = r->next;
  }
}

