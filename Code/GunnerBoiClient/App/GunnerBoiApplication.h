#pragma once

#include <memory>
#include <App/RenderApplication.h>

#include "../Game/GunnerBoiScene.h"

namespace GunnerBoi
{
	class GunnerBoiApplication : public App::RenderApplication
	{
	public:
		GunnerBoiApplication();

		bool Open() override;
		void Close() override;

	protected:
		void OnProcessInput() override;
		void OnUpdateLogic() override;
		void OnUpdateFrame() override;

	private:
		std::shared_ptr<GunnerBoiScene> _scene;
	};
}
