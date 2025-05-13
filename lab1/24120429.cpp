#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define SYNTAX_ERR_MESSAGE "Error"
#define MATH_ERR_MESSAGE "Error"

string subtract(string a,string b);
string add(string a,string b);
string multiply(string a, string b);
string singleMultiply(string a, char b);
string multiply(string a, string b);
bool areValidBrackets(string expression);
bool isValidOperator(string expression, size_t pos_of_operand);
void removeNegSign(string&a);
bool isNeg(string a);
void swapChar(char&a, char&b);
bool isEmptyQueue(Queue*q);

void swapChar(char&a, char&b){
    char temp = a;
    a = b;
    b = temp;
}

//Xem 1 số có phải là số âm không
bool isNeg(string a){
    return (a[0]=='-');
}

//so sánh 2 số
//so sánh dựa vào độ dài sau đó là thứ tự từ điển
int numCmp(string a, string b){
    size_t len_a = a.length();
    size_t len_b = b.length();

    if(len_a>len_b){
        return 1;
    }
    else if(len_a<len_b){
        return -1;
    }
    else{
        if(a==b) return 0;
        else if(a>b) return 1;
        else return -1;
    }

}

//thêm dấu âm, nếu đã có thì chuyển sang số dương
void addNegSign(string&a){
    if(a[0]=='-'){ 
        removeNegSign(a);
        return;}
    else{
        a.insert(a.begin(),'-');
    }
}
//Xóa dấu âm khỏi số
void removeNegSign(string&a){
    if(a[0]!='-') return;
    else{
        a.erase(a.begin());
    }
}
//đảo ngược chuỗi
void reverseString(string&a){
    size_t left = 0;
    size_t right = a.length()-1;
    while(left<right){
        swapChar(a[left],a[right]);
        left++;
        right--;
    }
}
//xóa toàn bộ số 0 ở đầu, giữ số 0 hợp lệ
void removeZeroAtHead(string &a){
    while(*(a.begin())=='0'&&a.length()>1){
        a.erase(0,1);
    }
}

//hàm add dùng để cộng 2 số
string add(string a, string b){
    size_t len_a = a.length();
    size_t len_b = b.length();

    //Trường hợp a hoặc b = 0
    if(a=="0") return b;
    if(b=="0") return a;

    //a dương b âm => a+b = |a| - |b|, dùng phép trừ
    if(!isNeg(a)&&isNeg(b)){
        removeNegSign(b);
        return subtract(a,b);
    }
    //a âm, b dương => a + b = |b| - |a|, dùng phép trừ
    if(isNeg(a)&&!isNeg(b)){
        removeNegSign(a);
        return subtract(b,a);
    }
    /*a âm b âm =>a + b = -(|a| + |b|),
        cộng phần dương sau đó thêm dấu trừ*/
    if(isNeg(a)&&isNeg(b)){
        removeNegSign(a);
        removeNegSign(b);
        string res = add(b,a);
        addNegSign(res);
        return res;
    }

    //Để thuật toán ngắn gọn, hàm chỉ tính a>b
    //Nếu a<b => gọi lại hàm, đảo vị trí a,b
    if(len_a<len_b){
        return add(b,a);
    }
    
    //Trường hợp a>=b
    /*Sử dụng phương pháp tính toán ở cấp tiểu học
    */
    string c;//Biến lưu kết quả cộng
    int ai = len_a-1;//Biến chỉ số để duyệt ngược số
    int bi = len_b-1;//Biến chỉ số để duyệt ngược số

    int carry = 0;//Biến nhớ

    while(ai>=0){
        /*
            
            Cộng từng chữ số theo cột tương ứng của a và b
            (trừ '0' để chuyển kí tự số ở bảng mã ascii về số nguyên)
            nếu cột chỉ có a, coi cột b = 0;
            lưu kết quả vào biến tạm temp
        */
        int temp = (a[ai--]-'0');
        if(bi>=0){
            temp+=(b[bi--]-'0');
        }


        //Nếu có nhớ, cộng thêm nhớ vào biến tạm temp
        //Đặt lại nhớ = 0;
        if(carry){
            temp+=carry;
            carry = 0;
        }

        //Nếu tổng cột tương ứng 2 số >= 10, ta chỉ lấy số hàng đơn vị
        // vì tối đa tổng là 18 nên -10 là lấy được số hàng đơn vị
        // gán biến nhớ bằng hàng chục (hiển nhiên là 1)
        if(temp >=10){
            carry = 1;
            temp-=10;
        }
        //đẩy temp vào c, (+'0' <=> chuyển sang kí tự số tương ứng ở bảng mã ascii)
        c.push_back(temp + '0');
    }
    //Nếu cộng xong còn nhớ thì thêm vào c,
    if(carry){
        c.push_back('1');
    }
    
    //đảo ngược và xóa các số không dư thừa ở đầu
    reverseString(c);
    removeZeroAtHead(c);
    return c;
}

string subtract(string a, string b){
    //Nếu a = b => kết quả = 0;
    if(numCmp(a,b)==0) return "0";

    //nếu a = 0 => a - b = (-b)
    if(a=="0"){
        if(isNeg(b)){
            removeNegSign(b);
            return b;
        }
        addNegSign(b);
        return b;
    }
    //Nếu b = 0 => a-b=a
    if(b=="0") return a;

    int len_a = a.length();
    int len_b = b.length();
    //Nếu a âm b dương => a - b = - |a| - |b| = -(|a|+|b|)
    if(isNeg(a)&&!isNeg(b)){
        removeNegSign(a);
        string c = add(a,b);
        addNegSign(c);
        return c;
    }
    //Nếu a dương b âm => a - b = (|a|+|b|)
    if(!isNeg(a)&&isNeg(b)){
        removeNegSign(b);
        string c = add(a,b);
        return c;
    }
    //Nếu a âm b âm => a - b = |b| - |a|
    if(isNeg(a)&&isNeg(b)){
        removeNegSign(a);
        removeNegSign(b);
        return subtract(b,a);
    }
    /*So sánh 2 số qua hàm numCmp()
        nếu a<b => a-b = (-(b-a));

    */
    if(numCmp(a,b)==-1){
        string c = subtract(b,a);
        addNegSign(c);
        return c;
    }
    int borrow = 0;
    string c;

    int ai = len_a-1;
    int bi = len_b-1;
    while(ai>=0){
        int temp = (a[ai--]-'0');
        if(bi>=0){
            temp -=(b[bi--]-'0');
        }
        if(borrow){
            temp -=1;
            borrow = 0;
        }
        if(temp<0){
            temp+=10;
            borrow=1;
        }
        c.push_back(temp+'0');
    }
    reverseString(c);
    removeZeroAtHead(c);
    return c;
}

string singleMultiply(string a, char b){
    if(b=='0') return "0";
    if(b=='1') return a;
    string c;
    int len_a = a.length();
    int carry =0;
    int ai=len_a-1;
    int num_b = b - '0';
    while(ai>=0){
        int temp = (a[ai--]-'0')*num_b;
        if(carry){
            temp +=carry;
            carry=0;
        }
        if(temp>=10){
            carry=temp/10;
            temp%=10;
        }
        c.push_back(temp+'0');
    }
    if(carry){
        c.push_back(carry+'0');
    }
    reverseString(c);
    removeZeroAtHead(c);
    return c;
}
void addNTimeZero(string &a, int n){
    while(n--){
        a.push_back('0');
    }
}
string multiply(string a, string b){
    if(a=="0"||b=="0") return "0";
    if(a=="1") return b;
    if(b=="1") return a;
    int len_a = a.length();
    int len_b = b.length();
    if(isNeg(a)&&isNeg(b)){
        removeNegSign(a);
        removeNegSign(b);
        string c = multiply(a,b);
        return c;
    }
    if(isNeg(a)&&!isNeg(b)){
        removeNegSign(a);
        string c = multiply(a,b);
        addNegSign(c);
        return c;
    }
    if(!isNeg(a)&&isNeg(b)){
        removeNegSign(b);
        string c = multiply(a,b);
        addNegSign(c);
        return c;
    }
    int bi = len_b -1;
    string c = "0";
    while(bi>=0){
        string temp = singleMultiply(a,b[bi]);
        addNTimeZero(temp,len_b-1 - bi);
        c = add(c,temp);
        bi--;
    }
    return c;
}

string divide(string a, string b){
    if(b=="0") return "Math ERROR";
    if(b=="1") return a;
    int len_a = a.length();
    int len_b = b.length();
    if(isNeg(a)&&isNeg(b)){
        removeNegSign(a);
        removeNegSign(b);
        return divide(a,b);
    }
    if(isNeg(a)&&!isNeg(b)){
        removeNegSign(a);
        string t_result = divide(a,b);
        addNegSign(t_result);
        return t_result;
    }
    if(!isNeg(a)&&isNeg(b)){
        removeNegSign(b);
        string t_result = divide(a,b);
        addNegSign(t_result);
        return t_result;
    }
    if(numCmp(a,b)==-1) return "0";
    if(numCmp(a,b)==0) return "1";

    string accumulator;
    string result;
   // cout<<"_DIVIDE_START\n";
    for(int i = 0 ;i<len_a;i++){
        accumulator+=(a[i]);
        removeZeroAtHead(accumulator);
        if(numCmp(accumulator,b)==0){
            result.push_back('1');
            accumulator.clear();
        }
        else if(numCmp(accumulator,b)==1){
            int count = 0;
            do
            {
                accumulator = subtract(accumulator,b);
                count++;
            }while(numCmp(accumulator,b)!=-1);
            if(accumulator=="0")
                accumulator.clear();
            result+= to_string(count);
        }
        else
            result.push_back('0');
    }
    removeZeroAtHead(result);
   // cout<<"_RESULT_DIVIDE: "<<result<<endl;
    return result;

}


/*------------------------------------------*/
typedef struct Node{
    string val;
	Node*next=nullptr;
}Node;

typedef struct Stack
{
	Node*top=nullptr;//like head
}Stack;

typedef struct Queue
{
	Node*front=nullptr;//like head
	Node*rear=nullptr;//like tail
}Queue;


Node* createNode(string str){
    Node*n=new Node;
    n->next=nullptr;
    n->val = str;
    return n;
}
//thêm phần tử vào stack
void push(Stack*&s,string data){
    Node*n = createNode(data);
    n->next = s->top;
    s->top = n;
}

//xóa phần tử khỏi stack
string pop(Stack*&s){
    if(s!=nullptr){
        string top_val=s->top->val;
        Node*temp = s->top;
        s->top = s->top->next;
        delete temp;
        return top_val;
    }else{
        cout<<"Stack is empty\n";
        return (string)"\0";
    }
}
//lấy giá trị đỉnh stack
string getTop(const Stack *s){
    if(s!=nullptr){
        return s->top->val;
    }else{
        return "BLANK";
    }
}

//thêm vào đuôi queue
void enqueue(Queue*&q, string data){
    Node*n = createNode(data);
    if(isEmptyQueue(q)){
        q->front=q->rear=n;
    }
    else{
        q->rear->next=n;
        q->rear=n;
    }
}
//xóa phần tử đầu queue
void dequeue(Queue*&q){
    Node*tmp = q->front;
    q->front = q->front->next;
    if(q->rear==tmp){
        q->rear = nullptr;
    }
    delete tmp;
}
//lấy phần tử đầu tiên queue
string getFront(const Queue*q){
    if(q!=nullptr){
        return q->front->val;
    }
    return "Error";
}
//xem stack rỗng không 
bool isEmptyStack(Stack*s){
    return s->top==nullptr;
}
//xem queue rỗng không 
bool isEmptyQueue(Queue*q){
    return q->front==nullptr;
}
//kiểm tra toán hạng
bool isOperand(char c){
    return c>='0'&&c<='9';
}
//kiểm tra toán tử
bool isOperator(char c){
    return c=='+'||c=='-'||c=='*'||c=='/';
}
//kiểm tra xem đây có phải là dấu âm hay không 
bool isUnaryMinus(string expression, size_t pos){
    if(pos==0||pos==expression.length()) return false;
    if(expression[pos-1]=='(') return true;
    return false;
}
//độ ưu tiên của toán tử
int precedence(string m_operator){
    if(m_operator=="+"||m_operator=="-") return 0;
    //
    //if(m_operator=="NEG") return 2;
    return 1;
}
// in ra queue
void displayQueue(const Queue*q){
    if(q->front==nullptr) return;
    Node*t_node = q->front;
    while(t_node!=nullptr){
        cout<<t_node->val<<' ';
        t_node=t_node->next;
    }
    cout<<endl;
}
//in ra stack từ dưới lên
void displayStackRecursion(const Node*top_stack){
    if(top_stack==nullptr){
        return;
    }
    displayStackRecursion(top_stack->next);
    cout<<top_stack->val<<' ';
}
void displayStack(const Stack*s){
    displayStackRecursion(s->top);
    cout<<endl;
}

//giải phóng bộ nhớ stack
void freeStack(Stack*&s){
    if(s!=nullptr){
        while(s->top!=nullptr){
            Node*t_node = s->top;
            s->top = s->top->next;
            delete t_node;
        }
        delete s;
        s=nullptr;
    }
}
//giải phóng bộ nhớ queue
void freeQueue(Queue*&q){
    if(q!=nullptr){
        while(q->front!=nullptr){
            Node*t_node = q->front;
            q->front=q->front->next;
            delete t_node;
        }
        delete q;
        q=nullptr;
    }
}

/*Xóa các dấu cách (space) trong chuỗi
    Trong quá trình xóa, kiểm tra nhanh tính hợp lệ của toán hạng, toán tử
*/
void removeSpace(string &s){
    size_t pos = 0;
    while((pos=s.find(' ',pos))!=string::npos){
        //cout<<pos<<" of "<<s.length()<<endl;
        if(pos!=0&&pos!=s.length()){
            //Xem 2 bên dấu cách có hợp lệ không 
            if((isOperand(s[pos-1])&&isOperand(s[pos+1]))
                ||(isOperator(s[pos-1])&&isOperator(s[pos+1]))){
                s = SYNTAX_ERR_MESSAGE;
                return;
            }
        }
        s.erase(s.begin()+pos);
        if(pos!=0){
            pos--;
        }
    }
}
 


void infixToPostfix(string& expression,Stack *&s, Queue *&q){

    /*
    Duyệt từ đầu đến cuối biểu thức(expression)
    Tự định nghĩa trạng thái 'âm' của 1 toán hạng là 'NEG'
    */
    //xóa toàn bộ dấu cách
    removeSpace(expression);
    if(expression==SYNTAX_ERR_MESSAGE||expression==MATH_ERR_MESSAGE){
        return;
    }
    //Kiểm tra các dấu ngoặc có hợp lệ hay không (nếu có)
    if(!areValidBrackets(expression)){
        expression = SYNTAX_ERR_MESSAGE;
        return;
    }
    size_t index = 0;
    size_t len = expression.length();
    while(index<len){
        if(isOperator(expression[index])){
            if(expression[index]=='-'){
                if(isUnaryMinus(expression,index)==1){
                    push(s,"NEG");
                    //không cần kiểm tra ưu tiên vì nó luôn được bọc trong ()
                    //tức trước nó luôn là ( trong stack.
                    index++;
                    continue;
                }
            }
            if(!isValidOperator(expression,index)){
                expression = SYNTAX_ERR_MESSAGE;
                return;
            }
            string t_operator(1,expression[index]);
            if(!isEmptyStack(s) &&(precedence(t_operator)<=precedence(getTop(s)))){
                while(!isEmptyStack(s)&&getTop(s)!="("){
                    string top_stack = getTop(s);
                    enqueue(q,top_stack);
                    pop(s);
                }
            }
            push(s,t_operator);
        }
        if(isOperand(expression[index])){
            size_t pos_end_operand = expression.find_first_of("+-*/)",index);
            if(pos_end_operand==string::npos)
                pos_end_operand = len;
            //cout<<"_POS_END_OPERAND_OF_"<<index<<"_IS_"<<pos_end_operand<<endl;
            //>iterator:: [begin()+index-->begin()+pos_end)
            string t_operand(expression.begin()+index,
                            expression.begin()+pos_end_operand);
            //gán giá trị của toán hạng bằng string::iterator từ expression

            enqueue(q,t_operand);
            //đưa index tới điểm ngay sau khi giá trị toán hạng dừng lại
            index = pos_end_operand;
            continue;
        }

        if(expression[index]=='('){
            if(index!=0&&isOperand(expression[index-1])){
                expression = SYNTAX_ERR_MESSAGE;
                return;
            }
            string t_bracket(1,'(');
            push(s,t_bracket);
        }
        if(expression[index]==')'){
            while(!isEmptyStack(s)&&getTop(s)!="("){
                string top_stack = getTop(s);
                enqueue(q,top_stack);
                pop(s);
            }
            if(!isEmptyStack(s)&&getTop(s)=="("){
                pop(s);
            }        
        }
        index++;
    }
    //_END_TASK01_INFIX_TO_POSTFIX
    while(!isEmptyStack(s)){
        string top_stack = s->top->val;
        enqueue(q,top_stack);
        pop(s);
    }
    //_END_INFIX_TO_POSTFIX
}

string evaluatePostfix(Queue*&q){
    Stack*t_stack = new Stack;
    while(!isEmptyQueue(q)){
        //lấy đầu hàng đợi
        string front_queue = getFront(q);
        dequeue(q);
        if(isOperand(front_queue[0])){
            push(t_stack,front_queue);
        }
        else if (front_queue=="NEG")
        {
            string top_stack = getTop(t_stack);
            pop(t_stack);
            addNegSign(top_stack);
            push(t_stack,top_stack);
        }
        else{
            string t_operand_a = getTop(t_stack);
            pop(t_stack);
            string t_operand_b = getTop(t_stack);
            pop(t_stack);
            string t_result;
            if(front_queue=="/"){
                //lỗi chia 0
                if(t_operand_a=="0") {   
                    freeStack(t_stack);
                    freeQueue(q);
                    return MATH_ERR_MESSAGE;
                }
                t_result = divide(t_operand_b,t_operand_a); 
            }
            else if(front_queue=="*"){
                t_result = multiply(t_operand_b,t_operand_a); 
            }
            else if(front_queue=="+"){
                t_result = add(t_operand_b,t_operand_a); 
            }
            else{
                t_result = subtract(t_operand_b,t_operand_a); 
            }
            push(t_stack,t_result);
        }
    }
    string result = t_stack->top->val;
    pop(t_stack);
    //stack chưa rỗng -> lỗi
    if(!isEmptyStack(t_stack)){
        result = SYNTAX_ERR_MESSAGE;
    }
    freeStack(t_stack);//Giải phóng bộ nhớ
    freeQueue(q);//Giải phóng bộ nhớ
    return result;
}

//Xem các dấu ngoặc trong biểu thức có khớp hay không 
bool areValidBrackets(string expression){
    if(expression.find('(',0)==string::npos&&expression.find(')',0)==string::npos){
        return true;
    }
    if(expression.find('(',0)!=string::npos&&expression.find(')',0)==string::npos){
        return false;
    }
    if(expression.find('(',0)==string::npos&&expression.find(')',0)!=string::npos){
        return false;
    }
    Stack*m_stack=new Stack;
    size_t pos = 0;
    while((pos = expression.find_first_of("()",pos))!=string::npos){
        string t_bracket(1,expression[pos]);
        if(t_bracket=="("){
            if(pos!=0&&isOperand(expression[pos-1]))
            {
                return false;
            }
            push(m_stack,t_bracket);
        }
        else{
            if(isEmptyStack(m_stack)){
                return false;
            }
            else{
                if(pos!=0&&isOperator(expression[pos-1]))
                {
                    return false;
                }
                pop(m_stack);
            }
        }
        pos++;
    }
    if(!isEmptyStack(m_stack)){
        return false;
    }
    return true;
}

//Xem toán tử có hợp lệ hay không

bool isValidOperator(string expression, size_t pos_of_operand){
    if(pos_of_operand==0||pos_of_operand==expression.length()-1){
        return false;
    }
    if(isOperand(expression[pos_of_operand-1])&&isOperand(expression[pos_of_operand+1])){
        return true;
    }if(expression[pos_of_operand-1]==')'||expression[pos_of_operand+1]=='(')
        return true;
    return false;
}


int main(int argc,char*argv[]){

    string input_file_path = argv[1];
    string  output_file_path = argv[2];
    
    ifstream input(input_file_path);
    ofstream output(output_file_path);
    if(!input.is_open()){
        cout<<"Tep dau vao khong ton tai!!\n";
        return -1;
    }
    
    string expression;
    while(getline(input,expression)){
        Stack*s=new Stack;
        Queue*q= new Queue;
        if(expression.length()==0){
            //dòng trống thì mình có in lỗi không nhỉ
            output<<SYNTAX_ERR_MESSAGE<<endl;
            cout<<SYNTAX_ERR_MESSAGE<<endl;
            continue;
        }
        infixToPostfix(expression,s,q);
        //displayQueue(q);
        if(expression==SYNTAX_ERR_MESSAGE||expression==MATH_ERR_MESSAGE){
            output<<expression<<endl;
            cout<<expression<<endl;
            continue; 
        }
        if(isEmptyQueue(q)){
            output<<SYNTAX_ERR_MESSAGE<<endl;
            cout<<SYNTAX_ERR_MESSAGE<<endl;
        }
        else{
            string result = evaluatePostfix(q);
            output<<result<<endl;
            cout<<result<<endl;
        }
    }
    input.close();
    output.close();
    return 0;
}