// ----------------------------------------------------------------------------------------
//  \file       Hardcoded.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Core/Singleton.h>
#include <Util/Generators/Generator.h>

namespace Sandbox
{
    /// Hardcoded mesh required by assignment
    class Hardcoded : public Util::Generator
    {
    _Singleton(Hardcoded)

    public:
        Hardcoded();

        std::shared_ptr<Graphics::Mesh> Generate() const;

    private:
        Graphics::VertexAttributeConfig _hardcodedAttributesTemplate;
    };
}
