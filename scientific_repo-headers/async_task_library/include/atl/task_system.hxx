
#ifndef ATL_TASK_SYSTEM
#define ATL_TASK_SYSTEM

#include <atl/task_queue.hxx>
#include <vector>
#include <thread>

namespace atl
{
    class task_system
    {
    private:
        std::vector<std::thread> threads;
        task_queue               queue;

    public:
        task_system ();
        ~task_system ();

        template <typename callable>
        auto async (callable&& task) -> void
        {
            queue.push(std::forward<callable>(task));
        }
    };
}

#endif
