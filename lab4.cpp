//
// Created by martin on 17-11-11.
//

// 很有意思, 需要保证相差为 1

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Queue{
    int  *const  elems;	//申请内存用于存放队列的元素
    const  int   max;	//elems能存放的最大元素个数
    int   head, tail;		//队列头和尾，队列空时head=tail;初始时head=tail=0
public:
    Queue(int m);		//初始化循环队列：elems有m个元素
    Queue(const Queue&s); 			//用队列s拷贝初始化队列
    virtual operator int ( ) const;			//返回队列的实际元素个数
    virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
    virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
    virtual Queue& operator<<(int e); 	//将e入队列,并返回队列
    virtual Queue& operator>>(int &e);	//出队列到e,并返回队列
    virtual Queue& operator=(const Queue&s); //赋s给队列,并返回被赋值的队列
    virtual void print( ) const;			//打印队列
    virtual ~Queue( );					//销毁队列
};


// -------------------------------------------------------------------------------------------------------------------
// 需要m 就是 max , 但是初始化的大小不仅仅在于此

Queue::Queue(int m): head(0), tail(0), elems(new int[m]),max(m - 1){

}

Queue::Queue(const Queue &s): head(s.head), tail(s.tail), elems(new int[s.max + 1]), max(s.max) {
    for (int i = head; i!= tail; i = (i + 1) %(max + 1)) {
        elems[i] = s.elems[i];
    }
} 

int Queue::full() const {
    return tail + 1 == head || (tail == max && head == 0);
}


int Queue::operator[](int x) const {
    if( x < 0 || x > *this) throw invalid_argument( "received negative value or too big" );
    return elems[(x + head) % (max + 1)];
}


Queue &Queue::operator<<(int e) {
    elems[tail] = e;
    tail = (tail + 1) % (max + 1);
    return *this;
}

Queue &Queue::operator>>(int &e) {
    if(head == tail)
        throw invalid_argument("the stack is empty");
    e = elems[head];
    head = (head + 1) % (max + 1);
    return *this;
}

Queue &Queue::operator=(const Queue &s) {
    delete [] elems;
    head = s.head;
    tail = s.tail;



    int** a = const_cast<int **>(&elems);
    *a = new int[s.max];

    int * b = const_cast<int *>(&max);
    *b = s.max;

    for (int i = head; i!= tail; i = (i + 1) %(max + 1)) {
        elems[i] = s.elems[i];
    }
    return *this;
}

void Queue::print() const {
    for (int i = head; i!= tail; i = (i + 1) %(max + 1)) {
        cout << elems[i] << " ";
    }
}

Queue::~Queue() {
    delete [] elems;
}

Queue::operator int() const {
    if(head == tail) return 0;

    if(head < tail) return tail - head;

    if(head > tail) return tail + max + 1 - head;
}


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
    int container_size = 0;


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
                cout << stoi(argv[i]);

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

