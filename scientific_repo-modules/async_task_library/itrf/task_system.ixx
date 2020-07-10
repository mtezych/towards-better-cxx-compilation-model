
export module atl:task_system;

import :task_queue;

namespace atl
{
    export class task_system
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
