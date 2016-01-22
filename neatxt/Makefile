CFLAGS   += `pkg-config --cflags glfw3`
CXXFLAGS += $(CFLAGS)
CXXFLAGS += -std=c++14
LDLIBS   += `pkg-config --libs glfw3 glu`

neatxt: imgui.o imgui_demo.o imgui_draw.o
