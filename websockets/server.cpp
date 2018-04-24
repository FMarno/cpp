#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(websocketpp::connection_hdl, server::message_ptr msg) {
  std::cout << msg->get_payload() << '\n';
}

class utility_server {
  server m_endpoint;

public:
  utility_server() {
    m_endpoint.set_error_channels(websocketpp::log::elevel::all);
    m_endpoint.set_access_channels(websocketpp::log::alevel::all ^
                                   websocketpp::log::alevel::frame_payload);
    m_endpoint.init_asio();
  }
  void run() {
    m_endpoint.set_message_handler(&on_message);
    m_endpoint.listen(9002);
    m_endpoint.start_accept();
    m_endpoint.run();
  }
};

int main() {
  std::cout << "hello" << '\n';
  utility_server s;
  s.run();
}

