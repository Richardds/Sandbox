// ----------------------------------------------------------------------------------------
//  \file       Random.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Vector.h"

namespace Util
{
    /// YAML library utilities for parsing various internal types
    class EXPORT YAMLParser
    {
    public:
        YAMLParser();
        virtual ~YAMLParser() = default;

    protected:

        void ValidateNode(const YAML::Node& node, YAML::NodeType::value type) const;
        void ValidateVersion(const YAML::Node& versionNode, int version) const;
        template<typename T>
        T Parse(const YAML::Node& node) const;
        Math::Vector2f ParseVector2f(const YAML::Node& node) const;
        Math::Vector3f ParseVector3f(const YAML::Node& node) const;
        
        bool _throwOnEmptyNode;
        bool _throwOnInvalidType;
    };

    template <typename T>
    T YAMLParser::Parse(const YAML::Node& node) const
    {
        this->ValidateNode(node, YAML::NodeType::Scalar);

        return node.as<T>();
    }
}
