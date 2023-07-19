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
        //this->enter();// 放在哪里问题不大
    }
    virtual ~Base(){
        //this->exit();// 不能放在这里，因为会先执行子类的析构，此时loopOver就不会调用到子类了
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
        this->enter();// 在子类里面做这件事
    }
    ~Game(){
        printf("~game\n");
        this->exit();// 必须在子类里面做这件事，否则不会调用到子类的loopOver
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
