/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#pragma once

#include <eosio/chain/types.hpp>
#include <eosio/chain/contract_types.hpp>

namespace eosio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_acc_newaccount(apply_context&);
   void apply_acc_updateauth(apply_context&);
   void apply_acc_deleteauth(apply_context&);
   void apply_acc_linkauth(apply_context&);
   void apply_acc_unlinkauth(apply_context&);

   /*
   void apply_acc_postrecovery(apply_context&);
   void apply_acc_passrecovery(apply_context&);
   void apply_acc_vetorecovery(apply_context&);
   */

   void apply_acc_setcode(apply_context&);
   void apply_acc_setabi(apply_context&);

   void apply_acc_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace eosio::chain
