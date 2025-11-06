# 🚀 CppMiddleware

### Composable request pipelines for modern C++ web servers

CppMiddleware is a lightweight, header-only middleware framework for C++ that brings the **Express.js-style middleware chain** to the world of **native C++ servers**.

It enables developers to build **clean, modular, and composable request handling pipelines**—perfect for embedding into any HTTP or networking server framework.

---

## 📖 Overview

CppMiddleware makes it easy to build and compose middleware functions like you would in Express.js:

```cpp
MiddlewareChain chain;

chain.use([](Request& req, Response& res, Next next) {
    std::cout << "Request received: " << req.path << std::endl;
    next();
});

chain.use([](Request& req, Response& res, Next next) {
    if (req.headers["Authorization"] != "secret") {
        res.status = 401;
        res.body = "Unauthorized";
        return;
    }
    next();
});

chain.use([](Request& req, Response& res, Next next) {
    res.status = 200;
    res.body = "Hello from CppMiddleware!";
});

chain.handle(req, res);
```

---

## ✨ Features

### 🧩 Core Features

* **Express-style middleware chaining** (`use`, `next`)
* **Request/Response abstractions** for easy data access
* **Lambda-friendly design** using `std::function`
* **Header-only** — just include and use
* **Pluggable** — works with any HTTP or TCP server

### ⚙️ Technical Highlights

* Zero external dependencies
* Exception-safe, memory-safe (RAII & smart pointers)
* Compatible with C++17 and above
* Simple, extensible API for custom middleware layers

---

## 🧠 Architecture

CppMiddleware follows a **chain-of-responsibility** design pattern:

```
Incoming Request
       ↓
[ Logging Middleware ]
       ↓
[ Authentication Middleware ]
       ↓
[ Routing Middleware ]
       ↓
[ Response Sent ]
```

Each middleware decides whether to:

* Handle the request itself, **or**
* Call the next middleware in the chain (`next()`)

---

## 🏗️ Installation

### Option 1: Clone directly

```bash
git clone https://github.com/<your-username>/CppMiddleware.git
```

Include the header in your project:

```cpp
#include "cppmiddleware.hpp"
```

### Option 2: Install system-wide

```bash
make install
```

Installs headers to `/usr/local/include/CppMiddleware/`

---

## 🚀 Quick Start

```cpp
#include "cppmiddleware.hpp"
#include <iostream>

int main() {
    MiddlewareChain chain;

    chain.use([](Request& req, Response& res, Next next) {
        std::cout << "Incoming request: " << req.path << std::endl;
        next();
    });

    chain.use([](Request& req, Response& res, Next next) {
        if (req.path == "/secret") {
            res.status = 403;
            res.body = "Forbidden";
            return;
        }
        next();
    });

    chain.use([](Request& req, Response& res, Next) {
        res.status = 200;
        res.body = "OK";
    });

    // Example simulated request
    Request req;
    req.path = "/hello";
    Response res;
    chain.handle(req, res);

    std::cout << "Response: " << res.status << " - " << res.body << std::endl;
}
```

Compile:

```bash
g++ -std=c++17 main.cpp -o main
./main
```

---

## 🧩 API Reference

### **Classes and Types**

#### `Request`

Represents an incoming request.

```cpp
struct Request {
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};
```

#### `Response`

Represents the outgoing response.

```cpp
struct Response {
    int status = 200;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};
```

#### `Next`

A function used to call the next middleware.

```cpp
using Next = std::function<void()>;
```

#### `MiddlewareFunc`

The signature of a middleware function.

```cpp
using MiddlewareFunc = std::function<void(Request&, Response&, Next)>;
```

#### `MiddlewareChain`

Main class that manages the middleware list and execution.

```cpp
class MiddlewareChain {
public:
    void use(MiddlewareFunc func);
    void handle(Request& req, Response& res);
};
```

---

## 🧱 Design Philosophy

CppMiddleware aims to:

* **Encourage clean modularity** in native web applications
* **Abstract complexity** of request handling
* Serve as a **core building block** for larger C++ frameworks (e.g., CppExpress, LiteServe++)

Its design follows the same principles as Node.js’s Express — but rewritten with **C++ idioms** like RAII, lambdas, and type safety.

---

## 🧪 Examples

### Logging Middleware

```cpp
chain.use([](Request& req, Response& res, Next next) {
    std::cout << "[" << req.method << "] " << req.path << std::endl;
    next();
});
```

### JSON Middleware (using nlohmann/json)

```cpp
chain.use([](Request& req, Response& res, Next next) {
    if (req.headers["Content-Type"] == "application/json") {
        auto data = nlohmann::json::parse(req.body);
        req.headers["json_name"] = data["name"];
    }
    next();
});
```

---

## 🔧 Future Enhancements

* [ ] Async middleware support (std::future / coroutines)
* [ ] Middleware composition utilities
* [ ] Built-in JSON request parsing
* [ ] Integration examples with HTTP libraries (Boost.Beast, cpp-httplib)
* [ ] Exception-safe middleware wrappers

---

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch
3. Add tests for new features
4. Submit a pull request 🚀

---

## 📄 License

MIT License © 2025 Josh Shergill

---
