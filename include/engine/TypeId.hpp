//
// Created by Lehdari on 16.7.2019.
//

#ifndef CMAKECOMPONENTS_TYPEID_HPP
#define CMAKECOMPONENTS_TYPEID_HPP


#include <cstdint>
#include <type_traits>


COMPONENT_FORWARD_DECLARATIONS


class TypeId {
private:
    template <typename T_Component>
    struct IdRegistered {
        static constexpr bool value = false;
    };

    template <typename... T_Components>
    struct TypeRegister {};

    template <typename T_Component>
    static constexpr int64_t typeIdPrivate(TypeRegister<>)
    {
        static_assert(IdRegistered<T_Component>::value, COMPONENT_TYPE_ERROR_MESSAGE);
        return -1;
    }

    template <typename T_Component, typename T_FirstComponent, typename... T_RestComponents>
    static constexpr int64_t typeIdPrivate(TypeRegister<T_FirstComponent, T_RestComponents...>) \
    {
        if constexpr (std::is_same<T_FirstComponent, T_Component>::value) return 0;
        else return 1 + typeIdPrivate<T_Component>(TypeRegister<T_RestComponents...>());
    }

    static constexpr TypeRegister<COMPONENT_TYPES> typeRegister = TypeRegister<COMPONENT_TYPES>();

public:
    template <typename T_Component>
    static constexpr int64_t typeId() {
        return typeIdPrivate<T_Component>(TypeId::typeRegister);
    }
};


#endif //CMAKECOMPONENTS_TYPEID_HPP
