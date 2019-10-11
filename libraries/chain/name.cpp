#include <eosio/chain/name.hpp>
#include <fc/variant.hpp>
#include <boost/algorithm/string.hpp>
#include <fc/exception/exception.hpp>
#include <eosio/chain/exceptions.hpp>

namespace eosio { namespace chain { 

   void name::set( const char* str ) {
      bool has_tail;
      const auto len = get_length(str, &has_tail);

      ACC_ASSERT(len <= 13 || (has_tail && len <= 17), name_type_exception, "Name is longer than 13 characters (${name}) ", ("name", string(str)));
      value = string_to_name(str);
      ACC_ASSERT(to_string() == string(str), name_type_exception,
                 "Name not properly normalized (name: ${name}, normalized: ${normalized}) ",
                 ("name", string(str))("normalized", to_string()));
   }

   size_t name::get_length(const char *str, bool *has_tail) {
       const auto tail_len = strnlen(name_tail.c_str(), 5);
       const auto len = strnlen(str, 14 + tail_len);

       //ilog("name get_length ${name_tail} ${len} ${tail_len}",("name_tail",name_tail) ("len",len) ("tail_len",tail_len));
       if(len < tail_len + 1)
       {
           *has_tail = false;
       }else{
           *has_tail = (string(str).compare(len-tail_len-1, tail_len, name_tail) != 0);
       }

       return len;
   }

   // keep in sync with name::to_string() in contract definition for name
   name::operator string()const {
     static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

      string str(13,'.');

      bool has_tail = false;
      uint64_t tmp = value;
      for( uint32_t i = 0; i <= 12; ++i ) {
          if(i==0){
              if((tmp & 0x0f) ==0x0f){
                  has_tail = true;
                  str[12-i] = '.';
              }
              else{
                  char c = charmap[tmp & 0x0f];
                  str[12-i] = c;
              }
              tmp >>= 4;
          }else{
              char c = charmap[tmp & 0x1f];
              str[12-i] = c;
              tmp >>= 5;
          }
      }

      boost::algorithm::trim_right_if( str, []( char c ){ return c == '.'; } );

      //ilog("name string ${has_tail} ${str} ${name_tail}",("has_tail",has_tail)("str",str)("name_tail",name_tail));
      return has_tail ? str + name_tail : str;
   }

} } /// eosio::chain

namespace fc {
  void to_variant(const eosio::chain::name& c, fc::variant& v) { v = std::string(c); }
  void from_variant(const fc::variant& v, eosio::chain::name& check) { check = v.get_string(); }
} // fc
