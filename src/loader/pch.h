#pragma once
#define _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
#define NOMINMAX 1

#pragma warning( push )
#pragma warning( disable : 26495 26451)
#include "json/json.hpp"
#include "curl/curl.h"
#include "log/LoggerFunctions.h"
#pragma warning( pop )

#include <string>
#include <shlobj_core.h>
#include <filesystem>
#include <fstream>
#include <utility>
#include <Windows.h>
