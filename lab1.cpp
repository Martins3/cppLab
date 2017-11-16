//
// Created by martin on 17-11-14.
//


//
// Created by martin on 17-10-12.
//

#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
struct STKP{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
void initSTKP(STKP *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTKP(STKP *const p, const STKP&s); //用栈s初始化p指向的栈
int  size (const STKP *const p);		//返回p指向的栈的最大元素个数max
int  howMany (const STKP *const p);	//返回p指向的栈的实际元素个数pos
int  getelem (const STKP *const p, int x);	//取下标x处的栈元素
STKP *const push(STKP *const p, int e); 	//将e入栈，并返回p
STKP *const pop(STKP *const p, int &e); 	//出栈到e，并返回

STKP *const assign(STKP*const p, const STKP&s); //赋s给p指的栈,并返回p
void print(const STKP*const p);				//自底至顶打印p指向的栈所有元素
void destroySTKP(STKP*const p);			//销毁p指向的栈

//---------------------------------------------------------------------------

void initSTKP(STKP *const p, int m){
    p->elems = new int[m];  //
    p->max = m;
    p->pos = 0;
}
//初始化p指向的栈：最多m个元素


void initSTKP(STKP *const p, const STKP&s){
    p->elems = new int[s.max];  //
    for (int i = 0; i < s.max; ++i) {
        p->elems[i] = s.elems[i];
    }
    p->max = s.max;
    p->pos = 0;

}
//用栈s初始化p指向的栈


int  size (const STKP *const p){
    return p->max;
}
//返回p指向的栈的最大元素个数max

int  howMany (const STKP *const p){
    return p->pos;
}//返回p指向的栈的实际元素个数pos


int getelem (const STKP *const p, int x){
    if( x < 0 || x >= p->max) throw invalid_argument( "received negative value" );
    return p->elems[x];
}	//取下标x处的栈元素


STKP *const push(STKP *const p, int e){
    if(p->pos == p->max){
        throw invalid_argument("the stack is full");
    }
    p->elems[p->pos] =  e;
    p->pos ++;
    return  p;

} 	//将e入栈，并返回p
STKP *const pop(STKP *const p, int &e){
    if(p->pos == 0){
        throw invalid_argument("the stack is full");
    }
    e = p->elems[p->pos - 1];
    p->pos --;
    return p;
}	//出栈到e，并返回p


STKP *const assign(STKP*const p, const STKP&s){
    delete [] p->elems;
    p->elems = new int[s.max];
    for (int i = 0; i < s.pos; ++i) {
        p->elems[i] = s.elems[i];
    }

    p->max = s.max;
    p->pos = s.pos;
    return p;
} //赋s给p指的栈,并返回p


void print(const STKP*const p){
    for (int i = 0; i < p->pos; ++i) {
        cout  << p->elems[i] << "  ";
    }
}		//自底至顶打印p指向的栈所有元素


void destroySTKP(STKP*const p){
    delete p->elems;
}			//销毁p指向的栈

int main(int argc, char* argv[]){
    // 创建读入的标准模板实现
//    freopen("U201514545_6.txt","w",stdout);
    char stage = 'X'; // 初始化不和任何匹配
    STKP * container = new STKP;
    STKP * other = new STKP;

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
                if(index > howMany(container) || index < 1){
                    cout << "E";
                    cout << "  ";
                    breaking = true;
                    break;
                }
                cout << getelem(container, index);
                cout << "  ";
                stage = 'X';
                break;
            case 'S':
                initSTKP(container, stoi(argv[i]));
                cout << "S";
                cout << "  ";
                cout << size(container);
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
                        if(size(container) <= howMany(container)){
                            breaking = true;
                            break;
                        }
                        push(container, k);
                    }
                    if(breaking){
                        cout << "E";
                        break;
                    }
                    inputs.clear();
                    print(container);
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
                if(output_times > howMany(container)){
                    cout << "E";
                    breaking = true;
                    break;
                }
                for (int j = 0; j < output_times; ++j) {
                    int temp;
                    pop(container, temp);
                }
                print(container);
                stage = 'X';
                break;
            case 'A':
                // 首先创建一个相应大小的container ,然后进行赋值

                other_size = stoi(argv[i]);
                initSTKP(other, other_size);
                other = assign(other, *container);
                container = other;

                cout << "A";
                cout << "  ";
                print(container);
                stage = 'X';
                break;
            case 'X':
                stage = argv[i][1]; //  需要确保当前必定为command
                switch (stage){
                    case 'C':
                        initSTKP(other, *container);
                        cout << "C";
                        cout << " ";
                        print(container);
                        stage = 'X';
                        break;
                    case 'N':
                        cout << "N";
                        cout << "  ";
                        cout << howMany(container); // 不清楚指针和对象都是可以的吗 ?
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
                if (howMany(container) >= size(container)) {
                    breaking = true;
                    break;
                }
                push(container, k);
            }
            if (breaking) {
                cout << "E";
            } else {
                inputs.clear();
                print(container);
            }
        }
    }
    return 0;
}
