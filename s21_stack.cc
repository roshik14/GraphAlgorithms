#include "s21_stack.h"

using s21::Stack;

Stack::Stack() { init(); }

Stack::Stack(const Stack& other) { *this = other; }

Stack::Stack(Stack&& other) { *this = std::move(other); }

Stack& Stack::operator=(const Stack& other) {
  if (this != &other) {
    destroy_stack();
    init();
    if (!other.empty()) {
      size_t size = other.size();
      int* tmp_arr = new int[size];
      size_t index = 0;
      Node* curr = other.head_;
      while (curr != nullptr) {
        tmp_arr[index++] = curr->value;
        curr = curr->next;
      }
      for (int i = size - 1; i >= 0; i--) push(tmp_arr[i]);
      delete[] tmp_arr;
    }
  }
  return *this;
}

Stack& Stack::operator=(Stack&& other) {
  if (this != &other) {
    this->head_ = other.head_;
    other.head_ = nullptr;
  }
  return *this;
}

Stack::~Stack() { destroy_stack(); }

int& Stack::peek() { return head_->value; }

bool Stack::empty() const noexcept { return head_->next == nullptr; }

void Stack::destroy_stack() {
  if (head_)
    while (!this->empty()) this->pop();
  delete head_;
  head_ = nullptr;
}

size_t Stack::size() const noexcept { return get_size(head_); }

void Stack::pop() {
  if (!empty()) {
    Node* tmp = head_;
    head_ = head_->next;
    delete tmp;
  }
}

void Stack::push(const int& value) {
  Node* next_node = new Node{value, head_};
  head_ = next_node;
}

void Stack::swap(Stack& other) noexcept {
  Stack tmp(*this);
  *this = std::move(other);
  other = std::move(tmp);
}

size_t Stack::get_size(Node* node) const {
  size_t size = 0;
  if (node) {
    while (node->next != nullptr) {
      size++;
      node = node->next;
    }
  }
  return size;
}

void Stack::init() {
  head_ = new Node();
  head_->value = 0;
  head_->next = nullptr;
}

void Stack::copy_content(Node* node, size_t size) {
  int* tmp_arr = new int[size];
  for (size_t index = 0; node->next != nullptr; index++) {
    tmp_arr[index] = node->value;
    node = node->next;
  }
  for (int i = size - 1; i >= 0; i--) push(tmp_arr[i]);
  delete[] tmp_arr;
}