CMakeComponents
=

CMakeComponents is a proof-of-concept project demonstrating compile-time type-id system via CMake macro
definitions.

Usage
-

Used components are listed in top-level CMakeLists before string manipulation commands, which parse the
component list into the macro definitions passed to engine target. The macros are defined to public interface
of the engine library, so the macros are defined in any target linking the engine library.

```
set(COMPONENT_TYPES "${COMPONENT_TYPES} Type1Component Type2Component")
```

Component types can also be scanned automatically by setting the `SCAN_COMPONENTS` CMake option ON. This feature
generates component type from every header file with ending `Component.hpp`.

The type ids can be queried by including `engine/TypeId.hpp` and calling `TypeId::typeId` with the desired type
as template parameter:

```
#include <engine/TypeId.hpp>

int main(void) {
    printf("Type1Component id: %ld\n", TypeId::typeId<Type1Component>());
    return 0;
}
```

When trying to query type id for a type that is not listed in CMakeLists.txt, a static_assert fails and provides
a compile error similar to (in this example listing of `Type4Component` has been forgotten):

```
In file included from .../src/app/main.cpp:4:0:
.../include/engine/TypeId.hpp: ...
.../include/engine/TypeId.hpp:38:51:   ...
.../include/engine/TypeId.hpp:38:51:   ...
.../include/engine/TypeId.hpp:46:42:   required from 'static constexpr int64_t TypeId::typeId() [with T_Component = Type4Component; int64_t = long long int]'
.../src/app/main.cpp:19:72:   required from here
.../include/engine/TypeId.hpp:29:9: error: static assertion failed: Component auto-scan was unable to find the component type. Please make sure that component types are defined individually in headers with *Component.hpp postfix.
         static_assert(IdRegistered<T_Component>::value,
         ^~~~~~~~~~~~~
```