//
//  main.c
//  datastructures chap 5 exam 10
//
//  Created by 한설 on 2023/04/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef char Element;
typedef struct LinkedNode { //노드 구조체
    Element data;
    struct LinkedNode* link;
} Node;
typedef struct Stack{   //스택 구조체
    Node* top;
}Stack;


//Stack ADT
void init_stack(Stack *a) {a -> top = NULL;}
int is_empty(Stack *a) {return a -> top == NULL;}
int size(Stack *a);
void push(Stack *a, Element e);
Element pop(Stack *a);
Element peek(Stack *a);
void destroy_stack(Stack *a);
void print_stack(Stack *a, char *msg);

void error(char* str);
void checkAnotherchar(char str[]);
void inputchar(char *str);

int main(int argc, const char * argv[]) {
    Stack a;    //스택 생성
    Element ch; //element 변수 생성
    init_stack(&a);
    int n, count = 0;
    char str[50];
    inputchar(str); //문자열 입력받기
    printf("입력된 문자열: %s", str);
    checkAnotherchar(str);  //공백, 구두점 등 회문 확인에 방해요소 제거
    n = (int)strlen(str);   //글자의 개수 확인
    for(int i = 0; i < n; i++)
    {
        push(&a, str[i]);   //스택에 기입
    }
    for(int i = 0; i < n; i++)
    {
        if (n == 1) //글자가 하나인 경우
        {
            printf("글자가 하나입니다.");
            break;
        }
        ch = pop(&a);   //스택에서 pop한 값 ch에 기입
        if(ch != str[i])    //str의 앞부분에서부터 확인
        {
            printf("회문이 아닙니다.");
            break;
        }
        count += 1; //무사히 넘길 경우 count + 1
    }
    if (count == n) //프로그램이 이상 없이 끝난 경우
        printf("회문입니다.");
    return 0;
}

void error(char* str)
{
    fprintf(stderr, "%s\n", str);
    exit(1);
}

int size(Stack *a)
{
    Node *p;
    int count = 0;
    for (p = a -> top; p != NULL; p = p -> link) count ++;
    return count;
}

void push(Stack *a, Element e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p -> data = e;
    
    p -> link = a -> top;
    a -> top = p;
}

Element pop(Stack *a)
{
    Node *p;
    Element e;
    if (is_empty(a))
        error("스택 공백 에러");
    
    p = a -> top;
    a -> top = p -> link;
    e = p -> data;
    free(p);
    return e;
}

Element peek(Stack *a)
{
    if (is_empty(a))
        error("스택 공백 에러");
    return (a -> top) -> data;
}

void destroy_stack(Stack *a)
{
    while (is_empty(a) == 0)
        pop(a);
}

void print_stack(Stack *a, char *msg)
{
    Node *p;
    printf("%s[%2d]= ", msg, size(a));
    for (p = a -> top; p != NULL; p = p -> link)
        printf("%2d ", p -> data);
    printf("\n");
}

void checkAnotherchar(char str[]) //문자열에서 대문자는 소문자로 바꿔주고 공백, 구두점 등등 삭제.
{
    char *s1;
    int j = 0, n;
    n = (int)strlen(str);   //str문자열의 길이 대입
    s1 = (char*)malloc(sizeof(char) * n);   //메모리 할당
    for(int i = 0; i < n; i++)
    {
        if(!isspace(*(str + i)) && *(str + i) != ',' && *(str + i) != '.' && *(str + i) != '\'')    //공백, 쉼표, 마침표, 작은따옴표를 제외하고
        {
            *(s1 + j) = tolower(*(str + i));    //대문자는 소문자로 바꿔 기입
            j = j + 1;
        }
    }
    strcpy(str, s1);    //str문자열에 s1 대입
    free(s1);   //메모리 반납
}

void inputchar(char *str)   //문자열을 사용자로부터 받기
{
    printf("문장을 입력해주세요.\n");
    fgets(str, 100, stdin);
}
