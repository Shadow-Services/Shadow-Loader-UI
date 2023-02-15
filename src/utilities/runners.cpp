#include <globals.hpp>

void runner::status_worker()
{
	while (g.worker.status_worker) {
		g.login.g_status = std::string(GetStatus());
		//printf("[INFO] Status: %s\n", std::string(GetStatus()));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void runner::login_worker()
{
	if (Login()) {
		g.worker.status_worker = false;
		g.window.logged_in = true;
		g.login.g_status = "Welcome " + std::string(GetUsername());
	}

	else {
		MessageBoxA(0, "Login failed", "Shadow", true);
	}
}

void runner::injection_worker(char* mod)
{
	if (Inject(mod, false)) {
		g.worker.status_worker = false;
		g.worker.injecting = false;
		MessageBoxA(0, "Injection successful, please enjoy your game.", "Shadow Client - Inject", MB_OK);
	}

	else {
		MessageBoxA(0, "[ERROR] Injection failed, please check logs or open a support ticket.", "Shadow Client - Inject", MB_OK);
	}
}

bool runner::module_callback(void* data, int n, const char** out_text)
{
	const std::vector<std::string>* v = (std::vector<std::string>*)data;
	*out_text = (*v)[n].c_str();
	return true;
}

std::size_t runner::write_callback(char* in, size_t size, size_t nmemb, std::string* out)
{
	std::size_t total_size = size * nmemb;
	if (total_size) {
		out->append(in, total_size);
		return total_size;
	}
	return 0;
}