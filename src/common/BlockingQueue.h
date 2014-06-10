/*******************************************************************
 * BlockingQueue.h
 *
 *  @date: 29 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

template<class T>
class BlockingQueue
{
    public:
        BlockingQueue();
        virtual ~BlockingQueue();

        void push(T elem);
        T pop();
        //T& peek();
        ////const T& peek();

    private:
        std::mutex              mMutex;
        std::condition_variable mCondVar;
        std::queue<T>           mQueue;
};

template<class T>
BlockingQueue<T>::BlockingQueue()
{
    // TODO Auto-generated constructor stub
}

template<class T>
BlockingQueue<T>::~BlockingQueue()
{
    // TODO Auto-generated destructor stub
}


template<class T>
void BlockingQueue<T>::push(T elem)
{
    std::unique_lock<std::mutex> lock(mMutex);
    mQueue.push(elem);
    mCondVar.notify_one();
}

template<class T>
T BlockingQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(mMutex);
    while(0==mQueue.size())
    {
        mCondVar.wait(lock);
    }
    T elem = mQueue.front();
    mQueue.pop();
    return elem;
}

#endif /* BLOCKINGQUEUE_H_ */
