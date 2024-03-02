# LinkedList

## About Templates in Header Files

You’ll notice that much of the code for this assignment is contained in header files instead of cpp files. That’s
because templated C++ code generally needs to be written entirely in header files; when you use templates, the
compiler generates specific versions of the templated code at compile time, depending on how you tried to
apply the template in your code. In order for the compiler to use the template, it first needs to know about the
entire template, which is usually done by putting all the relevant parts in the header. There are complicated
tricks that programmers can use to move some parts of the template into cpp files for faster recompilation, but
we’ll overlook that for this assignment.
