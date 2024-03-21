
#include <cstdint>
using namespace std;

namespace libex
{
    namespace Perf
    {
        class IMemory_Info
        {

            uint64_t system_memory;
            uint64_t free_memory;
            uint64_t memory_in_use;

            public:
            virtual ~IMemory_Info() = default;
            virtual void update() = 0;
        };

        
        
    }
}