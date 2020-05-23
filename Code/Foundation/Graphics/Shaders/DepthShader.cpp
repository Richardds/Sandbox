// ----------------------------------------------------------------------------------------
//  \file       DepthShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Shaders/DepthShader.h"

Graphics::DepthShader::DepthShader() :
	ShaderSystem("Depth"),
	_projectionPosition(-1)
{
}

void Graphics::DepthShader::InitializeUniformVariables()
{
	this->InitializeMatrix4fLocation("transformation", Math::Matrix4f(1.0f), this->_projectionPosition);
}

void Graphics::DepthShader::LoadProjection(const Math::Matrix4f& transformation) const
{
	this->LoadMatrix4f(this->_projectionPosition, transformation);
}
