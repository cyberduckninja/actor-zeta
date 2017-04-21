#ifndef ACTOR_ADDRESS_HPP
#define ACTOR_ADDRESS_HPP


#include "actor-zeta/intrusive_ptr.hpp"
#include "abstract_actor.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief This represents an actor's address container
///
        class actor_address final {
        public:
            actor_address() = default;

            actor_address(actor_address &&) = default;

            actor_address(const actor_address &) = default;

            actor_address &operator=(actor_address &&) = default;

            actor_address &operator=(const actor_address &) = default;

            explicit actor_address(abstract_actor *aa) : ptr_(aa) {};

            ~actor_address();

            inline abstract_actor *operator->() const noexcept {
                return ptr_.get();
            }

            inline explicit operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

            inline bool operator!() const noexcept {
                return !ptr_;
            }

        private:
            intrusive_ptr<abstract_actor> ptr_;
        };
    }
}
#endif //ACTOR_ADDRESS_HPP
