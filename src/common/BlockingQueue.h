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

#include <bits/unique_ptr.h>

//---------------------------------------------------------------------------------------
template<class T>
class BlockingQueuePtr
//---------------------------------------------------------------------------------------
{
   public:
      BlockingQueuePtr();
      virtual ~BlockingQueuePtr();

      void push(std::unique_ptr<T> elem);
      std::unique_ptr<T> pop();

   private:
      std::mutex mMutex;
      std::condition_variable mCondVar;
      std::queue<std::unique_ptr<T>> mQueue;
};

//---------------------------------------------------------------------------------------
template<class T>
BlockingQueuePtr<T>::BlockingQueuePtr()
//---------------------------------------------------------------------------------------
{
}

//---------------------------------------------------------------------------------------
template<class T>
BlockingQueuePtr<T>::~BlockingQueuePtr()
//---------------------------------------------------------------------------------------
{
}

//---------------------------------------------------------------------------------------
template<class T>
void BlockingQueuePtr<T>::push(std::unique_ptr<T> elem)
//---------------------------------------------------------------------------------------
{
   std::unique_lock<std::mutex> lock(mMutex);
   mQueue.push(std::move(elem));
   mCondVar.notify_one();
}

//---------------------------------------------------------------------------------------
template<class T>
std::unique_ptr<T> BlockingQueuePtr<T>::pop()
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

////---------------------------------------------------------------------------------------
//template<class T>
//std::shared_ptr<T> BlockingQueue<T>::peek()
////---------------------------------------------------------------------------------------
//{
//   std::unique_lock<std::mutex> lock(mMutex);
//
//   return std::shared_ptr<T>(mQueue.front().get());
//}

#endif /* BLOCKINGQUEUE_H_ */
