#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

typedef bool (*t_Login)();
typedef bool (*t_Logout)();
typedef char* (*t_Status)();
typedef char* (*t_Username)();
typedef char* (*t_Modules)();
typedef bool (*t_Inject)(char* moduleName, bool __ignore);

extern t_Login Login;
extern t_Logout Logout;
extern t_Status GetStatus;
extern t_Username GetUsername;
extern t_Modules GetModules;
extern t_Inject Inject;

extern bool g_loggedIn;