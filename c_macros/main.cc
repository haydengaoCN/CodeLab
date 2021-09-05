#include <iostream>

#define GREETINGS ("hello")

#define DEFINE_VARIABLE_LENGTH_MEMBER_FOR_TYPE_META(type, \
    index_type, \
    return_type, \
    name) \
  mutable PlainStringIndex<index_type> name##_index; \
  index_type name##_length() const { \
    return name##_index.length; \
  } \
  const return_type* name() const { \
    if (name##_index.length == 0) { \
      return NULL; \
    } \
    return reinterpret_cast<const return_type*>(\
        name##_index.GetData(this->data)); \
  }\
  static type* update_##name(const std::string &input, \
      std::string* buffer) { \
    buffer->append(input); \
    type* meta = CastFromString(buffer); \
    meta->name##_index.length = input.size(); \
    meta->name##_index.offset =  meta->data_length; \
    meta->data_length += input.size(); \
    return meta; \
  }\
  static type* update_##name(const void* input, uint64_t len, std::string* buffer) { \
    buffer->append(reinterpret_cast<const char*>(input), len); \
    type* meta = CastFromString(buffer); \
    meta->name##_index.length = len; \
    meta->name##_index.offset = meta->data_length; \
    meta->data_length += len; \
    return meta; \
  }

DEFINE_VARIABLE_LENGTH_MEMBER_FOR_TYPE_META(PlainCreativeMeta, \
                                            uint32_t, \
                                            char, \
                                            md5)

mutable PlainStringIndex<uint32_t> md5_index;

uint32_t md5_length() const {
  return md5_index.length;
}

const char* md5() const {
  if (md5_index.length == 0) {
    return __null;
  }
  return reinterpret_cast<const char*>( md5_index.GetData(this->data));
}

static PlainCreativeMeta* update_md5(const std::string &input, std::string* buffer) {
  buffer->append(input);
  PlainCreativeMeta* meta = CastFromString(buffer);
  meta->md5_index.length = input.size();
  meta->md5_index.offset = meta->data_length;
  meta->data_length += input.size();
  return meta;
}

static PlainCreativeMeta* update_md5(const void* input, uint64_t len, std::string* buffer) {
  buffer->append(reinterpret_cast<const char*>(input), len);
  PlainCreativeMeta* meta = CastFromString(buffer);
  meta->md5_index.length = len;
  meta->md5_index.offset = meta->data_length;
  meta->data_length += len;
  return meta;
}

#define DECLARE_FIELD(meta, new_meta, field_name) \
  auto field_name() const { \
    return new_meta ? new_meta->field_name : meta->field_name; \
  } \
  bool has_##field_name() const { \
    return new_meta ? true : meta != nullptr; \
  } \
  auto mutable_##field_name() const { \
    return new_meta ? &new_meta->field_name : &meta->field_name; \
  }

#define META_FIELD(meta, field_name) \
 public: \
 DECLARE_FIELD(meta, ams_meta_, field_name)

META_FIELD(meta_, aid);

public:
 auto aid() const {
   return ams_meta_ ? ams_meta_->aid : meta_->aid;
 } 
 bool has_aid() const {
   return ams_meta_ ? true : meta_ != std::__1::__get_nullptr_t(); 
 } 
 auto mutable_aid() const {
   return ams_meta_ ? &ams_meta_->aid : &meta_->aid;
 };

int main() {
  std::cout << GREETINGS << std::endl;

  return 0;
}
