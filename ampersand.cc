#include <iostream>
#include <vector>

// Mandatory ampersand demo with templates.
#ifdef DEMO1
static void fn(int) { }

// Example template: pack T object as 1-vector of T.
template <typename T>
std::vector<T> to_1vec(const T& t) {
  std::vector<T> result;
  result.push_back(t);
  return result;
}

int main() {
  auto okay_vec = to_1vec(&fn); // Okay, function pointer passed and
                                // vector of function pointer returned.
  auto fail_vec = to_1vec(fn);  // Error: function "fn" passed as reference to
                                // function. to_1vec tries to return a vector
                                // of plain functions, not function pointers.
  // (Your typical compiler probably won't tell you the real reason it fails).
}
#endif // DEMO1

// Contrived mandatory no-ampersand demo.
#ifdef DEMO2
// We need to make a struct and a function in a namespace for this to work.
namespace Evil {
  struct Thing { };
  void f(Thing) { std::cout << "Called Evil::f(Evil::Thing);\n"; };
}
static void f(int) { };

int main() {
  Evil::Thing thing;
  f(thing);    // Due to ADL, Evil::f is seen through the thing object & called.
  (&f)(thing); // Error: "&f" forces C++ to choose the "wrong" f [f(int)]
               // before C++ sees the thing object that allows it to invoke ADL.
}
#endif // DEMO2

// Contrived different-behavior-on-ampersand demo.
#ifdef DEMO3
// Similar struct/function in namespace pair.
// This time, the struct is convertible to int.
namespace Evil {
  struct Thing { operator int() const { return 42; }};
  void f(Thing) { std::cout << "Called Evil::f(Evil::Thing);\n"; }
}
static void f(int) { std::cout << "Called ::f(int);\n"; }

int main() {
  Evil::Thing thing;
  f(thing);    // ADL chooses Evil::f as above.
  (&f)(thing); // As before, C++ chooses f(int) in global namespace.
               // However, this silently works due to the implicit
               // Thing-to-int conversion.
}
#endif // DEMO3
