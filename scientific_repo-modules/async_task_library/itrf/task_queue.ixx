
export module atl:task_queue;

import std.core;
import std.threading;

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
