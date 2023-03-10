// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_info_base.proto

#include "message_info_base.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace ssp {
constexpr MessageInfoBase::MessageInfoBase(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : content_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , ver_(0u)
  , user_id_(0u)
  , publisher_time_(PROTOBUF_ULONGLONG(0))
  , publisher_id_(0u){}
struct MessageInfoBaseDefaultTypeInternal {
  constexpr MessageInfoBaseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MessageInfoBaseDefaultTypeInternal() {}
  union {
    MessageInfoBase _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MessageInfoBaseDefaultTypeInternal _MessageInfoBase_default_instance_;
}  // namespace ssp
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_message_5finfo_5fbase_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_message_5finfo_5fbase_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_message_5finfo_5fbase_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_message_5finfo_5fbase_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, ver_),
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, user_id_),
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, publisher_id_),
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, publisher_time_),
  PROTOBUF_FIELD_OFFSET(::ssp::MessageInfoBase, content_),
  1,
  2,
  4,
  3,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, sizeof(::ssp::MessageInfoBase)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ssp::_MessageInfoBase_default_instance_),
};

const char descriptor_table_protodef_message_5finfo_5fbase_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\027message_info_base.proto\022\003ssp\"n\n\017Messag"
  "eInfoBase\022\013\n\003ver\030\001 \001(\r\022\017\n\007user_id\030\002 \001(\r\022"
  "\024\n\014publisher_id\030\003 \001(\r\022\026\n\016publisher_time\030"
  "\004 \001(\004\022\017\n\007content\030\005 \001(\t"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_message_5finfo_5fbase_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_message_5finfo_5fbase_2eproto = {
  false, false, 142, descriptor_table_protodef_message_5finfo_5fbase_2eproto, "message_info_base.proto", 
  &descriptor_table_message_5finfo_5fbase_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_message_5finfo_5fbase_2eproto::offsets,
  file_level_metadata_message_5finfo_5fbase_2eproto, file_level_enum_descriptors_message_5finfo_5fbase_2eproto, file_level_service_descriptors_message_5finfo_5fbase_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_message_5finfo_5fbase_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_message_5finfo_5fbase_2eproto);
  return descriptor_table_message_5finfo_5fbase_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_message_5finfo_5fbase_2eproto(&descriptor_table_message_5finfo_5fbase_2eproto);
namespace ssp {

// ===================================================================

class MessageInfoBase::_Internal {
 public:
  using HasBits = decltype(std::declval<MessageInfoBase>()._has_bits_);
  static void set_has_ver(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_user_id(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_publisher_id(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static void set_has_publisher_time(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_content(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

MessageInfoBase::MessageInfoBase(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ssp.MessageInfoBase)
}
MessageInfoBase::MessageInfoBase(const MessageInfoBase& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  content_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_content()) {
    content_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_content(), 
      GetArena());
  }
  ::memcpy(&ver_, &from.ver_,
    static_cast<size_t>(reinterpret_cast<char*>(&publisher_id_) -
    reinterpret_cast<char*>(&ver_)) + sizeof(publisher_id_));
  // @@protoc_insertion_point(copy_constructor:ssp.MessageInfoBase)
}

void MessageInfoBase::SharedCtor() {
content_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&ver_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&publisher_id_) -
    reinterpret_cast<char*>(&ver_)) + sizeof(publisher_id_));
}

MessageInfoBase::~MessageInfoBase() {
  // @@protoc_insertion_point(destructor:ssp.MessageInfoBase)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void MessageInfoBase::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  content_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void MessageInfoBase::ArenaDtor(void* object) {
  MessageInfoBase* _this = reinterpret_cast< MessageInfoBase* >(object);
  (void)_this;
}
void MessageInfoBase::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MessageInfoBase::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MessageInfoBase::Clear() {
// @@protoc_insertion_point(message_clear_start:ssp.MessageInfoBase)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    content_.ClearNonDefaultToEmpty();
  }
  if (cached_has_bits & 0x0000001eu) {
    ::memset(&ver_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&publisher_id_) -
        reinterpret_cast<char*>(&ver_)) + sizeof(publisher_id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MessageInfoBase::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional uint32 ver = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_ver(&has_bits);
          ver_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 user_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_user_id(&has_bits);
          user_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 publisher_id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_publisher_id(&has_bits);
          publisher_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint64 publisher_time = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_publisher_time(&has_bits);
          publisher_time_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional string content = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_content();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ssp.MessageInfoBase.content");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* MessageInfoBase::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ssp.MessageInfoBase)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 ver = 1;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_ver(), target);
  }

  // optional uint32 user_id = 2;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_user_id(), target);
  }

  // optional uint32 publisher_id = 3;
  if (cached_has_bits & 0x00000010u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_publisher_id(), target);
  }

  // optional uint64 publisher_time = 4;
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(4, this->_internal_publisher_time(), target);
  }

  // optional string content = 5;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_content().data(), static_cast<int>(this->_internal_content().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "ssp.MessageInfoBase.content");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_content(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ssp.MessageInfoBase)
  return target;
}

size_t MessageInfoBase::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ssp.MessageInfoBase)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    // optional string content = 5;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_content());
    }

    // optional uint32 ver = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->_internal_ver());
    }

    // optional uint32 user_id = 2;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->_internal_user_id());
    }

    // optional uint64 publisher_time = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
          this->_internal_publisher_time());
    }

    // optional uint32 publisher_id = 3;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->_internal_publisher_id());
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MessageInfoBase::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ssp.MessageInfoBase)
  GOOGLE_DCHECK_NE(&from, this);
  const MessageInfoBase* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MessageInfoBase>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ssp.MessageInfoBase)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ssp.MessageInfoBase)
    MergeFrom(*source);
  }
}

void MessageInfoBase::MergeFrom(const MessageInfoBase& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ssp.MessageInfoBase)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_content(from._internal_content());
    }
    if (cached_has_bits & 0x00000002u) {
      ver_ = from.ver_;
    }
    if (cached_has_bits & 0x00000004u) {
      user_id_ = from.user_id_;
    }
    if (cached_has_bits & 0x00000008u) {
      publisher_time_ = from.publisher_time_;
    }
    if (cached_has_bits & 0x00000010u) {
      publisher_id_ = from.publisher_id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void MessageInfoBase::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ssp.MessageInfoBase)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MessageInfoBase::CopyFrom(const MessageInfoBase& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ssp.MessageInfoBase)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageInfoBase::IsInitialized() const {
  return true;
}

void MessageInfoBase::InternalSwap(MessageInfoBase* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  content_.Swap(&other->content_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MessageInfoBase, publisher_id_)
      + sizeof(MessageInfoBase::publisher_id_)
      - PROTOBUF_FIELD_OFFSET(MessageInfoBase, ver_)>(
          reinterpret_cast<char*>(&ver_),
          reinterpret_cast<char*>(&other->ver_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MessageInfoBase::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace ssp
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ssp::MessageInfoBase* Arena::CreateMaybeMessage< ::ssp::MessageInfoBase >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ssp::MessageInfoBase >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
