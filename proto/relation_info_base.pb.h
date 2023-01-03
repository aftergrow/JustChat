// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: relation_info_base.proto

#ifndef PROTOBUF_relation_5finfo_5fbase_2eproto__INCLUDED
#define PROTOBUF_relation_5finfo_5fbase_2eproto__INCLUDED

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
void  protobuf_AddDesc_relation_5finfo_5fbase_2eproto();
void protobuf_AssignDesc_relation_5finfo_5fbase_2eproto();
void protobuf_ShutdownFile_relation_5finfo_5fbase_2eproto();

class RelationInfoBase;

// ===================================================================

class RelationInfoBase : public ::google::protobuf::Message {
 public:
  RelationInfoBase();
  virtual ~RelationInfoBase();

  RelationInfoBase(const RelationInfoBase& from);

  inline RelationInfoBase& operator=(const RelationInfoBase& from) {
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
  static const RelationInfoBase& default_instance();

  void Swap(RelationInfoBase* other);

  // implements Message ----------------------------------------------

  RelationInfoBase* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RelationInfoBase& from);
  void MergeFrom(const RelationInfoBase& from);
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

  // repeated uint32 friend_list = 3;
  inline int friend_list_size() const;
  inline void clear_friend_list();
  static const int kFriendListFieldNumber = 3;
  inline ::google::protobuf::uint32 friend_list(int index) const;
  inline void set_friend_list(int index, ::google::protobuf::uint32 value);
  inline void add_friend_list(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      friend_list() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_friend_list();

  // repeated uint32 black_list = 4;
  inline int black_list_size() const;
  inline void clear_black_list();
  static const int kBlackListFieldNumber = 4;
  inline ::google::protobuf::uint32 black_list(int index) const;
  inline void set_black_list(int index, ::google::protobuf::uint32 value);
  inline void add_black_list(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      black_list() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_black_list();

  // optional uint32 friend_count = 5;
  inline bool has_friend_count() const;
  inline void clear_friend_count();
  static const int kFriendCountFieldNumber = 5;
  inline ::google::protobuf::uint32 friend_count() const;
  inline void set_friend_count(::google::protobuf::uint32 value);

  // optional uint32 black_count = 6;
  inline bool has_black_count() const;
  inline void clear_black_count();
  static const int kBlackCountFieldNumber = 6;
  inline ::google::protobuf::uint32 black_count() const;
  inline void set_black_count(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ssp.RelationInfoBase)
 private:
  inline void set_has_ver();
  inline void clear_has_ver();
  inline void set_has_user_id();
  inline void clear_has_user_id();
  inline void set_has_friend_count();
  inline void clear_has_friend_count();
  inline void set_has_black_count();
  inline void clear_has_black_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 ver_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > friend_list_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > black_list_;
  ::google::protobuf::uint32 friend_count_;
  ::google::protobuf::uint32 black_count_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_relation_5finfo_5fbase_2eproto();
  friend void protobuf_AssignDesc_relation_5finfo_5fbase_2eproto();
  friend void protobuf_ShutdownFile_relation_5finfo_5fbase_2eproto();

  void InitAsDefaultInstance();
  static RelationInfoBase* default_instance_;
};
// ===================================================================


// ===================================================================

// RelationInfoBase

// optional uint32 ver = 1;
inline bool RelationInfoBase::has_ver() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RelationInfoBase::set_has_ver() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RelationInfoBase::clear_has_ver() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RelationInfoBase::clear_ver() {
  ver_ = 0u;
  clear_has_ver();
}
inline ::google::protobuf::uint32 RelationInfoBase::ver() const {
  return ver_;
}
inline void RelationInfoBase::set_ver(::google::protobuf::uint32 value) {
  set_has_ver();
  ver_ = value;
}

// optional uint32 user_id = 2;
inline bool RelationInfoBase::has_user_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RelationInfoBase::set_has_user_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RelationInfoBase::clear_has_user_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RelationInfoBase::clear_user_id() {
  user_id_ = 0u;
  clear_has_user_id();
}
inline ::google::protobuf::uint32 RelationInfoBase::user_id() const {
  return user_id_;
}
inline void RelationInfoBase::set_user_id(::google::protobuf::uint32 value) {
  set_has_user_id();
  user_id_ = value;
}

// repeated uint32 friend_list = 3;
inline int RelationInfoBase::friend_list_size() const {
  return friend_list_.size();
}
inline void RelationInfoBase::clear_friend_list() {
  friend_list_.Clear();
}
inline ::google::protobuf::uint32 RelationInfoBase::friend_list(int index) const {
  return friend_list_.Get(index);
}
inline void RelationInfoBase::set_friend_list(int index, ::google::protobuf::uint32 value) {
  friend_list_.Set(index, value);
}
inline void RelationInfoBase::add_friend_list(::google::protobuf::uint32 value) {
  friend_list_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
RelationInfoBase::friend_list() const {
  return friend_list_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
RelationInfoBase::mutable_friend_list() {
  return &friend_list_;
}

// repeated uint32 black_list = 4;
inline int RelationInfoBase::black_list_size() const {
  return black_list_.size();
}
inline void RelationInfoBase::clear_black_list() {
  black_list_.Clear();
}
inline ::google::protobuf::uint32 RelationInfoBase::black_list(int index) const {
  return black_list_.Get(index);
}
inline void RelationInfoBase::set_black_list(int index, ::google::protobuf::uint32 value) {
  black_list_.Set(index, value);
}
inline void RelationInfoBase::add_black_list(::google::protobuf::uint32 value) {
  black_list_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
RelationInfoBase::black_list() const {
  return black_list_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
RelationInfoBase::mutable_black_list() {
  return &black_list_;
}

// optional uint32 friend_count = 5;
inline bool RelationInfoBase::has_friend_count() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void RelationInfoBase::set_has_friend_count() {
  _has_bits_[0] |= 0x00000010u;
}
inline void RelationInfoBase::clear_has_friend_count() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void RelationInfoBase::clear_friend_count() {
  friend_count_ = 0u;
  clear_has_friend_count();
}
inline ::google::protobuf::uint32 RelationInfoBase::friend_count() const {
  return friend_count_;
}
inline void RelationInfoBase::set_friend_count(::google::protobuf::uint32 value) {
  set_has_friend_count();
  friend_count_ = value;
}

// optional uint32 black_count = 6;
inline bool RelationInfoBase::has_black_count() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void RelationInfoBase::set_has_black_count() {
  _has_bits_[0] |= 0x00000020u;
}
inline void RelationInfoBase::clear_has_black_count() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void RelationInfoBase::clear_black_count() {
  black_count_ = 0u;
  clear_has_black_count();
}
inline ::google::protobuf::uint32 RelationInfoBase::black_count() const {
  return black_count_;
}
inline void RelationInfoBase::set_black_count(::google::protobuf::uint32 value) {
  set_has_black_count();
  black_count_ = value;
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

#endif  // PROTOBUF_relation_5finfo_5fbase_2eproto__INCLUDED
