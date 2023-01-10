// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: relation_info_base.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_relation_5finfo_5fbase_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_relation_5finfo_5fbase_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3015000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3015000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_relation_5finfo_5fbase_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_relation_5finfo_5fbase_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_relation_5finfo_5fbase_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_relation_5finfo_5fbase_2eproto_metadata_getter(int index);
namespace ssp {
class RelationInfoBase;
struct RelationInfoBaseDefaultTypeInternal;
extern RelationInfoBaseDefaultTypeInternal _RelationInfoBase_default_instance_;
}  // namespace ssp
PROTOBUF_NAMESPACE_OPEN
template<> ::ssp::RelationInfoBase* Arena::CreateMaybeMessage<::ssp::RelationInfoBase>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ssp {

// ===================================================================

class RelationInfoBase PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ssp.RelationInfoBase) */ {
 public:
  inline RelationInfoBase() : RelationInfoBase(nullptr) {}
  virtual ~RelationInfoBase();
  explicit constexpr RelationInfoBase(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RelationInfoBase(const RelationInfoBase& from);
  RelationInfoBase(RelationInfoBase&& from) noexcept
    : RelationInfoBase() {
    *this = ::std::move(from);
  }

  inline RelationInfoBase& operator=(const RelationInfoBase& from) {
    CopyFrom(from);
    return *this;
  }
  inline RelationInfoBase& operator=(RelationInfoBase&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const RelationInfoBase& default_instance() {
    return *internal_default_instance();
  }
  static inline const RelationInfoBase* internal_default_instance() {
    return reinterpret_cast<const RelationInfoBase*>(
               &_RelationInfoBase_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RelationInfoBase& a, RelationInfoBase& b) {
    a.Swap(&b);
  }
  inline void Swap(RelationInfoBase* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RelationInfoBase* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline RelationInfoBase* New() const final {
    return CreateMaybeMessage<RelationInfoBase>(nullptr);
  }

  RelationInfoBase* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RelationInfoBase>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const RelationInfoBase& from);
  void MergeFrom(const RelationInfoBase& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RelationInfoBase* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ssp.RelationInfoBase";
  }
  protected:
  explicit RelationInfoBase(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_relation_5finfo_5fbase_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFriendListFieldNumber = 3,
    kBlackListFieldNumber = 4,
    kVerFieldNumber = 1,
    kUserIdFieldNumber = 2,
  };
  // repeated uint32 friend_list = 3;
  int friend_list_size() const;
  private:
  int _internal_friend_list_size() const;
  public:
  void clear_friend_list();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_friend_list(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_friend_list() const;
  void _internal_add_friend_list(::PROTOBUF_NAMESPACE_ID::uint32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_friend_list();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint32 friend_list(int index) const;
  void set_friend_list(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_friend_list(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      friend_list() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_friend_list();

  // repeated uint32 black_list = 4;
  int black_list_size() const;
  private:
  int _internal_black_list_size() const;
  public:
  void clear_black_list();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_black_list(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_black_list() const;
  void _internal_add_black_list(::PROTOBUF_NAMESPACE_ID::uint32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_black_list();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint32 black_list(int index) const;
  void set_black_list(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_black_list(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      black_list() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_black_list();

  // optional uint32 ver = 1;
  bool has_ver() const;
  private:
  bool _internal_has_ver() const;
  public:
  void clear_ver();
  ::PROTOBUF_NAMESPACE_ID::uint32 ver() const;
  void set_ver(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_ver() const;
  void _internal_set_ver(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // optional uint32 user_id = 2;
  bool has_user_id() const;
  private:
  bool _internal_has_user_id() const;
  public:
  void clear_user_id();
  ::PROTOBUF_NAMESPACE_ID::uint32 user_id() const;
  void set_user_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_user_id() const;
  void _internal_set_user_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:ssp.RelationInfoBase)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > friend_list_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > black_list_;
  ::PROTOBUF_NAMESPACE_ID::uint32 ver_;
  ::PROTOBUF_NAMESPACE_ID::uint32 user_id_;
  friend struct ::TableStruct_relation_5finfo_5fbase_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RelationInfoBase

// optional uint32 ver = 1;
inline bool RelationInfoBase::_internal_has_ver() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool RelationInfoBase::has_ver() const {
  return _internal_has_ver();
}
inline void RelationInfoBase::clear_ver() {
  ver_ = 0u;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::_internal_ver() const {
  return ver_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::ver() const {
  // @@protoc_insertion_point(field_get:ssp.RelationInfoBase.ver)
  return _internal_ver();
}
inline void RelationInfoBase::_internal_set_ver(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000001u;
  ver_ = value;
}
inline void RelationInfoBase::set_ver(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_ver(value);
  // @@protoc_insertion_point(field_set:ssp.RelationInfoBase.ver)
}

// optional uint32 user_id = 2;
inline bool RelationInfoBase::_internal_has_user_id() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool RelationInfoBase::has_user_id() const {
  return _internal_has_user_id();
}
inline void RelationInfoBase::clear_user_id() {
  user_id_ = 0u;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::_internal_user_id() const {
  return user_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::user_id() const {
  // @@protoc_insertion_point(field_get:ssp.RelationInfoBase.user_id)
  return _internal_user_id();
}
inline void RelationInfoBase::_internal_set_user_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000002u;
  user_id_ = value;
}
inline void RelationInfoBase::set_user_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_user_id(value);
  // @@protoc_insertion_point(field_set:ssp.RelationInfoBase.user_id)
}

// repeated uint32 friend_list = 3;
inline int RelationInfoBase::_internal_friend_list_size() const {
  return friend_list_.size();
}
inline int RelationInfoBase::friend_list_size() const {
  return _internal_friend_list_size();
}
inline void RelationInfoBase::clear_friend_list() {
  friend_list_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::_internal_friend_list(int index) const {
  return friend_list_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::friend_list(int index) const {
  // @@protoc_insertion_point(field_get:ssp.RelationInfoBase.friend_list)
  return _internal_friend_list(index);
}
inline void RelationInfoBase::set_friend_list(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  friend_list_.Set(index, value);
  // @@protoc_insertion_point(field_set:ssp.RelationInfoBase.friend_list)
}
inline void RelationInfoBase::_internal_add_friend_list(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  friend_list_.Add(value);
}
inline void RelationInfoBase::add_friend_list(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_add_friend_list(value);
  // @@protoc_insertion_point(field_add:ssp.RelationInfoBase.friend_list)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
RelationInfoBase::_internal_friend_list() const {
  return friend_list_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
RelationInfoBase::friend_list() const {
  // @@protoc_insertion_point(field_list:ssp.RelationInfoBase.friend_list)
  return _internal_friend_list();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
RelationInfoBase::_internal_mutable_friend_list() {
  return &friend_list_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
RelationInfoBase::mutable_friend_list() {
  // @@protoc_insertion_point(field_mutable_list:ssp.RelationInfoBase.friend_list)
  return _internal_mutable_friend_list();
}

// repeated uint32 black_list = 4;
inline int RelationInfoBase::_internal_black_list_size() const {
  return black_list_.size();
}
inline int RelationInfoBase::black_list_size() const {
  return _internal_black_list_size();
}
inline void RelationInfoBase::clear_black_list() {
  black_list_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::_internal_black_list(int index) const {
  return black_list_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RelationInfoBase::black_list(int index) const {
  // @@protoc_insertion_point(field_get:ssp.RelationInfoBase.black_list)
  return _internal_black_list(index);
}
inline void RelationInfoBase::set_black_list(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  black_list_.Set(index, value);
  // @@protoc_insertion_point(field_set:ssp.RelationInfoBase.black_list)
}
inline void RelationInfoBase::_internal_add_black_list(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  black_list_.Add(value);
}
inline void RelationInfoBase::add_black_list(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_add_black_list(value);
  // @@protoc_insertion_point(field_add:ssp.RelationInfoBase.black_list)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
RelationInfoBase::_internal_black_list() const {
  return black_list_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
RelationInfoBase::black_list() const {
  // @@protoc_insertion_point(field_list:ssp.RelationInfoBase.black_list)
  return _internal_black_list();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
RelationInfoBase::_internal_mutable_black_list() {
  return &black_list_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
RelationInfoBase::mutable_black_list() {
  // @@protoc_insertion_point(field_mutable_list:ssp.RelationInfoBase.black_list)
  return _internal_mutable_black_list();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ssp

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_relation_5finfo_5fbase_2eproto