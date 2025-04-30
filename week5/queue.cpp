#include <stdio.h>
#include <string.h>

#define MAX_LEN_PER_LINE 20//độ dài tối đa mỗi dòng


typedef struct Node
{
    int key;
    Node *next = nullptr;
} Node;

typedef struct Queue
{
    Node *front = nullptr;
    Node *rear=nullptr;
} Queue;

Queue* initializeQueue();
void enqueue(Queue *q, int key);
int dequeue(Queue *q);
int size(Queue q);
bool isEmpty(Queue q);
void queueStatus(Queue q,FILE*fo);
void showQueue(Queue q,FILE*fo);

Queue *initializeQueue()
{
    Queue *s = new Queue;
    return s;
}

Node *createNode(int key)
{
    Node *new_node = new Node;
    new_node->key = key;
    return new_node;
}

void enqueue(Queue**q,int key){
    if(*q==nullptr) *q = initializeQueue();//nếu hàng đợi chưa được khởi tạo 
    Node*new_node= createNode(key);
    if((*q)->front==nullptr){//nếu hàng đợi trống
        (*q)->front=(*q)->rear=new_node;
    }else{
        (*q)->rear->next = new_node;
        (*q)->rear = new_node;
    }
}

int dequeue(Queue*q){
    if(q==nullptr||q->front==nullptr)
        return -1;//hàng đợi chưa khởi tạo hoặc đang trống
    else{
        int val = q->front->key;//key cần trả về
        Node*temp = q->front;//địa chỉ node cần xóa
        if(q->front==q->rear)
            q->front = q->rear = nullptr;//có 1 phần tử duy nhất
        else
            q->front = q->front->next;//trỏ front hàng đợi sang node kế tiếp
        delete temp;
        return val;
    }
}
int size(Queue *q){
    if(q==nullptr) return -1;//nếu hàng đợi chưa khởi tạo
    int count = 0;
    Node*cur = q->front;
    while(cur!=nullptr){
        count++;//tăng biến đếm
        cur=cur->next;//dịch sang vị trí tiếp
    }
    return count;
}

bool isEmpty(Queue *q){
    return (q==nullptr||q->front==nullptr);//(Queue chưa khởi tạo hoặc rỗng)?true:false;
}


void queueStatus(Queue *q,FILE*fo){
    if(isEmpty(q))
        fprintf(fo,"EMPTY");
    else{
        Node*cur = q->front;
        while(cur!=nullptr){
            fprintf(fo,"%d ",cur->key);
            cur = cur->next;
        }
    }
    fprintf(fo,"\n");
}

void freeQueue(Queue**q){
    if(*q==nullptr) return;//nếu hàng đợi chưa được khởi tạo
    while((*q)->front!=nullptr){
        Node*temp = (*q)->front->next;  
        delete (*q)->front;
        (*q)->front = temp;
    }
    *q = nullptr;//trỏ hàng đợi về nullptr
}

int main()
{
    FILE *fi = fopen("input.txt", "r");
    FILE *fo = fopen("output.txt", "w");
    if(fi==nullptr||fo==nullptr){
        printf("KHONG THE MO FILE I/O\n");
        return -1;
    }
    Queue*q=nullptr;
    char buffer[MAX_LEN_PER_LINE];//dùng để lấy một dòng trong luồng fi, độ dài đủ cho kích thước tối đa.

    while (fgets(buffer, MAX_LEN_PER_LINE, fi) != nullptr)//lặp lấy từng dòng vào chuỗi buffer
    {
        if(strlen(buffer)<=1) continue;//trường hợp dòng rỗng
        
        buffer[strcspn(buffer,"\n")]='\0';//loại '\n' ở cuối chuỗi

        if (strcmp(buffer, "init") == 0){
            freeQueue(&q);//giải phóng queue cũ
            q = initializeQueue();
        }
        else if (strcmp(buffer, "dequeue") == 0)
            dequeue(q);
        else
        {
            //trường hợp enqueue, buffer trỏ tới: "enqueue INT_32",
            //sscanf truyền vào con trỏ buffer+8 tức trỏ tới "INT_32"
            //sscanf: đọc dữ liệu từ chuỗi char* thay vì stdin
            int val;
            sscanf(buffer+8,"%d",&val);
            enqueue(&q,val);
        }
        queueStatus(q,fo);
       //in vào luồng fo trạng thái queue sau mỗi dòng
    }
    freeQueue(&q);//giải phóng bộ nhớ
    fclose(fi);
    fclose(fo);
}