//V
// Created by martin on 17-11-11.
//

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Stack{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
    Stack(int m);		//初始化栈：最多存m个元素
    Stack(const Stack&s); 			//用栈s拷贝初始化栈
    virtual int size ( ) const;			//返回栈的最大元素个数max
    virtual operator int () const;			//返回栈的实际元素个数pos
    virtual int operator[ ] (int x) const;	//取下标x处的栈元素，第1个元素x=0
    virtual Stack& operator<<(int e); 	//将e入栈,并返回栈
    virtual Stack& operator>>(int &e);	//出栈到e,并返回栈
    virtual Stack& operator=(const Stack&s); //赋s给栈,并返回被赋值的栈
    virtual void print( ) const;			//打印栈
    virtual ~Stack( );					//销毁栈
};
// ------------------------------------------------------------------------------------------------------------

Stack::Stack(int m):max(m), pos(0),elems(new int[m]) {

}

Stack::Stack(const Stack &s):max(s.max), pos(s.pos),elems(new int[s.max]) {
    for (int i = 0; i < max; ++i) {
        elems[i] = s.elems[i];
    }
}

int Stack::size() const {
    return max;
}

Stack::operator int() const {
    return pos;
}

int Stack::operator[](int x) const {
    if( x < 0 || x >= pos) throw invalid_argument( "out of boundary" );
    return this->elems[pos - 1 - x];
}

Stack &Stack::operator<<(int e) {
    if(pos > max){
        throw invalid_argument("the stack is full");
    }
    elems[pos] =  e;
    pos ++;
    return  *this;
}

Stack &Stack::operator>>(int &e) {
    if(pos == 0)
        throw invalid_argument("the stack is full");
    e = elems[pos - 1];
    pos --;
    return *this;
}


Stack &Stack::operator=(const Stack &s) {
    delete elems;
    int** a = const_cast<int **>(&elems);
    *a = new int[s.max];

    int * b = const_cast<int *>(&max);
    *b = s.max;

    pos = s.pos;

    for (int i = 0; i < pos; ++i) {
        (*a)[i] = s.elems[i];
    }
    return *this;
}

void Stack::print() const {
    for (int i = 0; i < pos; ++i) {
        cout << " " << elems[i];
    }
}

Stack::~Stack() {
    delete [] elems;
}








class Queue:public Stack{
    Stack  s2;
public:
    Queue(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    Queue(const Queue&s); 			//用队列s拷贝初始化队列
    virtual operator int ( ) const;			//返回队列的实际元素个数
    virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
    virtual int operator[ ](int x)const;   //取下标为x的元素，第1个元素下标为0
    virtual Queue& operator<<(int e);  // 将 e 入队列,并返回队列
    virtual Queue& operator>>(int &e);	//出队列到e,并返回队列
    virtual Queue& operator=(const Queue&s); //赋s给队列,并返回被赋值的队列
    virtual void print( ) const;			//打印队列
    virtual ~Queue( );					//销毁队列
};


// ---------------------------------------------------------------------------------------------------------
Queue::Queue(int m) : Stack(m), s2(m){

}

// 令人窒息的操作
// 只要是使用的s1 就是需要替换
Queue::Queue(const Queue &s): Stack(s), s2(s.s2){

}

Queue::operator int() const {
    return this->Stack::operator int() + s2.Stack::operator int();
}

int Queue::full() const {
    if(size() == this -> Stack::operator int()){
        if(s2 != 0){
            return true;
        }
    }
    return false;
}


int Queue::operator[](int x) const {
    if(x < 0 || x > (*this))
        throw invalid_argument("使用[] 访问出现越界");
    if(x > s2){
        // 对于s1 需要使用反向的查找
        return this -> Stack::operator[](this -> Stack::operator int() - 1 - (x - s2)); // 注意 [] 的含义
    } else{
        // s2 normal
        return s2[x];
    }
}

Queue &Queue::operator<<(int e) {
    if(full()){
        throw invalid_argument("full should be check outside");
    }
    // 首先添加到文件, 如果发现第一个已经满了，添加到第二个中间

    if(this->size() == this -> Stack::operator int()){
        while (this -> Stack::operator int() != 0){
            int a;
            this -> Stack::operator >>(a);
            s2 << a;
        }
    }
    this-> Stack::operator << (e);
    return *this;
}

Queue &Queue::operator >>(int &e) {
    if((*this) == 0){
        throw invalid_argument("the stack is empty");
    }
    if(s2 == 0) {
        while ( this->Stack::operator int()!= 0) {
            int a;
            this -> Stack::operator >> (a);
            s2 << a;
        }
    }
    s2 >> e;
    return *this;
}
// 赋值构造函数
Queue &Queue::operator=(const Queue &s) {
    s2 = s.s2;
    Stack::operator=(s);
}

void Queue::print() const {
    // careful the stack is already been overload
    // what it is improtant is that s2 is more early been added !
    for (int i = 0; i < s2; ++i) {
        cout << s2[i] << " ";
    }

    for (int j = this ->Stack::operator int()  - 1; j >= 0 ; --j) {
        cout << this -> Stack::operator[](j) << " ";
    }

}

Queue::~Queue() = default;


int main(int argc, char* argv[]){
    // 创建读入的标准模板实现
//    freopen("U201514545_6.txt","w",stdout);
    char stage = 'X'; // 初始化不和任何匹配
    shared_ptr<Queue> container;
    shared_ptr<Queue> other;

    // 由于需要在见检查的位置最开始, 所以关于push 是需要使用结构保证和back tracking

    // only two command will leads to E
    vector<int> inputs;

    bool breaking = false;


    int i;
    for ( i = 0; i < argc ; ++i) {
        if(i == 0 ){
            stage = 'F'; // 第一个参数为文件名称 忽略
            continue;
        }

        if(i == 1){
            // 很关注是不是在开始位置不是 -S 的
            stage = 'S';
            continue;
        }

        // S I  O A C  表示当前的状态
        // 读取新的命令的时候 change to another stage, and print what we know  !

        // for S :

        // command over , print the command

        // specially for I : we need to know care about the name if it's command , change the stage
        int other_size;
        int output_times;
        int index;
        string a;

        switch (stage){
            case 'G':
                // same with S O A
                index = stoi(argv[i]);
                cout << "G";
                cout << "  ";
                if(index > *container || index < 1){
                    cout << "E";
                    cout << "  ";
                    breaking = true;
                    break;
                }
                cout << (*container)[index];
                cout << "  ";
                stage = 'X';
                break;
            case 'S':
                container = make_shared<Queue>(stoi(argv[i]));
                cout << "S";
                cout << "  ";
                cout << container -> size();
                cout << " ";
                stage = 'X'; // 进入到选择command的状态
                break;
            case 'I':
                // 在 I 参数任意, 需要含有检测是否为数值
                a = argv[i];
                if(a.length() == 2 && isalpha(a[1])){
                    cout << "I";
                    cout << " ";
                    for(int k: inputs) {
                        if(container -> full()){
                            breaking = true;
                            break;
                        }
                        *container << k;
                    }
                    if(breaking){
                        cout << "E";
                        break;
                    }
                    inputs.clear();
                    container -> print();
                    i -- ;
                    stage = 'X';
                }else{
                    inputs.push_back(stoi(argv[i]));
                }

                break;
            case 'O':
                output_times = stoi(argv[i]);
                cout << "O";
                cout << "  ";
                if(output_times > *container){
                    cout << "E";
                    breaking = true;
                    break;
                }
                for (int j = 0; j < output_times; ++j) {
                    int temp;
                    (*container) >> temp;
                }
                container -> print();
                stage = 'X';
                break;
            case 'A':
                // 首先创建一个相应大小的container ,然后进行赋值

                other_size = stoi(argv[i]);
                other = make_shared<Queue>(other_size);
                other = container;
                container = other;

                cout << "A";
                cout << "  ";
                container -> print();
                stage = 'X';
                break;
            case 'X':
                stage = argv[i][1]; //  需要确保当前必定为command
                switch (stage){
                    case 'C':
                        other = make_shared<Queue>(*container);
                        container = other;
                        cout << "C";
                        cout << " ";
                        container -> print();
                        stage = 'X';
                        break;
                    case 'N':
                        cout << "N";
                        cout << "  ";
                        cout << *container; // 不清楚指针和对象都是可以的吗 ?
                        cout << " ";
                        stage = 'X';
                        break;
                    default:break;
                }
                break;

            default:
                throw invalid_argument("get into some unexpected area");
        }
        if(breaking) break;
        // 添加一条从的遇到错误的情景
    }

    // 如果放置Ｉ 出现在最后的位置上面
    // the reason to get into X is command is over

    if(!breaking) {
        if(stage == 'I') {
            cout << "I";
            cout << " ";
            for (int k: inputs) {
                if (container->full()) {
                    breaking = true;
                    break;
                }
                *container << k;
            }
            if (breaking) {
                cout << "E";
            } else {
                inputs.clear();
                container->print();
            }
        }
    }
    return 0;
}
