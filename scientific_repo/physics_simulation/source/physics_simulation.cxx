
#include <atl/task_system.hxx>

#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <iomanip>

namespace phy_sim
{
    template <typename element_type>
    using array = std::array<element_type, 128>;

    struct vec3
    {
        float x;
        float y;
        float z;
    };

    auto length (const vec3& v) -> float
    {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    auto read_input () -> array<vec3>
    {
        auto vectors = array<vec3> { };

        auto random_device    = std::random_device { };
        auto random_generator = std::mt19937 { random_device() };
        auto distribution     = std::uniform_real_distribution<float> { 0.0, 1.0 };

        const auto random_vec3 = [&] ()
        {
            return vec3 { distribution(random_generator),
                          distribution(random_generator),
                          distribution(random_generator) };
        };
        std::generate(std::begin(vectors), std::end(vectors), random_vec3);

        return vectors;
    }

    auto compute_lengths (const array<vec3>& vectors) -> array<float>
    {
        auto lengths = array<float> { };
        {
            auto task_system = atl::task_system { };

            for (auto task_index = 0uL; task_index < vectors.size(); ++task_index)
            {
                auto task = [task_index, &vectors, &lengths] ()
                {
                    lengths[task_index] = length(vectors[task_index]);
                };
                task_system.async(task);
            }
        }
        return lengths;
    }

    auto print_results (const array<float>& lengths) -> void
    {
        std::cout << std::setprecision(std::numeric_limits<float>::max_digits10);
        std::cout << std::scientific;

        for (const auto& length : lengths)
        {
            std::cout << length << '\n';
        }
    }
}

auto main () -> int
{
    const auto vectors = phy_sim::read_input();

    const auto lengths = phy_sim::compute_lengths(vectors);

    phy_sim::print_results(lengths);

    return 0;
}
