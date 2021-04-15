// ----------------------------------------------------------------------------------------
//  \file       Precompiled.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

// C libraries
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

// C++ libraries
#include <chrono>
#include <fstream>
#include <functional>
#include <memory>
#include <random>
#include <string>
#include <regex>
#include <utility>
#include <unordered_map>
#include <vector>
#include <list>

// OpenGL related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Math library
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

// Texture library
#include <gli/gl.hpp>
#include <gli/gli.hpp>
#include <gli/load_dds.hpp>

// Mesh library
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// Physics library
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/ConstraintSolver/btConstraintSolver.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <LinearMath/btDefaultMotionState.h>

// Compile time configuration
#include "Config.h"

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
