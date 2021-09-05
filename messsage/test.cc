#include <google/protobuf/message.h>
namespace google::protobuf {

Message Foo {
  optional string text = 1;
  repeated int32 numbers = 2;
}

int main() {
  std::string data; // Will store a serialized version of the message.

  // Create a message and serialize it.
  Foo foo;
  foo.set_text("Hello World!");
  foo.add_numbers(1);
  foo.add_numbers(5);
  foo.add_numbers(42);

  foo.SerializeToString(&data);
}

}