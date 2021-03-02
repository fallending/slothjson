/*
 * @Author: your name
 * @Date: 2021-03-02 15:00:50
 * @LastEditTime: 2021-03-02 15:02:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /slothjson/include/jsontypedefs.h
 */

#include "slothjson.h"

// ----------------------------------
// Meta macro
// ----------------------------------

#define mt_macro_first_( A, ... )                           A
#define mt_macro_first(...)                                 mt_macro_first_( __VA_ARGS__, 0 )

#define mt_macro_concat_( A, B )                            A##B
#define mt_macro_concat( A, B )                             mt_macro_concat_( A, B )

// 偏移取数
#define mt_macro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...)   mt_macro_first(__VA_ARGS__)
#define mt_macro_at(N, ...)                                 mt_macro_concat(mt_macro_at, N)( __VA_ARGS__ )

#define mt_macro_count(...)                                 mt_macro_at( 16, __VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 )
#define mt_macro_count_dec(...)                             mt_macro_at( 16, __VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 ) // 总参数个数减一

#define mt_macro_join0( ... )
#define mt_macro_join1( A )                                 A
#define mt_macro_join2( A, B )                              A##____##B
#define mt_macro_join3( A, B, C )                           A##____##B##____##C
#define mt_macro_join4( A, B, C, D )                        A##____##B##____##C##____##D
#define mt_macro_join5( A, B, C, D, E )                     A##____##B##____##C##____##D##____##E
#define mt_macro_join6( A, B, C, D, E, F )                  A##____##B##____##C##____##D##____##E##____##F
#define mt_macro_join7( A, B, C, D, E, F, G )               A##____##B##____##C##____##D##____##E##____##F##____##G
#define mt_macro_join8( A, B, C, D, E, F, G, H )            A##____##B##____##C##____##D##____##E##____##F##____##G##____##H
#define mt_macro_join( ... )                                mt_macro_concat(mt_macro_join, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

#define mt_macro_cstr( A )                                  mt_macro_cstr_( A )
#define mt_macro_cstr_( A )                                 #A

// ----------------------------------
// Mutation type
// ----------------------------------

namespace slothjson {

typedef bool MtBool;
typedef int8_t MtInt8;
typedef int16_t MtInt16;
typedef int32_t MtInt32;
typedef int64_t MtInt64;
typedef double MtDouble;
typedef std::map<std::string, std::string> MtMap;
typedef std::vector<int32_t> MtArray;
typedef std::string MtString;

#define MtBoolDefault true
#define MtInt8Default 0
#define MtInt16Default 0 
#define MtInt32Default 0 
#define MtInt64Default 0 
#define MtDoubleDefault 0.0f
#define MtMapDefault {}
#define MtArrayDefault {}
#define MtStringDefault ""

}

// ----------------------------------
// Json struct
// ----------------------------------

#define mt_field(type, field) \
public: \
    type field; \
    void skip_##field() { __skip_##field = true; } \
    bool json_has_##field() const { return __json_has_##field; } \
private: \
    bool __skip_##field; \
    bool __json_has_##field; \
    void init_##field() { __skip_##field = false; __json_has_##field = true; field = type##Default; }

#define mt_struct_begin(name) \
struct name \
{

#define mt_struct_end(name) \
public: \
    name(); \
    name& operator=(const name& obj_val); \
    bool operator==(const name& obj_val) const; \
    bool encode(allocator_t& alloc, rapidjson::Value& json_val) const; \
    bool decode(const rapidjson::Value& json_val); \
}; \
bool encode(const name& obj_val, allocator_t& alloc, rapidjson::Value& json_val); \
bool decode(const rapidjson::Value& json_val, name& obj_val);

#define mt_def_field_encode_1( a ) \
if (!__skip_##a && !encode_field(a, #a, alloc, json_val)) break;
#define mt_def_field_encode_2( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_3( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_4( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_5( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_6( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_7( a, ...) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_8( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_9( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )
#define mt_def_field_encode_10( a, ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_encode_1( a )

#define mt_def_field_encode( ... ) \
mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)


#define mt_def_field_decode_1( a ) \
if (!decode_field(json_val, #a, a, __json_has_##a)) break;
#define mt_def_field_decode_2( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_3( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_4( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_5( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_6( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_7( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_8( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_9( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )
#define mt_def_field_decode_10( a, ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
mt_def_field_decode_1( a )

#define mt_def_field_decode( ... ) \
mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

#define mt_def_struct( name, ...) \
bool name::encode(allocator_t& alloc, rapidjson::Value& json_val) const \
{ \
    do \
    { \
        json_val.SetObject(); \
        mt_def_field_encode( __VA_ARGS__ ) \
        return true; \
    } while (0); \
    return false; \
} \
bool name::decode(const rapidjson::Value& json_val) \
{ \
    do \
    { \
        mt_def_field_decode( __VA_ARGS__ ) \
        return true; \
    } while (0); \
    return false; \
} \
bool encode(const name& obj_val, allocator_t& alloc, rapidjson::Value& json_val) \
{ \
    return obj_val.encode(alloc, json_val); \
} \
bool decode(const rapidjson::Value& json_val, name& obj_val) \
{ \
    return obj_val.decode(json_val); \
}