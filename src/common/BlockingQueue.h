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
      virtual ~BlockingQueue();

      void push(std::unique_ptr<T> elem);
      std::unique_ptr<T> pop();

   private:
      std::mutex mMutex;
      std::condition_variable mCondVar;
      std::queue<std::unique_ptr<T>> mQueue;
};

//---------------------------------------------------------------------------------------
template<class T>
BlockingQueue<T>::BlockingQueue()
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
void BlockingQueue<T>::push(std::unique_ptr<T> elem)
//---------------------------------------------------------------------------------------
{
   std::unique_lock<std::mutex> lock(mMutex);
   mQueue.push(std::move(elem));
   mCondVar.notify_one();
}

//---------------------------------------------------------------------------------------
template<class T>
std::unique_ptr<T> BlockingQueue<T>::pop()
//---------------------------------------------------------------------------------------
{
   std::unique_lock<std::mutex> lock(mMutex);
   while (0 == mQueue.size())
   {
      mCondVar.wait(lock);
   }

   std::unique_ptr<T> elem = std::move(mQueue.front());
   mQueue.pop();
   return elem;
}

#endif /* BLOCKINGQUEUE_H_ */
