#pragma once

#include <memory>
#include <App/RenderApplication.h>

#include "../Game/SandboxScene.h"

namespace Sandbox
{
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
