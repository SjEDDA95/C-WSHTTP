#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <string>
#include <unordered_map>
#include <sstream>

std::string handleRequest(const std::string &request);
std::string handleGetRequest(const std::string &path);
std::string handleHeadRequest(const std::string &path);
std::string handlePostRequest(const std::string &path, std::istringstream &requestStream);
std::string handlePutRequest(const std::string &path, std::istringstream &requestStream);
std::string handleDeleteRequest(const std::string &path);
std::unordered_map<std::string, std::string> parseHeaders(std::istringstream &requestStream);

#endif // HANDLER_HPP
