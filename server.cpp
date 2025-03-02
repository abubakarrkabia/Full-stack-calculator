#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <iostream>
#include <sstream>

using namespace Pistache;

void handleCalculate(const Rest::Request& request, Http::ResponseWriter response) {
    auto a = std::stod(request.query().get("a").value());
    auto b = std::stod(request.query().get("b").value());
    std::string op = request.query().get("op").value();

    double result;
    if (op == "add") result = a + b;
    else if (op == "subtract") result = a - b;
    else if (op == "multiply") result = a * b;
    else if (op == "divide" && b != 0) result = a / b;
    else {
        response.send(Http::Code::Bad_Request, "Invalid operation");
        return;
    }

    std::ostringstream output;
    output << result;
    response.send(Http::Code::Ok, output.str());
}

int main() {
    Address addr(Ipv4::any(), Port(8080));
    Http::Endpoint server(addr);

    Rest::Router router;
    Rest::Routes::Get(router, "/calculate", Rest::Routes::bind(handleCalculate));

    server.init();
    server.setHandler(router.handler());
    std::cout << "Server running on port 8080..." << std::endl;
    server.serve();

    return 0;
}
