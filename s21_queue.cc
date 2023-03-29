#include "s21_queue.h"

#include <utility>

using s21::Queue;

Queue::Queue() { init(); }

Queue::Queue(const Queue& other) { *this = other; }

Queue::Queue(Queue&& other) { *this = std::move(other); }

Queue::~Queue() { destroy(); }

Queue& Queue::operator=(Queue&& other) {
  if (this != &other) {
    head_ = std::exchange(other.head_, nullptr);
    tail_ = std::exchange(other.tail_, nullptr);
  }
  return *this;
}

Queue& Queue::operator=(const Queue& other) {
  if (this != &other) {
    destroy();
    init();
    copy_content(other.head_);
  }
  return *this;
}

Queue::value_type Queue::peek() const { return head_->value; }

bool Queue::empty() const noexcept { return head_ == nullptr; }

void Queue::destroy() {
  while (!empty()) this->pop();
  head_ = nullptr;
  tail_ = head_;
}

void Queue::pop() {
  if (!empty()) {
    Node* tmp = head_;
    head_ = head_->next;
    delete tmp;
  }
}

void Queue::push(const value_type& value) {
  Node* next_node = new Node{value, nullptr};
  if (empty()) {
    head_ = next_node;
    tail_ = next_node;
  } else {
    tail_->next = next_node;
    tail_ = next_node;
  }
}

void Queue::init() {
  head_ = nullptr;
  tail_ = head_;
}

void Queue::copy_content(Node* node) {
  while (node) {
    push(node->value);
    node = node->next;
  }
}
