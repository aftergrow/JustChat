// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: photo_info_base.proto

#ifndef PROTOBUF_photo_5finfo_5fbase_2eproto__INCLUDED
#define PROTOBUF_photo_5finfo_5fbase_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace ssp {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_photo_5finfo_5fbase_2eproto();
void protobuf_AssignDesc_photo_5finfo_5fbase_2eproto();
void protobuf_ShutdownFile_photo_5finfo_5fbase_2eproto();

class PhotoInfoBase;

// ===================================================================

class PhotoInfoBase : public ::google::protobuf::Message {
 public:
  PhotoInfoBase();
  virtual ~PhotoInfoBase();

  PhotoInfoBase(const PhotoInfoBase& from);

  inline PhotoInfoBase& operator=(const PhotoInfoBase& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PhotoInfoBase& default_instance();

  void Swap(PhotoInfoBase* other);

  // implements Message ----------------------------------------------

  PhotoInfoBase* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PhotoInfoBase& from);
  void MergeFrom(const PhotoInfoBase& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 ver = 1;
  inline bool has_ver() const;
  inline void clear_ver();
  static const int kVerFieldNumber = 1;
  inline ::google::protobuf::uint32 ver() const;
  inline void set_ver(::google::protobuf::uint32 value);

  // optional uint32 user_id = 2;
  inline bool has_user_id() const;
  inline void clear_user_id();
  static const int kUserIdFieldNumber = 2;
  inline ::google::protobuf::uint32 user_id() const;
  inline void set_user_id(::google::protobuf::uint32 value);

  // optional uint32 last_publisher = 3;
  inline bool has_last_publisher() const;
  inline void clear_last_publisher();
  static const int kLastPublisherFieldNumber = 3;
  inline ::google::protobuf::uint32 last_publisher() const;
  inline void set_last_publisher(::google::protobuf::uint32 value);

  // optional uint64 last_publisher_time = 4;
  inline bool has_last_publisher_time() const;
  inline void clear_last_publisher_time();
  static const int kLastPublisherTimeFieldNumber = 4;
  inline ::google::protobuf::uint64 last_publisher_time() const;
  inline void set_last_publisher_time(::google::protobuf::uint64 value);

  // optional uint64 last_user_get_time = 5;
  inline bool has_last_user_get_time() const;
  inline void clear_last_user_get_time();
  static const int kLastUserGetTimeFieldNumber = 5;
  inline ::google::protobuf::uint64 last_user_get_time() const;
  inline void set_last_user_get_time(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:ssp.PhotoInfoBase)
 private:
  inline void set_has_ver();
  inline void clear_has_ver();
  inline void set_has_user_id();
  inline void clear_has_user_id();
  inline void set_has_last_publisher();
  inline void clear_has_last_publisher();
  inline void set_has_last_publisher_time();
  inline void clear_has_last_publisher_time();
  inline void set_has_last_user_get_time();
  inline void clear_has_last_user_get_time();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 ver_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint64 last_publisher_time_;
  ::google::protobuf::uint64 last_user_get_time_;
  ::google::protobuf::uint32 last_publisher_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_photo_5finfo_5fbase_2eproto();
  friend void protobuf_AssignDesc_photo_5finfo_5fbase_2eproto();
  friend void protobuf_ShutdownFile_photo_5finfo_5fbase_2eproto();

  void InitAsDefaultInstance();
  static PhotoInfoBase* default_instance_;
};
// ===================================================================


// ===================================================================

// PhotoInfoBase

// optional uint32 ver = 1;
inline bool PhotoInfoBase::has_ver() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PhotoInfoBase::set_has_ver() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PhotoInfoBase::clear_has_ver() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PhotoInfoBase::clear_ver() {
  ver_ = 0u;
  clear_has_ver();
}
inline ::google::protobuf::uint32 PhotoInfoBase::ver() const {
  return ver_;
}
inline void PhotoInfoBase::set_ver(::google::protobuf::uint32 value) {
  set_has_ver();
  ver_ = value;
}

// optional uint32 user_id = 2;
inline bool PhotoInfoBase::has_user_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PhotoInfoBase::set_has_user_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PhotoInfoBase::clear_has_user_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PhotoInfoBase::clear_user_id() {
  user_id_ = 0u;
  clear_has_user_id();
}
inline ::google::protobuf::uint32 PhotoInfoBase::user_id() const {
  return user_id_;
}
inline void PhotoInfoBase::set_user_id(::google::protobuf::uint32 value) {
  set_has_user_id();
  user_id_ = value;
}

// optional uint32 last_publisher = 3;
inline bool PhotoInfoBase::has_last_publisher() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PhotoInfoBase::set_has_last_publisher() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PhotoInfoBase::clear_has_last_publisher() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PhotoInfoBase::clear_last_publisher() {
  last_publisher_ = 0u;
  clear_has_last_publisher();
}
inline ::google::protobuf::uint32 PhotoInfoBase::last_publisher() const {
  return last_publisher_;
}
inline void PhotoInfoBase::set_last_publisher(::google::protobuf::uint32 value) {
  set_has_last_publisher();
  last_publisher_ = value;
}

// optional uint64 last_publisher_time = 4;
inline bool PhotoInfoBase::has_last_publisher_time() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PhotoInfoBase::set_has_last_publisher_time() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PhotoInfoBase::clear_has_last_publisher_time() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PhotoInfoBase::clear_last_publisher_time() {
  last_publisher_time_ = GOOGLE_ULONGLONG(0);
  clear_has_last_publisher_time();
}
inline ::google::protobuf::uint64 PhotoInfoBase::last_publisher_time() const {
  return last_publisher_time_;
}
inline void PhotoInfoBase::set_last_publisher_time(::google::protobuf::uint64 value) {
  set_has_last_publisher_time();
  last_publisher_time_ = value;
}

// optional uint64 last_user_get_time = 5;
inline bool PhotoInfoBase::has_last_user_get_time() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PhotoInfoBase::set_has_last_user_get_time() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PhotoInfoBase::clear_has_last_user_get_time() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PhotoInfoBase::clear_last_user_get_time() {
  last_user_get_time_ = GOOGLE_ULONGLONG(0);
  clear_has_last_user_get_time();
}
inline ::google::protobuf::uint64 PhotoInfoBase::last_user_get_time() const {
  return last_user_get_time_;
}
inline void PhotoInfoBase::set_last_user_get_time(::google::protobuf::uint64 value) {
  set_has_last_user_get_time();
  last_user_get_time_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ssp

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_photo_5finfo_5fbase_2eproto__INCLUDED
