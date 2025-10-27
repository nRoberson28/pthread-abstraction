#ifndef THREADPROJ_THREAD_H
#define THREADPROJ_THREAD_H

#include <pthread.h>
#include <iostream>


class Thread {
public:
    Thread() : isAlive(false) {}
    virtual ~Thread() {}

    void start() {
        if (!isAlive) {
            isAlive = true;
            if (pthread_create(&thread, nullptr, createHelper, this) != 0) {
                std::cerr << "Thread creation failed" << std::endl;
                isAlive = false;
            }
            else {
                threadId = pthread_self();
            }
        }
    }

    void stop() {
        if (isAlive) {
            isAlive = false;
        }
    }

    void join() {
        if (thread) {
            pthread_join(threadId, nullptr);
        }
    }

    pthread_t getId() {
        return threadId;
    }



protected:
    virtual void run() = 0;
    virtual void done() {}

private:
    pthread_t thread;
    pthread_t threadId;
    bool isAlive;

    static void* createHelper(void* arg) {
        Thread* thread = static_cast<Thread*>(arg);
        thread->run();
        thread->isAlive = false;
        thread->done();
        return nullptr;
    }
};

class counter : public Thread {
public:
    counter() {}

protected:
    void run () override {
        for (int i = 0; i < 20; i++) {

        }
    }
};



#endif //THREADPROJ_THREAD_H