#ifndef THREAD_SAFE_QUEUE__THREAD_SAFE_QUEUE_H_
#define THREAD_SAFE_QUEUE__THREAD_SAFE_QUEUE_H_

#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T, typename Container = std::deque<T>>
class ThreadSafeQueue {
 public:
	ThreadSafeQueue();
	ThreadSafeQueue(const ThreadSafeQueue&);
	ThreadSafeQueue& operator=(const ThreadSafeQueue&);

	void Push(const T&);

	bool TryPop(T&);
	void WaitAndPop(T&);

	bool Empty() const;
	size_t Size() const;

	void Clear();
 private:
  using Queue = std::queue<T, Container>;

  Queue queue;
  mutable std::mutex queue_mutex;
  std::condition_variable queue_event;
};

template<typename T, typename Container>
ThreadSafeQueue<T, Container>::ThreadSafeQueue() = default;

template<typename T, typename Container>
ThreadSafeQueue<T, Container>::ThreadSafeQueue(const ThreadSafeQueue& other) {
	std::lock_guard<std::mutex> lock(other.queue_mutex);
	queue = other.queue;
}

template<typename T, typename Container>
ThreadSafeQueue<T, Container>& ThreadSafeQueue<T, Container>::operator=(const ThreadSafeQueue& other) {
  if (this == &other)
	return *this;

  {
	std::lock(queue_mutex, other.queue_mutex);
	std::lock_guard<std::mutex> this_lock(queue_mutex, std::adopt_lock);
	std::lock_guard<std::mutex> other_lock(other.queue_mutex, std::adopt_lock);
	queue = other.queue;
  }
  queue_event.notify_all();
  return *this;
}

template<typename T, typename Container>
void ThreadSafeQueue<T, Container>::Push(const T& val) {
  {
    std::lock_guard<std::mutex> lock(queue_mutex);
    queue.push(val);
  }
  queue_event.notify_one();
}

template<typename T, typename Container>
bool ThreadSafeQueue<T, Container>::TryPop(T& val) {
  std::lock_guard<std::mutex> lock(queue_mutex);

  if (queue.empty())
  	return false;

  val = queue.front();
  queue.pop();
  return true;
}

template<typename T, typename Container>
void ThreadSafeQueue<T, Container>::WaitAndPop(T& val) {
  std::unique_lock<std::mutex> lock(queue_mutex);
  queue_event.wait(lock, [this] { return !queue.empty(); });
  val = queue.front();
  queue.pop();
}

template<typename T, typename Container>
bool ThreadSafeQueue<T, Container>::Empty() const {
  std::lock_guard<std::mutex> lock(queue_mutex);
  return queue.empty();
}

template<typename T, typename Container>
size_t ThreadSafeQueue<T, Container>::Size() const {
  std::lock_guard<std::mutex> lock(queue_mutex);
  return queue.size();
}

template<typename T, typename Container>
void ThreadSafeQueue<T, Container>::Clear() {
  std::lock_guard<std::mutex> lock(queue_mutex);
  while (!queue.empty())
    queue.pop();
}

#endif //THREAD_SAFE_QUEUE__THREAD_SAFE_QUEUE_H_
