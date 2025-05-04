#include <gtest/gtest.h>
#include "../src/server.hpp"

using namespace https_server;

TEST(Empty, Empty) 
{
    // Arrange
	//

    // Act
	//

    // Assert
    ASSERT_EQ(true, true);
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
