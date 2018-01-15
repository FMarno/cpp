#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

void print(const boost::system::error_code&)
{
    std::cout << "hello asio two: electric boogaloo!" << '\n';
}

int main()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.async_wait(&print);
    io.run();
}
