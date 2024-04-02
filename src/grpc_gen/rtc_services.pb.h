// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rtc_services.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_rtc_5fservices_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_rtc_5fservices_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3018000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3018001 < PROTOBUF_MIN_PROTOC_VERSION
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
#define PROTOBUF_INTERNAL_EXPORT_rtc_5fservices_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_rtc_5fservices_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_rtc_5fservices_2eproto;
namespace mediaservice {
class IPv4Addr;
struct IPv4AddrDefaultTypeInternal;
extern IPv4AddrDefaultTypeInternal _IPv4Addr_default_instance_;
class RecvAddrRequest;
struct RecvAddrRequestDefaultTypeInternal;
extern RecvAddrRequestDefaultTypeInternal _RecvAddrRequest_default_instance_;
class RecvAddrResponse;
struct RecvAddrResponseDefaultTypeInternal;
extern RecvAddrResponseDefaultTypeInternal _RecvAddrResponse_default_instance_;
}  // namespace mediaservice
PROTOBUF_NAMESPACE_OPEN
template<> ::mediaservice::IPv4Addr* Arena::CreateMaybeMessage<::mediaservice::IPv4Addr>(Arena*);
template<> ::mediaservice::RecvAddrRequest* Arena::CreateMaybeMessage<::mediaservice::RecvAddrRequest>(Arena*);
template<> ::mediaservice::RecvAddrResponse* Arena::CreateMaybeMessage<::mediaservice::RecvAddrResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mediaservice {

// ===================================================================

class RecvAddrRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mediaservice.RecvAddrRequest) */ {
 public:
  inline RecvAddrRequest() : RecvAddrRequest(nullptr) {}
  ~RecvAddrRequest() override;
  explicit constexpr RecvAddrRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RecvAddrRequest(const RecvAddrRequest& from);
  RecvAddrRequest(RecvAddrRequest&& from) noexcept
    : RecvAddrRequest() {
    *this = ::std::move(from);
  }

  inline RecvAddrRequest& operator=(const RecvAddrRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline RecvAddrRequest& operator=(RecvAddrRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RecvAddrRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const RecvAddrRequest* internal_default_instance() {
    return reinterpret_cast<const RecvAddrRequest*>(
               &_RecvAddrRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RecvAddrRequest& a, RecvAddrRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(RecvAddrRequest* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RecvAddrRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline RecvAddrRequest* New() const final {
    return new RecvAddrRequest();
  }

  RecvAddrRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RecvAddrRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const RecvAddrRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const RecvAddrRequest& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RecvAddrRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mediaservice.RecvAddrRequest";
  }
  protected:
  explicit RecvAddrRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAddrCountFieldNumber = 1,
  };
  // uint32 addr_count = 1;
  void clear_addr_count();
  ::PROTOBUF_NAMESPACE_ID::uint32 addr_count() const;
  void set_addr_count(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_addr_count() const;
  void _internal_set_addr_count(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:mediaservice.RecvAddrRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::uint32 addr_count_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_rtc_5fservices_2eproto;
};
// -------------------------------------------------------------------

class IPv4Addr final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mediaservice.IPv4Addr) */ {
 public:
  inline IPv4Addr() : IPv4Addr(nullptr) {}
  ~IPv4Addr() override;
  explicit constexpr IPv4Addr(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  IPv4Addr(const IPv4Addr& from);
  IPv4Addr(IPv4Addr&& from) noexcept
    : IPv4Addr() {
    *this = ::std::move(from);
  }

  inline IPv4Addr& operator=(const IPv4Addr& from) {
    CopyFrom(from);
    return *this;
  }
  inline IPv4Addr& operator=(IPv4Addr&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const IPv4Addr& default_instance() {
    return *internal_default_instance();
  }
  static inline const IPv4Addr* internal_default_instance() {
    return reinterpret_cast<const IPv4Addr*>(
               &_IPv4Addr_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(IPv4Addr& a, IPv4Addr& b) {
    a.Swap(&b);
  }
  inline void Swap(IPv4Addr* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(IPv4Addr* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline IPv4Addr* New() const final {
    return new IPv4Addr();
  }

  IPv4Addr* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<IPv4Addr>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const IPv4Addr& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const IPv4Addr& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(IPv4Addr* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mediaservice.IPv4Addr";
  }
  protected:
  explicit IPv4Addr(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIpFieldNumber = 1,
    kPortFieldNumber = 2,
  };
  // string ip = 1;
  void clear_ip();
  const std::string& ip() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_ip(ArgT0&& arg0, ArgT... args);
  std::string* mutable_ip();
  PROTOBUF_MUST_USE_RESULT std::string* release_ip();
  void set_allocated_ip(std::string* ip);
  private:
  const std::string& _internal_ip() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_ip(const std::string& value);
  std::string* _internal_mutable_ip();
  public:

  // uint32 port = 2;
  void clear_port();
  ::PROTOBUF_NAMESPACE_ID::uint32 port() const;
  void set_port(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_port() const;
  void _internal_set_port(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:mediaservice.IPv4Addr)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr ip_;
  ::PROTOBUF_NAMESPACE_ID::uint32 port_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_rtc_5fservices_2eproto;
};
// -------------------------------------------------------------------

class RecvAddrResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mediaservice.RecvAddrResponse) */ {
 public:
  inline RecvAddrResponse() : RecvAddrResponse(nullptr) {}
  ~RecvAddrResponse() override;
  explicit constexpr RecvAddrResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RecvAddrResponse(const RecvAddrResponse& from);
  RecvAddrResponse(RecvAddrResponse&& from) noexcept
    : RecvAddrResponse() {
    *this = ::std::move(from);
  }

  inline RecvAddrResponse& operator=(const RecvAddrResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline RecvAddrResponse& operator=(RecvAddrResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RecvAddrResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const RecvAddrResponse* internal_default_instance() {
    return reinterpret_cast<const RecvAddrResponse*>(
               &_RecvAddrResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(RecvAddrResponse& a, RecvAddrResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(RecvAddrResponse* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RecvAddrResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline RecvAddrResponse* New() const final {
    return new RecvAddrResponse();
  }

  RecvAddrResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RecvAddrResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const RecvAddrResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const RecvAddrResponse& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RecvAddrResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mediaservice.RecvAddrResponse";
  }
  protected:
  explicit RecvAddrResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAddressFieldNumber = 1,
  };
  // repeated .mediaservice.IPv4Addr address = 1;
  int address_size() const;
  private:
  int _internal_address_size() const;
  public:
  void clear_address();
  ::mediaservice::IPv4Addr* mutable_address(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::mediaservice::IPv4Addr >*
      mutable_address();
  private:
  const ::mediaservice::IPv4Addr& _internal_address(int index) const;
  ::mediaservice::IPv4Addr* _internal_add_address();
  public:
  const ::mediaservice::IPv4Addr& address(int index) const;
  ::mediaservice::IPv4Addr* add_address();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::mediaservice::IPv4Addr >&
      address() const;

  // @@protoc_insertion_point(class_scope:mediaservice.RecvAddrResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::mediaservice::IPv4Addr > address_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_rtc_5fservices_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RecvAddrRequest

// uint32 addr_count = 1;
inline void RecvAddrRequest::clear_addr_count() {
  addr_count_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RecvAddrRequest::_internal_addr_count() const {
  return addr_count_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 RecvAddrRequest::addr_count() const {
  // @@protoc_insertion_point(field_get:mediaservice.RecvAddrRequest.addr_count)
  return _internal_addr_count();
}
inline void RecvAddrRequest::_internal_set_addr_count(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  addr_count_ = value;
}
inline void RecvAddrRequest::set_addr_count(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_addr_count(value);
  // @@protoc_insertion_point(field_set:mediaservice.RecvAddrRequest.addr_count)
}

// -------------------------------------------------------------------

// IPv4Addr

// string ip = 1;
inline void IPv4Addr::clear_ip() {
  ip_.ClearToEmpty();
}
inline const std::string& IPv4Addr::ip() const {
  // @@protoc_insertion_point(field_get:mediaservice.IPv4Addr.ip)
  return _internal_ip();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void IPv4Addr::set_ip(ArgT0&& arg0, ArgT... args) {
 
 ip_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mediaservice.IPv4Addr.ip)
}
inline std::string* IPv4Addr::mutable_ip() {
  std::string* _s = _internal_mutable_ip();
  // @@protoc_insertion_point(field_mutable:mediaservice.IPv4Addr.ip)
  return _s;
}
inline const std::string& IPv4Addr::_internal_ip() const {
  return ip_.Get();
}
inline void IPv4Addr::_internal_set_ip(const std::string& value) {
  
  ip_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* IPv4Addr::_internal_mutable_ip() {
  
  return ip_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* IPv4Addr::release_ip() {
  // @@protoc_insertion_point(field_release:mediaservice.IPv4Addr.ip)
  return ip_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void IPv4Addr::set_allocated_ip(std::string* ip) {
  if (ip != nullptr) {
    
  } else {
    
  }
  ip_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ip,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:mediaservice.IPv4Addr.ip)
}

// uint32 port = 2;
inline void IPv4Addr::clear_port() {
  port_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 IPv4Addr::_internal_port() const {
  return port_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 IPv4Addr::port() const {
  // @@protoc_insertion_point(field_get:mediaservice.IPv4Addr.port)
  return _internal_port();
}
inline void IPv4Addr::_internal_set_port(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  port_ = value;
}
inline void IPv4Addr::set_port(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_port(value);
  // @@protoc_insertion_point(field_set:mediaservice.IPv4Addr.port)
}

// -------------------------------------------------------------------

// RecvAddrResponse

// repeated .mediaservice.IPv4Addr address = 1;
inline int RecvAddrResponse::_internal_address_size() const {
  return address_.size();
}
inline int RecvAddrResponse::address_size() const {
  return _internal_address_size();
}
inline void RecvAddrResponse::clear_address() {
  address_.Clear();
}
inline ::mediaservice::IPv4Addr* RecvAddrResponse::mutable_address(int index) {
  // @@protoc_insertion_point(field_mutable:mediaservice.RecvAddrResponse.address)
  return address_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::mediaservice::IPv4Addr >*
RecvAddrResponse::mutable_address() {
  // @@protoc_insertion_point(field_mutable_list:mediaservice.RecvAddrResponse.address)
  return &address_;
}
inline const ::mediaservice::IPv4Addr& RecvAddrResponse::_internal_address(int index) const {
  return address_.Get(index);
}
inline const ::mediaservice::IPv4Addr& RecvAddrResponse::address(int index) const {
  // @@protoc_insertion_point(field_get:mediaservice.RecvAddrResponse.address)
  return _internal_address(index);
}
inline ::mediaservice::IPv4Addr* RecvAddrResponse::_internal_add_address() {
  return address_.Add();
}
inline ::mediaservice::IPv4Addr* RecvAddrResponse::add_address() {
  ::mediaservice::IPv4Addr* _add = _internal_add_address();
  // @@protoc_insertion_point(field_add:mediaservice.RecvAddrResponse.address)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::mediaservice::IPv4Addr >&
RecvAddrResponse::address() const {
  // @@protoc_insertion_point(field_list:mediaservice.RecvAddrResponse.address)
  return address_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mediaservice

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_rtc_5fservices_2eproto