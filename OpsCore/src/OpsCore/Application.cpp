#include "Application.h"
#include "OpsCore/Events/ApplicationEvent.h"
#include "OpsCore/Log.h"

namespace oc {

	Application::Application() {

	}

	Application::~Application() {}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryInput)) {
			OC_TRACE(e);
		} else {
			OC_INFO(e);
		}
		

		while (true);
	}

}