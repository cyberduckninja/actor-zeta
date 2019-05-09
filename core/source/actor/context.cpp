#include <actor-zeta/actor/context.hpp>

namespace actor_zeta { namespace actor {

        context::~context() {
            if( ptr.get() != nullptr ){
                ptr.release();
            }

        }

        auto context::operator->() noexcept -> context_t * {
            return ptr.get();
        }

        auto context::operator->() const noexcept -> context_t * {
            return ptr.get();
        }

        auto context::operator*() noexcept -> context_t & {
            return *ptr.get();
        }

        auto context::operator*() const noexcept -> context_t & {
            return *ptr.get();
        }

        context::context(context_t *ptr, messaging::message &&msg) :
                ptr(ptr),
                msg(std::move(msg)) {

        }

        messaging::message& context::message() {
            return msg; /// TODO hack
        }

        const messaging::message &context::message() const {
            return msg;
        }

}}