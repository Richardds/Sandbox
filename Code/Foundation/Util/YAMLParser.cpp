// ----------------------------------------------------------------------------------------
//  \file       YAMLParser.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Util/YAMLParser.h"

#include "Core/Exception/ParsingException.h"
#include "Core/Exception/UnsupportedException.h"

Util::YAMLParser::YAMLParser() :
    _throwOnEmptyNode(true),
    _throwOnInvalidType(true)
{
}

void Util::YAMLParser::ValidateNode(const YAML::Node& node, const YAML::NodeType::value type) const
{
    if (this->_throwOnEmptyNode && !node)
    {
        throw Core::ParsingException("Invalid node");
    }
    if (this->_throwOnInvalidType && type != node.Type())
    {
        throw Core::ParsingException("Invalid node type");
    }
}

void Util::YAMLParser::ValidateVersion(const YAML::Node& versionNode, const int version) const
{
    this->ValidateNode(versionNode, YAML::NodeType::Scalar);
    
    if (version != versionNode.as<int>())
    {
        throw Core::UnsupportedException("Unsupported scene format");
    }
}

Math::Vector2f Util::YAMLParser::ParseVector2f(const YAML::Node& node) const
{
    this->ValidateNode(node, YAML::NodeType::Sequence);

    return Math::Vector2f(
        this->Parse<float>(node[0]),
        this->Parse<float>(node[1])
    );
}

Math::Vector3f Util::YAMLParser::ParseVector3f(const YAML::Node& node) const
{
    this->ValidateNode(node, YAML::NodeType::Sequence);

    return Math::Vector3f(
        this->Parse<float>(node[0]),
        this->Parse<float>(node[1]),
        this->Parse<float>(node[2])
    );
}
