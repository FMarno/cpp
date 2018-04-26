#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server& endpoint, websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    std::cout << msg->get_payload() << '\n';
    endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
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
      m_endpoint.set_message_handler(
          [this](auto hdl, auto msg) { on_message(m_endpoint, hdl, msg); });
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

