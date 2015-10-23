#include "nsfw.h"
#include "Assets.h"
#include "TestApp.h"

int main(char* args) {
	TestApp app;

	app.init();
	app.play();
	app.term();

	nsfw::Assets::instance().init();
	return 0;
}
