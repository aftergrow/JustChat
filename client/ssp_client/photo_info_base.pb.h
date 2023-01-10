// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: photo_info_base.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_photo_5finfo_5fbase_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_photo_5finfo_5fbase_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_photo_5finfo_5fbase_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_photo_5finfo_5fbase_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_photo_5finfo_5fbase_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_photo_5finfo_5fbase_2eproto_metadata_getter(int index);
namespace ssp {
class PhotoInfoBase;
struct PhotoInfoBaseDefaultTypeInternal;
extern PhotoInfoBaseDefaultTypeInternal _PhotoInfoBase_default_instance_;
}  // namespace ssp
PROTOBUF_NAMESPACE_OPEN
template<> ::ssp::PhotoInfoBase* Arena::CreateMaybeMessage<::ssp::PhotoInfoBase>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ssp {

// ===================================================================

class PhotoInfoBase PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ssp.PhotoInfoBase) */ {
 public:
  inline PhotoInfoBase() : PhotoInfoBase(nullptr) {}
  virtual ~PhotoInfoBase();
  explicit constexpr PhotoInfoBase(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PhotoInfoBase(const PhotoInfoBase& from);
  PhotoInfoBase(PhotoInfoBase&& from) noexcept
    : PhotoInfoBase() {
    *this = ::std::move(from);
  }

  inline PhotoInfoBase& operator=(const PhotoInfoBase& from) {
    CopyFrom(from);
    return *this;
  }
  inline PhotoInfoBase& operator=(PhotoInfoBase&& from) noexcept {
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
  static const PhotoInfoBase& default_instance() {
    return *internal_default_instance();
  }
  static inline const PhotoInfoBase* internal_default_instance() {
    return reinterpret_cast<const PhotoInfoBase*>(
               &_PhotoInfoBase_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PhotoInfoBase& a, PhotoInfoBase& b) {
    a.Swap(&b);
  }
  inline void Swap(PhotoInfoBase* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PhotoInfoBase* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PhotoInfoBase* New() const final {
    return CreateMaybeMessage<PhotoInfoBase>(nullptr);
  }

  PhotoInfoBase* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PhotoInfoBase>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const PhotoInfoBase& from);
  void MergeFrom(const PhotoInfoBase& from);
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
  void InternalSwap(PhotoInfoBase* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ssp.PhotoInfoBase";
  }
  protected:
  explicit PhotoInfoBase(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_photo_5finfo_5fbase_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kVerFieldNumber = 1,
    kUserIdFieldNumber = 2,
    kLastPublisherTimeFieldNumber = 4,
    kLastUserGetTimeFieldNumber = 5,
    kLastPublisherFieldNumber = 3,
  };
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

  // optional uint64 last_publisher_time = 4;
  bool has_last_publisher_time() const;
  private:
  bool _internal_has_last_publisher_time() const;
  public:
  void clear_last_publisher_time();
  ::PROTOBUF_NAMESPACE_ID::uint64 last_publisher_time() const;
  void set_last_publisher_time(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_last_publisher_time() const;
  void _internal_set_last_publisher_time(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // optional uint64 last_user_get_time = 5;
  bool has_last_user_get_time() const;
  private:
  bool _internal_has_last_user_get_time() const;
  public:
  void clear_last_user_get_time();
  ::PROTOBUF_NAMESPACE_ID::uint64 last_user_get_time() const;
  void set_last_user_get_time(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_last_user_get_time() const;
  void _internal_set_last_user_get_time(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // optional uint32 last_publisher = 3;
  bool has_last_publisher() const;
  private:
  bool _internal_has_last_publisher() const;
  public:
  void clear_last_publisher();
  ::PROTOBUF_NAMESPACE_ID::uint32 last_publisher() const;
  void set_last_publisher(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_last_publisher() const;
  void _internal_set_last_publisher(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:ssp.PhotoInfoBase)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 ver_;
  ::PROTOBUF_NAMESPACE_ID::uint32 user_id_;
  ::PROTOBUF_NAMESPACE_ID::uint64 last_publisher_time_;
  ::PROTOBUF_NAMESPACE_ID::uint64 last_user_get_time_;
  ::PROTOBUF_NAMESPACE_ID::uint32 last_publisher_;
  friend struct ::TableStruct_photo_5finfo_5fbase_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PhotoInfoBase

// optional uint32 ver = 1;
inline bool PhotoInfoBase::_internal_has_ver() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool PhotoInfoBase::has_ver() const {
  return _internal_has_ver();
}
inline void PhotoInfoBase::clear_ver() {
  ver_ = 0u;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 PhotoInfoBase::_internal_ver() const {
  return ver_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 PhotoInfoBase::ver() const {
  // @@protoc_insertion_point(field_get:ssp.PhotoInfoBase.ver)
  return _internal_ver();
}
inline void PhotoInfoBase::_internal_set_ver(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000001u;
  ver_ = value;
}
inline void PhotoInfoBase::set_ver(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_ver(value);
  // @@protoc_insertion_point(field_set:ssp.PhotoInfoBase.ver)
}

// optional uint32 user_id = 2;
inline bool PhotoInfoBase::_internal_has_user_id() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool PhotoInfoBase::has_user_id() const {
  return _internal_has_user_id();
}
inline void PhotoInfoBase::clear_user_id() {
  user_id_ = 0u;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 PhotoInfoBase::_internal_user_id() const {
  return user_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 PhotoInfoBase::user_id() const {
  // @@protoc_insertion_point(field_get:ssp.PhotoInfoBase.user_id)
  return _internal_user_id();
}
inline void PhotoInfoBase::_internal_set_user_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000002u;
  user_id_ = value;
}
inline void PhotoInfoBase::set_user_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_user_id(value);
  // @@protoc_insertion_point(field_set:ssp.PhotoInfoBase.user_id)
}

// optional uint32 last_publisher = 3;
inline bool PhotoInfoBase::_internal_has_last_publisher() const {
  bool value = (_has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool PhotoInfoBase::has_last_publisher() const {
  return _internal_has_last_publisher();
}
inline void PhotoInfoBase::clear_last_publisher() {
  last_publisher_ = 0u;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 PhotoInfoBase::_internal_last_publisher() const {
  return last_publisher_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 PhotoInfoBase::last_publisher() const {
  // @@protoc_insertion_point(field_get:ssp.PhotoInfoBase.last_publisher)
  return _internal_last_publisher();
}
inline void PhotoInfoBase::_internal_set_last_publisher(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000010u;
  last_publisher_ = value;
}
inline void PhotoInfoBase::set_last_publisher(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_last_publisher(value);
  // @@protoc_insertion_point(field_set:ssp.PhotoInfoBase.last_publisher)
}

// optional uint64 last_publisher_time = 4;
inline bool PhotoInfoBase::_internal_has_last_publisher_time() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool PhotoInfoBase::has_last_publisher_time() const {
  return _internal_has_last_publisher_time();
}
inline void PhotoInfoBase::clear_last_publisher_time() {
  last_publisher_time_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 PhotoInfoBase::_internal_last_publisher_time() const {
  return last_publisher_time_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 PhotoInfoBase::last_publisher_time() const {
  // @@protoc_insertion_point(field_get:ssp.PhotoInfoBase.last_publisher_time)
  return _internal_last_publisher_time();
}
inline void PhotoInfoBase::_internal_set_last_publisher_time(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000004u;
  last_publisher_time_ = value;
}
inline void PhotoInfoBase::set_last_publisher_time(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_last_publisher_time(value);
  // @@protoc_insertion_point(field_set:ssp.PhotoInfoBase.last_publisher_time)
}

// optional uint64 last_user_get_time = 5;
inline bool PhotoInfoBase::_internal_has_last_user_get_time() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool PhotoInfoBase::has_last_user_get_time() const {
  return _internal_has_last_user_get_time();
}
inline void PhotoInfoBase::clear_last_user_get_time() {
  last_user_get_time_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 PhotoInfoBase::_internal_last_user_get_time() const {
  return last_user_get_time_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 PhotoInfoBase::last_user_get_time() const {
  // @@protoc_insertion_point(field_get:ssp.PhotoInfoBase.last_user_get_time)
  return _internal_last_user_get_time();
}
inline void PhotoInfoBase::_internal_set_last_user_get_time(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000008u;
  last_user_get_time_ = value;
}
inline void PhotoInfoBase::set_last_user_get_time(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_last_user_get_time(value);
  // @@protoc_insertion_point(field_set:ssp.PhotoInfoBase.last_user_get_time)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ssp

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_photo_5finfo_5fbase_2eproto