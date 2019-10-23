#pragma once

#include<iostream>
#include<tuple>


std::tuple<std::string, std::string> parseShader(const std::string& filePath);
unsigned int compileShader(unsigned int type, const std::string& source);
unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);