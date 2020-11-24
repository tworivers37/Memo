#include <iostream>
#include <type_traits>

enum class TypeClass
{
    Type1,
    Type2,
    Type3,

    FIRST = Type1,
    LAST = Type3
};

class TypeClassIterator
{
public:
    TypeClassIterator()
        : type_{TypeClass::FIRST}
    {
    }

    TypeClassIterator(TypeClass type)
        : type_{type}
    {
    }

    TypeClassIterator begin()
    {
        return *this;
    }

    TypeClassIterator end()
    {
        type_ = static_cast<TypeClass>(std::underlying_type<TypeClass>::type(TypeClass::LAST) + 1);
        return *this;
    }

    bool operator!=(TypeClassIterator const& type_iterator)
    {
        return type_ != type_iterator.type_;
    }

    TypeClass operator*()
    {
        return type_;
    }

    TypeClassIterator operator++()
    {
        type_ = static_cast<TypeClass>(std::underlying_type<TypeClass>::type(type_) + 1);
        return *this;
    }

    static std::string type_to_string(TypeClass const& type)
    {
        if(type == TypeClass::Type1) return "Type1";
        else if(type == TypeClass::Type2) return "Type2";
        else if(type == TypeClass::Type3) return "Type3";

        return "etc...";
    }

private:
    TypeClass type_;
};

int main()
{
    TypeClassIterator itr;
    for(auto const& type : itr)
    {
        std::cout<<TypeClassIterator::type_to_string(type)<<"\n";
    }

    return 0;
}