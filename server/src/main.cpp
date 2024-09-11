#include "networking-tcp/networking-tcp.h"

namespace constant
{
	static const std::string Port = "1337";
	static constexpr tcp::Server::IpVersion IpVersion = tcp::Server::IpVersion::IPV4;
}

int main(int argc, char** argv) {
	// create a server
	boost::asio::io_context ctx;

	// order matters; create the server first and then start the io context
	auto server = tcp::Server::Create(ctx,constant::Port, constant::IpVersion);
	ctx.run();

	return 0;
}