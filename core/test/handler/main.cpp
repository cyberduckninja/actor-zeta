#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/actor/context.hpp>
#include <actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>

#include <iostream>
#include <actor-zeta/core.hpp>

using actor_zeta::actor::make_handler;
using actor_zeta::actor::context;

class dummy_context final : public context {
public:
    dummy_context(actor_zeta::messaging::message msg) : message_(std::move(msg)) {}

    ~dummy_context() override = default;

    auto addresses(actor_zeta::detail::string_view) -> actor_zeta::actor::actor_address & override {
        return address_;
    }

    auto self() -> actor_zeta::actor::actor_address override {
        return address_;
    };

    auto current_message() -> actor_zeta::messaging::message & override {
        return message_;
    };
private:
    actor_zeta::actor::actor_address address_;
    actor_zeta::messaging::message message_;
};

int main() {
    actor_zeta::actor::actor_address address_tmp;
    auto* ptr_1 = make_handler(
            [](context&){
                std::cerr << "ptr_1"  << std::endl;
            }

    );

    dummy_context tmp_1 (actor_zeta::make_message(address_tmp,"",6));

    ptr_1->invoke(tmp_1);

    auto* ptr_2 =  make_handler(
            [](context&, int& data ){
                std::cerr << "ptr_2" << data << std::endl;
            }

    );

    dummy_context tmp_2 (actor_zeta::make_message(address_tmp,"",6));

    ptr_2->invoke(tmp_2);


    auto* ptr_3 = make_handler(
            [](context&, int& data_1 , int& data_2  ){
                std::cerr << "ptr_3" << data_1 << "" << data_2 << std::endl;
            }

    );

    dummy_context tmp_3 (actor_zeta::make_message(address_tmp,"",6,7));

    ptr_3->invoke(tmp_3);

    return 0;
}