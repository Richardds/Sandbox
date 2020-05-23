#pragma once

#include <Precompiled.h>
#include <App/RenderApplication.h>

#include "Game/SandboxScene.h"

namespace Sandbox
{
	/// Sandbox application overrider class
	class SandboxApplication : public App::RenderApplication
	{
	public:
		SandboxApplication() = default;

		bool Open() override;
		void Close() override;

	protected:
		void OnProcessInput() override;
		void OnUpdateLogic() override;
		void OnUpdateFrame() override;

	private:
		std::shared_ptr<SandboxScene> _scene;
	};
}
