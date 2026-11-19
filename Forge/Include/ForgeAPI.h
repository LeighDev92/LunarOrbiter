#pragma once

#ifdef FORGE_EXPORTS
#define FORGE_API __declspec(dllexport)
#else
#define FORGE_API __declspec(dllimport)
#endif
