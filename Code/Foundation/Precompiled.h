// ----------------------------------------------------------------------------------------
//  \file       Precompiled.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <chrono>
#include <fstream>
#include <functional>
#include <memory>
#include <random>
#include <string>
#include <regex>
#include <unordered_map>
#include <utility>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gli/gl.hpp>
#include <gli/gli.hpp>
#include <gli/load_dds.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#ifdef _WIN32
#   ifdef DLL_EXPORT
#       define EXPORT __declspec(dllexport)
#   else
#       define EXPORT __declspec(dllimport)
#   endif
#else
#   define __stdcall
#   define __cdecl
#   define EXPORT
#endif

#pragma warning(disable:4251)
#pragma warning(disable:4275)
