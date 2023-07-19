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
        this->enter();
    }
    ~Base(){
        this->exit();
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
    virtual void loopBegin() = 0;
    virtual void loopOver() = 0;
    static void doThread(Base* game){
        game->loopBegin();
        game->loop();
        game->loopOver();
    }
};
class Game :public Base {
public:
    Game(){
        int a = 1;
    }
    void loopBegin()override{
        int begin = 1;		begin += 100;
    }
    void loopOver()override{
        int over = 10;		over += 10;
    }
};
void main()
{
    auto ptr = new Game();
    delete ptr;
}
