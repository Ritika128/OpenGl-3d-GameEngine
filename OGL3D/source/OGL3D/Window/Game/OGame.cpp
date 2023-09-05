#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();
	

	m_display->makeCurrentContext();
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(1, 0, 0, 1));


	m_display->present(false);
}

void OGame::onQuit()
{
}

void OGame::quit()
{
	m_isRunning = false;
}
