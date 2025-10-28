#ifndef THREADPROJ_THREAD_H
#define THREADPROJ_THREAD_H

#include <pthread.h>
#include <iostream>


class Thread {
public:
    Thread() : isAlive(false), thread(0) {}
    virtual ~Thread() {}

    void start() {
        if (!isAlive) {
            isAlive = true;
            if (pthread_create(&thread, nullptr, createHelper, this) != 0) {
                std::cerr << "Thread creation failed" << std::endl;
                isAlive = false;
            }
        }
    }

    void stop() {
        if (isAlive) {
            isAlive = false;
        }
    }

    void join() {
        if (isAlive) {
            pthread_join(thread, nullptr);
            stop();
        }
    }

    pthread_t getId() {
        return thread;
    }

protected:
    virtual void run() = 0;
    virtual void done() {}

    bool isAlive;

private:
    pthread_t thread;

    static void* createHelper(void* arg) {
        Thread* thread = static_cast<Thread*>(arg);
        thread->run();
        thread->isAlive = false;
        thread->done();
        return nullptr;
    }
};

#endif THREADPROJ_THREAD_H