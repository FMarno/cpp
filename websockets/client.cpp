#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

void on_message(client& c, websocketpp::connection_hdl hdl, message_ptr msg)
{
    std::cout << msg->get_payload() << std::endl;

    websocketpp::lib::error_code ec;
    c.send(hdl, msg->get_payload(), msg->get_opcode(), ec);
    if (ec)
    {
        std::cout << ec.message() << std::endl;
    }
}

int main()
{
    client c;
    std::string uri = "ws://localhost:9002";

    c.set_access_channels(websocketpp::log::alevel::all);
    c.clear_access_channels(websocketpp::log::alevel::frame_payload);

    c.init_asio();

    c.set_message_handler([&c](auto hdl, auto msg) { on_message(c, hdl, msg); });
}
