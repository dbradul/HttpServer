#include <thread>
#include <future>
#include <chrono>
#include <memory>


#include "gtest/gtest.h"
#include "common/BlockingQueue.h"

using namespace std;
using namespace std::chrono;

template<typename T>
const T& PeekConst(const BlockingQueue<T>& queue)
{
    return queue.peek();
}

////////////////////////////////////////////////////////
TEST(TestBlockingQueue, BaseTest)
{
    // Arrange
    BlockingQueue<int> queue;

    // Act
    queue.push(42);

    // Assert
    EXPECT_EQ(42, queue.peek());
    EXPECT_EQ(42, PeekConst(queue));
}

////////////////////////////////////////////////////////
TEST(TestBlockingQueue, ThreadTest)
{
    // Arrange
    // Act
    // Assert
    BlockingQueue<int> queue;
    thread t1 ([&]{
        for(size_t i = 0; i<1024; ++i)
        {
            queue.push(i);
        }
    });

    thread t2 ([&]{
        for(size_t i = 0; i<1024; ++i)
        {
            EXPECT_EQ(i, queue.peek());
            queue.pop();
        }
    });

    t1.join();
    t2.join();
}


////////////////////////////////////////////////////////
TEST(TestBlockingQueue, BlockingPeekTest)
{
    // Arrange
    // Act
    BlockingQueue<int> queue;

    auto asyncFuture = std::async(
        std::launch::async,[&] {
            queue.peek();
        }
    );

    // Assert
    EXPECT_EQ(asyncFuture.wait_for(1s), future_status::timeout);

    queue.push(43);
}


////////////////////////////////////////////////////////
TEST(TestBlockingQueue, UniquePtrTest)
{
    // Arrange
    // Act
    BlockingQueue<unique_ptr<int>> queue;
    queue.push(make_unique<int>(42));

    // Assert
    EXPECT_EQ(*queue.peek(), 42);
    auto p  = move(queue.peek());
    auto p2 = move(queue.peek());
    EXPECT_EQ(*p, 42);
    EXPECT_EQ(p2, nullptr);
}
