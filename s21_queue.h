#ifndef SRC_S21_Queue_H_
#define SRC_S21_Queue_H_

#include <cstddef>

namespace s21 {
class Queue {
  using value_type = int;
  using reference = int&;
  using const_reference = const int&;
  using size_type = size_t;
  struct Node {
    value_type value;
    Node* next;
  };

 public:
  Queue();
  Queue(const Queue&);
  Queue(Queue&&);
  ~Queue();
  Queue& operator=(Queue&&);
  Queue& operator=(const Queue&);
  value_type peek() const;
  bool empty() const noexcept;
  void push(const_reference value);
  void pop();

 private:
  void copy_content(Node*);
  void init();
  void destroy();

 private:
  Node* head_;
  Node* tail_;
};
}  // namespace s21

#endif  // SRC_S21_Queue_H_
