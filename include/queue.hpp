#include <queue>
#include <optional>
#include <pthread.h>
using namespace std;


namespace libex
{
    template <typename T>
    class Queue
    {

        private:
        
        std::queue<T> data;
        pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

        public:

        Queue();
        optional<T> dequeue();
        optional<int> enqueue(T data);
        bool is_empty();
    };


    template <typename T>
    libex::Queue<T>::Queue()
    {

    }

    template <typename T>
    bool libex::Queue<T>::is_empty()
    {
        return data.empty();
    }

    template <typename T>
    optional<T> libex::Queue<T>::dequeue()
    {
        int lock_stat = pthread_mutex_trylock(&this->lock);
        if(lock_stat != 0)
        {
            return nullopt;
        }
        if(data.empty())
        {
            return nullopt;
        }
        T to_return = data.front();
        data.pop();
        pthread_mutex_unlock(&this->lock);
        return to_return;
    }

    template <typename T>
    optional<int> libex::Queue<T>::enqueue(T to_push)
    {
        int lock_stat = pthread_mutex_trylock(&this->lock);
        if(lock_stat != 0)
        {
            return nullopt;
        }
        data.push(to_push);
        pthread_mutex_unlock(&this->lock);
        return 0;
    }

}