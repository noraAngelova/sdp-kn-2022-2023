#include "static_stack.hpp"
#include "resizable_stack.hpp"
#include "linked_stack.hpp"

//using IntStack = Stack<int>;
//using IntStack = RStack<int>;
using IntStack = LinkedStack<int>;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack_tests.h"
