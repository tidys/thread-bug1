#include <iostream>
#include <stdio.h>
using namespace std;
#include <mutex>
#include <thread>

class Base{
public:
    mutex               _mutex;
    bool				_run = true;
    thread* _thread = nullptr;
    Base(){
        printf("base\n");
        //this->enter();// �����������ⲻ��
    }
    virtual ~Base(){
        //this->exit();// ���ܷ��������Ϊ����ִ���������������ʱloopOver�Ͳ�����õ�������
        printf("~base\n");
    }

    void exit(){
        if (this->_thread) {
            std::unique_lock<std::mutex> lock(_mutex);
            this->_run = false;
            this->_thread->join();
            delete this->_thread;
            this->_thread = nullptr;
        }
    }
    void enter() {
        if (_thread == nullptr) {
            _thread = new thread(doThread, this);
        }
    }

    void loop(){
        while (true) {
            if (!this->_run) { break; }
        }
    }
    virtual void loopBegin() {};
    virtual void loopOver() {};
    static void doThread(Base* game){
        game->loopBegin();
        game->loop();
        game->loopOver();
    }
};
class Game :public Base {
public:
    Game(){
        printf("game\n");
        this->enter();// �����������������
    }
    ~Game(){
        printf("~game\n");
        this->exit();// ��������������������£����򲻻���õ������loopOver
    }
    void loopBegin()override{
        int begin = 1;		begin += 100;
        printf("begin\n");
    }
    void loopOver()override{
        int over = 10;		over += 10;
        printf("over\n");
    }
};
void main()
{
    Base* ptr = new Game();
    system("pause");
    delete ptr;
    system("pause");

}
