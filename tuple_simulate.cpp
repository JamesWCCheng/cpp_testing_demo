#include <utility>
template<class... Elements> class Tuple;
template<> class Tuple<> {
};
//a partial specializtion for one + another parameters.
template<class Element, class... Elements>
//Tuple<char, int, string> : Tuple<int, string> {mElement = char}
//Tuple<int, string>       : Tuple<string>      {mElement = int}
//Tuple<string>            : Tuple<>            {mElement = string}
//Tuple<>                                       {}
class Tuple<Element, Elements...> : private Tuple<Elements...> {
public:
  Tuple(Element element, Elements... elements)
    //Construct the base class with the argument forwarding.
    : Tuple<Elements...>(std::forward<Elements>(elements)...),
    //forward the element to mElement.
    mElement(std::forward<Element>(element))
  {
  }
  //store the first element.
  Element mElement;
};

template<class... Elements>
Tuple<Elements...> MakeTuple(Elements&&... args) {
  return Tuple<Elements...>(std::forward<Elements>(args)...);
}

//just a declaration no impl.
template<int N, class... Types> class TupleElement;

//The exit expanding condition is the specialization for N = 0.
//N=0 means we are shifting to the right index of what we wanna access.

template<class Type, class... Types>
class TupleElement<0, Type, Types...> {
public:
  typedef Tuple<Type, Types...> tuple_type;
  typedef Type type;
};

//A partial specialization with the typedef chain.....
template<int N, class Type, class... Types>
class TupleElement<N, Type, Types...> : private TupleElement<N - 1, Types...> {
public:
  static_assert(N > 0, "Negative index is invalid");
  typedef typename TupleElement<N - 1, Types...>::tuple_type tuple_type;
  typedef typename TupleElement<N - 1, Types...>::type type;
};
//              [0]   [1]  [2]
//tuple with {char, int, string}
//Pass N=2 to get the "string" element.

//1. N=2, Type=char, Types=int, string.
// typedef typename TupleElement<1, int, string>::tuple_type tuple_type;

//2. N=1, Type=int, Types=string.
// typedef typename TupleElement<0, string>::tuple_type tuple_type;

//3. N=0, Type=string, Types=nothing.
// typedef Tuple<string,> tuple_type;
// typedef string type;


template<int N, class... Elements>
typename TupleElement<N, Elements...>::type &Get(Tuple<Elements...> &t) {
  //super fucking tricky casting.
  //You can follow this.
  //http://i...content-available-to-author-only...e.com/WekKrh
  //Forcely casting to access the right value in the inheritance hierarchy
  return reinterpret_cast<typename TupleElement<N, Elements...>::tuple_type&>(t).mElement;
}

#include <iostream>

int main() {

  auto t = MakeTuple(5566, "Hello, World!", false, 2.0, 2498);

  std::cout << std::boolalpha;
  std::cout << sizeof(t) << std::endl;
  std::cout << Get<0>(t) << std::endl;
  std::cout << Get<1>(t) << std::endl;
  std::cout << Get<2>(t) << std::endl;
  std::cout << Get<3>(t) << std::endl;
  std::cout << Get<4>(t) << std::endl;

  //std::cout << Get<-1>(t) << std::endl;
  return 0;
}
