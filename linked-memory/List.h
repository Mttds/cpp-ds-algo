#pragma once

template <typename T>
class List {
  public:
    const T & operator[](unsigned index); // overload operator [] to access List class like arrays
    void insertAtFront(const T & data);

    // We define this constructor to make sure that head_ is null-initialized.
    List() : head_(nullptr) { }

    // We define a destructor to delete the memory allocated for the ListNode
    // objects when the List is destroyed.
    ~List() {
      // We'll walk through from the head.
      ListNode *thru = head_;
      while (thru != nullptr) {
        // Copy the address that the "thru" pointer has currently.
        ListNode* toDelete = thru;
        // Step the pointer to the "next" pointer of the current node.
        thru = thru->next;
        // Now, finally, we can delete the toDelete pointer. We could not
        // delete it before we stepped away from it above, because we needed
        // the next pointer information first.
        delete toDelete;
        // We don't strictly need to set toDelete to nullptr here because
        // it goes out of scope immediately after, but remember that you
        // should generally do this after deleting a pointer:
        toDelete = nullptr;
      }
    }

  private:
    class ListNode {
      public:
        const T & data;
        ListNode *next;
        ListNode(const T & data) : data(data), next(nullptr) { }
    };

    ListNode *head_;   /*< Head pointer for our List */
    
    ListNode* _find(const T & data);
};

#include "List.cpp"  // Include the template implementation
