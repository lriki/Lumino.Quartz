
#include <Quartz\Application.h>


void AccessInstance(lnq::Application* app);

namespace lnq
{

Application::Application()
{
	AccessInstance(this);
}

Application::~Application()
{
}

void Application::OnInitialize()
{

}

} // namespace lnq