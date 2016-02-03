
#include <Quartz/Application.h>

class Application : public lnq::Application
{
public:
	Application();
	virtual ~Application();
	virtual void OnInitialize() override;
};
