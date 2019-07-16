#include <cstdio>
#include <engine/Type1Component.hpp>
#include <engine/Type2Component.hpp>
#include <engine/TypeId.hpp>
#include "Type3Component.hpp"
#include "Type4Component.hpp"

#define STRX(...) STR(__VA_ARGS__)
#define STR(...) #__VA_ARGS__


int main()
{
    printf("Registered components: %s\n", STRX(COMPONENT_TYPES));
    printf("Forward declaration macro: %s\n", STRX(COMPONENT_FORWARD_DECLARATIONS));
    printf("Type1Component id: %lld\n", TypeId::typeId<Type1Component>());
    printf("Type2Component id: %lld\n", TypeId::typeId<Type2Component>());
    printf("Type3Component id: %lld\n", TypeId::typeId<Type3Component>());
    printf("Type4Component id: %lld\n", TypeId::typeId<Type4Component>());
    return 0;
}
