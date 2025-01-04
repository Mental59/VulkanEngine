#include <iostream>
#include <format>
#include <exception>
#include "app/helloTriangleApp.hpp"

int main()
{
	try
	{
		HelloTriangleApplication app;
		app.run();
	}
	catch (const std::exception& error)
	{
		std::cerr << std::format("APPLICATION TERMINATED, {}\n", error.what());
		return 1;
	}

	return 0;
}
