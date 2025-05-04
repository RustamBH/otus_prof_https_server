#include <gtest/gtest.h>
#include "../src/server.hpp"

using namespace https_server;

TEST(RequestHandlerTest, HandleValidRequest) {
	http::request<http::dynamic_body> response_;

	response_.set(http::field::server, "Boost.Asio HTTPS Server");
	response_.set(http::field::content_type, "text/html");
	beast::ostream(response_.body()) << "Hello https\n";
	
	std::string response = get_response();
	
	EXPECT_TRUE(response.find("HTTP/1.1 Hello https OK") != std::string::npos);

}


