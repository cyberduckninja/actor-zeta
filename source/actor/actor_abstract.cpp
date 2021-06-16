#include <iostream>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

    actor_abstract::~actor_abstract() {
    }

    actor_abstract::actor_abstract(std::string type)
        : communication_module(std::move(type), sub_type_t::actor) {
    }

}} // namespace actor_zeta::base
