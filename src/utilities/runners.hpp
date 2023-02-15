#pragma once
#include <globals.hpp>

class runner
{
public:
	static void status_worker();
	static void login_worker();
	static void injection_worker(char* mod);
	static bool module_callback(void* data, int n, const char** out_text);
	static std::size_t write_callback(char* in, size_t size, size_t nmemb, std::string* out);
};