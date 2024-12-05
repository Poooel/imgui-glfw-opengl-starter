#include <Backend.h>
#include <imgui.h>

int main() {
    Backend backend([] { ImGui::ShowDemoWindow(); });
    backend.startLoop();
    return 0;
}
