#pragma once
#include <cstdint>
#include <stdint.h>
#include <string>
#include <concepts>
#include <type_traits>

namespace gui {

    enum class ValueType {
        Int,
        Float,
        String,
        Pointer,
        None,
    };

    class Value {
    private:
        ValueType   type_;
        struct {
            union {
                int64_t ival;
                double  fval;
                void*   ptr;
            };
            std::string sval;
        };
    public:
        Value()
            : type_(ValueType::None)
        {}

        template<class T>
        requires std::integral<T>
        Value(T val)
            : type_(ValueType::Int)
            , ival((int64_t)val)
        {}

        template<class T>
        requires std::integral<T>
        operator T () const {
            return T(ival);
        }

        template<class T>
        requires std::floating_point<T>
        Value(T val)
            : type_(ValueType::Float)
            , fval((double)val)
        {}

        template<class T>
        requires std::floating_point<T>
        operator T () const {
            return T(fval);
        }

        template<class T>
        requires std::same_as<std::string, T>
        Value(T&& val)
            : type_(ValueType::String)
            , sval(std::forward(val))
        {
        }

        std::string const& stringVal() const {
            return sval;
        }

        template<class T>
        requires std::is_pointer_v<T>
        Value(T val)
            : type_(ValueType::Pointer)
            , ptr(val)
        {
        }

        template<class T>
        requires std::is_pointer_v<T>
        operator T () const {
            return T(ptr);
        }

    };

}