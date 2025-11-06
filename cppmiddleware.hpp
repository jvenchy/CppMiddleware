#ifndef CPP_MIDDLEWARE_HPP
#define CPP_MIDDLEWARE_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>

//
// Basic request and response types
//
struct Request {
    std::string method = "GET";
    std::string path = "/";
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

struct Response {
    int status = 200;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

//
// Middleware function types
//
using Next = std::function<void()>;
using MiddlewareFunc = std::function<void(Request&, Response&, Next)>;

//
// MiddlewareChain class
//
class MiddlewareChain {
private:
    std::vector<MiddlewareFunc> middleware_;

public:
    void use(const MiddlewareFunc& func) {
        middleware_.push_back(func);
    }

    void handle(Request& req, Response& res) {
        execute(0, req, res);
    }

private:
    void execute(size_t index, Request& req, Response& res) {
        if (index >= middleware_.size()) return;

        auto next = [this, index, &req, &res]() {
            execute(index + 1, req, res);
        };

        middleware_[index](req, res, next);
    }
};

#endif // CPP_MIDDLEWARE_HPP
