#include<gtest/gtest.h>
#include<utilities.h>
#include<shaderLib.h>

//utilities
TEST(utilities_library, current_directory_test){
    EXPECT_TRUE((GetCurrentWorkingDir().find("gltest") != std::string::npos)) << GetCurrentWorkingDir();
}

TEST(utilities_library, gl_error_check){
    EXPECT_TRUE(GLLogCall("","",0));
}