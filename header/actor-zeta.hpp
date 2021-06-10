#pragma once

// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>

namespace actor_zeta {

    using base::abstract_actor;
    using base::actor;
    using base::actor_address;
    using base::basic_async_actor;
    using base::context;
    using base::make_handler;
    using base::supervisor_t;
    using base::supervisor;

    using executor::abstract_executor;
    using executor::executable;
    using executor::execution_device;
    using executor::executor_t;
    using executor::work_sharing;

    using base::message_ptr;

    template<class T>
    auto make_message(actor_address sender_, T name) -> message_ptr {
        return message_ptr(new base::message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_message(actor_address sender_, T name, Arg&& arg) -> message_ptr {
        return message_ptr(new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<class T, typename... Args>
    auto make_message(actor_address sender_, T name, Args&&... args) -> message_ptr {
        return message_ptr(new base::message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...}))));
    }

    template<
        typename Actor,
        typename Supervisor,
        typename... Args>
    auto join(Supervisor* supervisor, Args&&... args) -> actor_zeta::actor_address {
        return supervisor->join(new Actor(supervisor, std::forward<Args>(args)...));
    }

    template<typename Sender, typename... Args>
    void send(Sender& a1, Args... args) {
        a1->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename Sender, typename... Args>
    void send(const Sender& a1, Args... args) {
        a1->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<class Sender, class Message>
    void send(const Sender& actor, Message msg) {
        actor->enqueue(std::move(msg));
    }

    template<class Sender, class Message>
    void send(Sender& actor, Message msg) {
        actor->enqueue(std::move(msg));
    }

    inline void link_imp(actor_zeta::actor_address& a1, actor_zeta::actor_address& a2) {
        send(a1, a2, "add_link", a2);
        send(a2, a1, "add_link", a1);
    }

    inline void link(basic_async_actor& actor1, basic_async_actor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor* actor1, Supervisor* actor2) {
        auto a1 = actor1->address();
        auto a2 = actor2->address();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, Supervisor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, actor_address& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2->address();
        link_imp(a1, a2);
    }

    inline void link(actor_address& actor1, actor_address& actor2) {
        link_imp(actor1, actor2);
    }

    template<class Supervisor, class... Args>
    auto spawn_actor(supervisor_t*, Args&&... args) -> supervisor {
        return new Supervisor(std::forward<Args>(args)...);
    }

    template<class Supervisor, class... Args>
    auto spawn_actor(supervisor&, Args&&... args) -> supervisor {
        return new Supervisor(std::forward<Args>(args)...);
    }

    template<class Supervisor, class... Args>
    auto spawn_supervisor(supervisor_t*, Args&&... args) -> Supervisor {
    }

    template<class Supervisor, class... Args>
    auto spawn_supervisor(supervisor&, supervisor&, Args&&... args) -> Supervisor {
    }

} // namespace actor_zeta