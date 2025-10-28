#include <vector>
#include "thread.h"
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

class Counter : public Thread {
public:
    Counter(int start, int end) : startCount(start), endCount(end), finalNumbers(0) {}
    int getEndCount() const { return endCount; }
    int getStartCount() const { return startCount; }
    const std::vector<int>& getFinalNumbers() const { return finalNumbers; }

protected:
    void run () override {
        for (int i = startCount; i <= endCount && isAlive; i++) {
            pthread_mutex_lock(&mutex);
            finalNumbers.push_back(i);
            pthread_mutex_unlock(&mutex);
        }
    }

    void done() override {
        pthread_mutex_lock(&mutex);
        std::cout << "Thread " << this->getId() << " complete... "
                  << "Counted from " << this->getStartCount() << " to " << this->getEndCount << std::endl;
        pthread_mutex_unlock(&mutex);
    }

private:
    int endCount;
    int startCount;
    std::vector<int> finalNumbers;
};

int main() {
    const int NUM_THREADS = 5;
    const int COUNT_TO = 100;
    const int COUNT_PER_THREAD = COUNT_TO / NUM_THREADS;

    std::vector<Counter*> threads;

    for (int i = 0; i < NUM_THREADS; i++) {
        int start = i * COUNT_PER_THREAD + 1;
        int end = (i + 1) * COUNT_PER_THREAD;
        threads.push_back(new Counter(start, end));
        threads[i]->start();
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i]->join();
    }

    std::cout << "\nFinal count in order...\n\n";

    std::vector<int> finalNumbers;

    for (int i = 0; i < NUM_THREADS; i++) {
        const std::vector<int>& threadNumbers = threads[i]->getFinalNumbers();
        finalNumbers.insert(finalNumbers.end(), threadNumbers.begin(), threadNumbers.end());
    }

    std::sort(finalNumbers.begin(), finalNumbers.end());

    for (int i = 0; i < finalNumbers.size(); i++) {
        std::cout << finalNumbers[i] << " ";
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        delete threads[i];
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
