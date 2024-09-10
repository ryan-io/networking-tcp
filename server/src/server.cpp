#include "server/server.h"
#include "networking-tcp/networking-tcp.h"

void DebugServer::Log(const char* msg) {
	using namespace tcp;
	boost::asio::io_context ctx;
	Server::Connection c = Server::Create("1337", ctx, Server::IPV4);
}