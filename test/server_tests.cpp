#include <gtest/gtest.h>
#include "../src/server.hpp"

using namespace https_server;

TEST(RequestHandlerTest, HandleValidRequest) {
	net::io_context ioc;
	ssl::context ctx{ ssl::context::tlsv12 };

	// SSL контекст	
	ctx.set_options(
		ssl::context::default_workarounds |
		ssl::context::no_sslv2 |
		ssl::context::single_dh_use);

	// Загружаем сертификат и приватный ключ
	ctx.use_certificate_chain_file("server.crt");
	ctx.use_private_key_file("server.key", ssl::context::pem);

	https_client::HttpsClient client{ ioc, ctx };
	client.request("localhost", "4433", "/index.html");
	
	EXPECT_TRUE(response.find("HTTP/1.1 200 OK") != std::string::npos);

}


