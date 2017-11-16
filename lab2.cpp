//
// Created by martin on 17-11-14.
//



#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>


class Stack{
    int *const elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
    Stack(int m);
    // 初始化栈：最多m个元素
    Stack(const Stack&s); //用栈s拷贝初始化栈
    int  size ( ) const;		//返回栈的最大元素个数max
    int  howMany ( ) const;	//返回栈的实际元素个数pos
    int  getelem (int x) const;	//取下标x处的栈元素
    Stack& push(int e); 	//将e入栈,并返回栈
    Stack& pop(int &e); 	//出栈到e,并返回栈
    Stack& assign(const Stack&s); //赋s给栈,并返回被赋值的栈
    void print( ) const;		//打印栈
    ~Stack( );				//销毁栈
};
using namespace std;
Stack::Stack(int m):max(m), pos(0),elems(new int[m]){

}

// copy constructor
Stack::Stack(const Stack &s): max(s.max), pos(s.pos), elems(new int[s.max]) {
    for (int i = 0; i < pos; ++i) {
        elems[i] = s.elems[i];
    }
}

int Stack::size() const {
    return max;
}

int Stack::howMany() const {
    return pos;
}

int Stack::getelem(int x) const {
    if( x < 0 || x > this->max) throw invalid_argument( "received negative value" );
    return this->elems[x];
}

Stack &Stack::push(int e) {
    if(pos >= max){
        throw invalid_argument("the stack is full");
    }
    elems[pos] =  e;
    pos ++;
    return  *this;
}

Stack &Stack::pop(int &e) {
    if(pos == 0)
        throw invalid_argument("the stack is full");
    e = elems[pos - 1];
    pos --;
    return *this;
}

Stack &Stack::assign(const Stack &s) {
    delete [] elems;
    int** a = const_cast<int **>(&elems);
    *a = new int[s.max];

    int * b = const_cast<int *>(&max);
    *b = s.max;

    pos = s.pos;

    // 对于数组的元素进行赋值
    for (int i = 0; i < pos; ++i) {
        elems[i] = s.elems[i];
    }
    return *this;
}

void Stack::print() const {
    for (int i = 0; i < pos; ++i) {
        cout << elems[i] << "  ";
    }
}

Stack::~Stack() {
    delete [] elems;
}



int main(int argc, char* argv[]){
    // 创建读入的标准模板实现
//    freopen("U201514545_6.txt","w",stdout);
    char stage = 'X'; // 初始化不和任何匹配
    shared_ptr<Stack> container;
    shared_ptr<Stack> other;

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
                if(index > container ->howMany() || index < 1){
                    cout << "E";
                    cout << "  ";
                    breaking = true;
                    break;
                }
                cout << container -> getelem(index);
                cout << "  ";
                stage = 'X';
                break;
            case 'S':
                container = make_shared<Stack>(stoi(argv[i]));
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
                        // change full 1
                        if(container -> size() <= container ->howMany()){
                            breaking = true;
                            break;
                        }
                        container -> push(k);
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
                if(output_times > container -> howMany()){
                    cout << "E";
                    breaking = true;
                    break;
                }
                for (int j = 0; j < output_times; ++j) {
                    int temp;
                    container -> pop(temp);
                }
                container -> print();
                stage = 'X';
                break;
            case 'A':
                // 首先创建一个相应大小的container ,然后进行赋值

                other_size = stoi(argv[i]);
                other = make_shared<Stack>(other_size);
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
                        other = make_shared<Stack>(*container);
                        container = other;
                        cout << "C";
                        cout << " ";
                        container -> print();
                        stage = 'X';
                        break;
                    case 'N':
                        cout << "N";
                        cout << "  ";
                        cout << container -> howMany(); // 不清楚指针和对象都是可以的吗 ?
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
                if (container -> size() <= container ->howMany()) {
                    breaking = true;
                    break;
                }
                container -> howMany();
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








