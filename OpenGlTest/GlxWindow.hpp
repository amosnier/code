#include <GL/glew.h>
#include <GL/glx.h>

class GlxWindow {
public:
	GlxWindow();
	~GlxWindow();
	void test();
private:
	static bool isExtensionSupported(const char *extList, const char *extension);
	static int ctxErrorHandler(Display *dpy, XErrorEvent *ev);

	static bool ctxErrorOccurred;
	Display *display;
	GLXContext ctx;
	Window win;
	Colormap cmap;
};
