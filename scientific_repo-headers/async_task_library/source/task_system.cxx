
#include <atl/task_system.hxx>

namespace atl
{
    namespace
    {
        auto run_thread (task_queue& queue) -> void
        {
            while (true)
            {
                auto task = queue.pop();

                if (task)
                {
                    std::invoke(*task);
                }
                else
                {
                    break;
                }
            }
        }
    }

    task_system::task_system ()
    {
        const auto thread_count = std::thread::hardware_concurrency();

        for (auto i = 0uL; i != thread_count; ++i)
        {
            threads.emplace_back([this] () { run_thread(queue); });
        }
    }

    task_system::~task_system ()
    {
        queue.finish();

        for (auto& thread : threads)
        {
            thread.join();
        }
    }
}
