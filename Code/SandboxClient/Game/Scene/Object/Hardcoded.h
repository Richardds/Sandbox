// ----------------------------------------------------------------------------------------
//  \file       Hardcoded.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
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

        [[nodiscard]] std::shared_ptr<Graphics::Mesh> Generate();

    private:
        Graphics::VertexAttributeConfig _hardcodedAttributesTemplate;
    };
}
