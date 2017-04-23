#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include "actor-zeta/intrusive_ptr.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief Basic actor implementation
///
//smart actor
        class actor {
        public:
            actor() = default;

            actor(const actor &a) = delete;

            actor(actor &&a) = default;

            actor &operator=(const actor &a) = delete;

            actor &operator=(actor &&a) = default;

            template<class T>
            explicit  actor(intrusive_ptr <T> ptr) : heart(std::move(ptr)) {}

            template<class T>
            explicit actor(T *ptr) : heart(ptr) {}

            template<class T>
            actor &operator=(intrusive_ptr <T> ptr) {
                actor tmp{std::move(ptr)};
                swap(tmp);
                return *this;
            }

            template<class T>
            actor &operator=(T *ptr) {
                actor tmp{ptr};
                swap(tmp);
                return *this;
            }

            actor_address address() const noexcept;

            ~actor();

            inline abstract_actor *operator->() const noexcept {
                return heart.get();
            }

            inline explicit operator bool() const noexcept {
                return static_cast<bool>(heart);
            }

            const std::string &type() const;

            inline bool operator!() const noexcept {
                return !heart;
            }

        private:

            void swap(actor &) noexcept;

            intrusive_ptr <abstract_actor> heart;
        };
    }
}
#endif