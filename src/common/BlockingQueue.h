/*******************************************************************
 * BlockingQueue.h
 *
 *  @date: 29-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <memory>


//---------------------------------------------------------------------------------------
template<class T>
class BlockingQueue
//---------------------------------------------------------------------------------------
{
public:
    BlockingQueue();
    ~BlockingQueue();

    void push(const T& elem);
    void push(T&& elem);
    T& peek();
    const T& peek() const;
    void pop();

private:
    mutable std::mutex mMutex;
    mutable std::condition_variable mCondVar;
    std::queue<T> mQueue;
};

//---------------------------------------------------------------------------------------
template<class T>
BlockingQueue<T>::BlockingQueue()
    : mMutex()
    , mCondVar()
    , mQueue()
    //---------------------------------------------------------------------------------------
{
}

//---------------------------------------------------------------------------------------
template<class T>
BlockingQueue<T>::~BlockingQueue()
//---------------------------------------------------------------------------------------
{
}

//---------------------------------------------------------------------------------------
template<class T>
void BlockingQueue<T>::push(const T& elem)
//---------------------------------------------------------------------------------------
{
    std::unique_lock<std::mutex> lock(mMutex);
    mQueue.push(elem);
    mCondVar.notify_one();
}

//---------------------------------------------------------------------------------------
template<class T>
void BlockingQueue<T>::push(T&& elem)
//---------------------------------------------------------------------------------------
{
    std::unique_lock<std::mutex> lock(mMutex);
    mQueue.push(std::move(elem));
    mCondVar.notify_one();
}

//---------------------------------------------------------------------------------------
template<class T>
T& BlockingQueue<T>::peek()
//---------------------------------------------------------------------------------------
{
    return const_cast<T&>(static_cast<const BlockingQueue<T>*>(this)->peek());
}

//---------------------------------------------------------------------------------------
template<class T>
const T& BlockingQueue<T>::peek() const
//---------------------------------------------------------------------------------------
{
    std::unique_lock<std::mutex> lock(mMutex);
    while (0 == mQueue.size())
    {
        mCondVar.wait(lock);
    }

    return mQueue.front();
}

//---------------------------------------------------------------------------------------
template<class T>
void BlockingQueue<T>::pop()
//---------------------------------------------------------------------------------------
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (mQueue.size()>0)
    {
        mQueue.pop();
    }
}

#endif /* BLOCKINGQUEUE_H_ */
