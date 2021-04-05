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

#ifndef WIN32
#define __stdcall
#define __cdecl
#endif
