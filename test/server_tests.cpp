#include <gtest/gtest.h>
#include "../src/server.hpp"

using namespace https_server;

TEST(RequestHandlerTest, HandleValidRequest) {
      // SSL контекст
      ssl::context ctx{ ssl::context::tlsv12 };
      ctx.set_options(
          ssl::context::default_workarounds |
          ssl::context::no_sslv2 |
          ssl::context::single_dh_use);

      // Загружаем сертификат и приватный ключ
      ctx.use_certificate_chain_file("server.crt");
      ctx.use_private_key_file("server.key", ssl::context::pem);

      // IO контекст
      net::io_context ioc{ threads };

      // Создаем и запускаем сервер
      https_server::http_server server{ ioc, ctx, tcp::endpoint{"127.0.0.1", "4433"}, "./www" , static_cast<std::size_t>(4) };
      
      server.start();
	
	http::request<http::dynamic_body> response_;

	response_.set(http::field::server, "Boost.Asio HTTPS Server");
	response_.set(http::field::content_type, "text/html");
	beast::ostream(response_.body()) << "Hello https\n";

	http_connection conn{};
	std::string response = server.write_response();
	
	EXPECT_TRUE(response.find("HTTP/1.1 Hello https OK") != std::string::npos);

}


