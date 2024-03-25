#include <string>
#include <iostream>
#include <vector>

#include "Dictionary.h"

int main() {
  // Initialize a vector 100 elements long, filled with 0 values
  const int V_SIZE = 100;
  std::vector<int> v(V_SIZE, 0);
  // Reassign each item to hold a value matching its index
  for (int i=0; i<V_SIZE; i++) {
    v[i] = i;
  }

  // We'll also create some persistent std::string data items that our tree
  // will be able to store references to safely.
  // (As described above, this is necessary to make the example safely
  // compatible with various compilers according to the C++ standard, since
  // our tree will be storing explicit references to data that is outside of
  // the tree instead of managed by the tree internally. If we pass the
  // quoted string literals to the insert() calls below instead of using
  // these persistent variables, then on some systems, the attempt to store
  // a reference to a temporary string literal will fail.)

  const std::string str_thirty_seven("thirty seven");
  const std::string str_nineteen("nineteen");
  const std::string str_fifty_one("fifty one");
  const std::string str_fifty_five("fifty five");
  const std::string str_four("four");
  const std::string str_eleven("eleven");
  const std::string str_twenty("twenty");
  const std::string str_two("two");
  const std::string str_seven("seven");
  const std::string str_eight("eight");
  const std::string str_six("six");
  const std::string str_five("five");

  // Let's create an inner scoping block here to restrict the lifetime of our
  // tree to be shorter than that of the ints and strings, since the tree
  // will directly reference those items. This way, the ints and strings will
  // be destroyed only after the tree has already gone out of scope at the
  // end, so the tree will be destroyed before the objects that it refers to.
  {
    Dictionary<int, std::string> t;

    // Let's enable conversion from bool to strings "true" and "false"
    // for the std::cout stream. This is just to show that the empty()
    // member function is working.
    std::cout << std::boolalpha;
    std::cout << "Dictionary empty at the beginning? " << t.empty() << std::endl;

    std::cout << "Inserting items..." << std::endl;

    // Note that we insert items here by reference to the actual items in the
    // vector "v" where they reside. The [] indexing operator for std::vector
    // returns a reference.
    t.insert(v[37], str_thirty_seven);
    t.insert(v[19], str_nineteen);
    t.insert(v[51], str_fifty_one);
    t.insert(v[55], str_fifty_five);
    t.insert(v[4], str_four);
    t.insert(v[11], str_eleven);
    t.insert(v[20], str_twenty);
    t.insert(v[2], str_two);

    std::cout << "Dictionary empty after insertions? " << t.empty() << std::endl;
    std::cout << "Current tree contents in order:" << std::endl;
    t.printInOrder();
    std::cout << std::endl;

    std::cout << "Using find to show that 51 has been inserted:" << std::endl;
    std::cout << "t.find(51): " << t.find(51) << std::endl;

    std::cout << "Trying to remove some items:" << std::endl;
    std::cout << "t.remove(11): " << t.remove(11) << " (zero child remove)" << std::endl;
    std::cout << "t.remove(51): " << t.remove(51) << " (one child remove)" << std::endl;
    std::cout << "t.remove(19): " << t.remove(19) << " (two child remove)" << std::endl;

    std::cout << "Current tree contents in order:" << std::endl;
    t.printInOrder();
    std::cout << std::endl;

    try {
      std::cout << "Attempting to find a non-existent item, 51: " << std::endl;
      std::cout << "t.find(51): " << t.find(51) << std::endl;
    }
    catch (const std::runtime_error& e) {
      std::cout << "\nCaught exception with error message: " << e.what() << std::endl;
    }

    try {
      std::cout << "Attempting to remove a non-existent item, 99: " << std::endl;
      std::cout << "t.remove(99): " << t.remove(99) << std::endl;
    }
    catch (const std::runtime_error& e) {
      std::cout << "\nCaught exception with error message: " << e.what() << std::endl;
    }
  }

  {
    Dictionary<int, std::string> t;
    t.insert(v[4], str_four);
    t.insert(v[6], str_six);
    t.insert(v[5], str_five);
    t.insert(v[7], str_sever);
    t.insert(v[8], str_eight);
  }

  std::cout << "Exiting program normally." << std::endl;

  return 0;
}