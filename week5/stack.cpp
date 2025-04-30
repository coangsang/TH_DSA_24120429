#include <stdio.h>
#include <string.h>

#define MAX_LEN_PER_LINE 17//độ dài tối đa mỗi dòng
typedef struct Node
{
    int key;
    Node *next = nullptr;//thành viên next được gán giá trị mặc định null
} Node;

typedef struct Stack
{
    Node *top = nullptr;//thành viên top được gán giá trị mặc định null
} Stack;

Stack *initializeStack()
{
    Stack *s = new Stack;//cấp phát động bằng toán tử new
    return s;
}

Node *createNode(int key)
{
    Node *new_node = new Node;
    new_node->key = key;//gán key cho thành viên key của new_node 
    return new_node;
}

void push(Stack **s, int key)
{
    if(*s==nullptr) *s = initializeStack();//khởi tạo stack bằng hàm initializeStack() nếu chưa được khởi tạo 
    Node *n = createNode(key);//tạo một node mới có giá trị key được truyền vào bằng hàm createNode()
    n->next = (*s)->top;//trỏ next của n tới top stack
    (*s)->top = n;//trỏ top stack tới n
}


int pop(Stack *s)
{
    if(s==nullptr||s->top==nullptr) return -1;//nếu stack chưa được khởi tạo hoặc đang rỗng: trả về -1;
    else
    {
        int top_val = s->top->key;//gán key của node top vào biến tạm
        Node *temp = s->top;//lưu con trỏ top vào node tạm
        s->top = s->top->next;//trỏ node top sang next
        delete temp;//xóa top cũ
        return top_val;//trả về key top cũ
    }
}

int size(Stack *s)
{
    if(s==nullptr) return -1;

    Node*cur = s->top;
    int count = 0;
    while (cur != nullptr)
    {
        count++;
        cur = cur->next;
    }
    return count;
}

bool isEmpty(Stack *s)
{
    return (s==nullptr||s->top==nullptr);//(stack chưa khởi tạo hoặc rỗng)? true: false
}



void showStack(Node* top, FILE *fo)
{       //đệ quy in ngược từ dưới đáy stack lên đỉnh
    //đưa vào con trỏ node top
    //khi đệ quy qua đáy, các bước đệ quy in key vào buffer fo.
    if(top!=nullptr){
        showStack(top->next,fo);
        fprintf(fo,"%d ",top->key);
    }
}//trỏ s về nullptr

void freeStack(Stack **s)
{
    if(*s==nullptr) return;
    while ((*s)->top != nullptr)
    {
        Node *temp = (*s)->top->next;
        delete (*s)->top;
        (*s)->top = temp;
    }
    *s = nullptr;
}

void stackStatus(Stack *s,FILE*fo){
    if(isEmpty(s))
        fprintf(fo,"EMTPY\n");
    else{
        showStack(s->top, fo);
        fprintf(fo,"\n");
    }
}

int main()
{
    FILE *fi = fopen("input.txt", "r");
    FILE *fo = fopen("output.txt", "w");
    if(fi==nullptr||fo==nullptr){//nếu không mở được file input/output thì return ngay
        printf("KHONG THE MO FILE I/O\n");
        return -1;
    }
    Stack *s=nullptr;//khởi tạo stack *s gán con trỏ
    char buffer[MAX_LEN_PER_LINE];//dùng để lấy một dòng trong luồng fi, độ dài đủ cho kích thước tối đa.

    while (fgets(buffer, MAX_LEN_PER_LINE, fi) != nullptr)//lặp lấy từng dòng vào chuỗi buffer
    {
        if(strlen(buffer)<=1) continue;//trường hợp dòng rỗng
        buffer[strcspn(buffer,"\n")]='\0';//loại '\n' ở cuối chuỗi

        if (strcmp(buffer, "init") == 0){
            freeStack(&s);//giải phóng stack cũ trước khi tạo mới
            s = initializeStack();
        }
        else if (strcmp(buffer, "pop") == 0)
            pop(s);
        else
        {
            //trường hợp push, buffer trỏ tới: "push INT_32",
            //sscanf truyền vào con trỏ buffer+5 tức trỏ tới "INT_32"
            //sscanf: đọc dữ liệu từ chuỗi char* thay vì stdin
            int val;
            sscanf(buffer+5,"%d",&val);
            push(&s,val);
        }
        stackStatus(s,fo);//in vào luồng fo trạng thái stack sau mỗi dòng
    }
    freeStack(&s);
    fclose(fi);
    fclose(fo);
}