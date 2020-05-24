template<class U, class V, class Enable = void>
struct my_trait;

template<class U, class V>
struct my_trait<U, V, typename std::enable_if<sizeof(U) >= sizeof(V)>::type> {
using first = V;
using second = U;
};

template<class U, class V>
struct my_trait<U, V, typename std::enable_if<sizeof(U) < sizeof(V)>::type> {
using first = U;
using second = V;
};