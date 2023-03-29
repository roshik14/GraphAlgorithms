#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <cstddef>
#include <utility>

namespace s21 {
class Stack {
 public:
  Stack();
  Stack(const Stack&);
  Stack(Stack&&);
  Stack& operator=(const Stack&);
  Stack& operator=(Stack&&);
  ~Stack();

  int& peek();
  bool empty() const noexcept;
  size_t size() const noexcept;
  void push(const int& value);
  void pop();
  void swap(Stack&) noexcept;

 private:
  struct Node {
    int value;
    Node* next;
  };
  Node* head_;
  void copy_content(Node*, size_t size);
  size_t get_size(Node*) const;
  void init();
  void clear() noexcept;
  void destroy_stack();
};
}  // namespace s21
#endif  // SRC_S21_STACK_H_
