
#include <atl/task_queue.hxx>

namespace atl
{
    auto task_queue::finish() -> void
    {
        {
            auto lock = std::lock_guard<std::mutex> { mutex };
            done = true;
        }
        ready.notify_all();
    }

    auto task_queue::pop () -> std::optional<std::function<void()>>
    {
        auto lock = std::unique_lock<std::mutex> { mutex };

        ready.wait(lock, [&] () { return !tasks.empty() || done; });

        if (!tasks.empty())
        {
            auto task = std::move(tasks.front());

            tasks.pop_front();

            return task;
        }
        else
        {
            return std::nullopt;
        }
    }
}