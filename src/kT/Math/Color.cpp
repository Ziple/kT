#define KT_TEMPLATE_IMPL
#include <kT/Math/Color.hpp>

namespace kT
{
#if defined(KT_EXTERN_TEMPLATES_SUPPORT)
    template Color< Uint16 >;
    template Color< Uint32 >;
    template Color< Float32 >;
#endif
}