
#ifndef ATL_TASK_QUEUE
#define ATL_TASK_QUEUE

#include <deque>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <utility>
#include <optional>

namespace atl
{
    class task_queue
    {
    private:
        std::deque<std::function<void()>> tasks;
        std::mutex                        mutex;
        std::condition_variable           ready;
        bool                              done { false };

    public:
        auto finish () -> void;

        auto pop () -> std::optional<std::function<void()>>;

        template <typename callable>
        auto push (callable&& task) -> void
        {
            {
                auto lock = std::lock_guard<std::mutex> { mutex };
                tasks.emplace_back(std::forward<callable>(task));
            }
            ready.notify_one();
        }
    };
}

#endif
