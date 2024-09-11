#include <iostream>
#include <boost/asio.hpp>

static const std::string Port = "1337";
static const std::string Address = "127.0.0.1";

int main(int main(int argc, char** argv)) {
	std::cout << "Starting a new client...\n";

	try {
		boost::asio::io_context ctx;
		boost::asio::ip::tcp::resolver resolver(ctx);
		const auto endpoints = resolver.resolve(Address, Port);
		boost::asio::ip::tcp::socket socket(ctx);
		boost::asio::connect(socket, endpoints);

		// we can now listen to messages

		// TODO: should there be a short delay to reduce computation load here?
		for (;;) {
			std::array<char, 128> buffer;
			boost::system::error_code error;

			auto length = socket.read_some(boost::asio::buffer(buffer), error);

			if (error == boost::asio::error::eof)	// end of file stream
			{
				// this is good -> appropriate closing of connection
				break; // simply break out of this infinite loop
			}
			if (error) {
				throw boost::system::system_error(error);	// throw an error that is not anticipated
			}

			std::cout.write(buffer.data(), length);	// output the data to the console
		}

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	system("pause");

	return 0;
}