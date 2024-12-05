#include "Backend.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

Backend::Backend(
    const std::function<void()>& mainLoop,
    const std::function<void()>& postInitialization,
    const std::function<void()>& preFinalization,
    const std::function<void()>& postFinalization
)
    : mainLoop(mainLoop),
      preFinalization(preFinalization),
      postFinalization(postFinalization) {
    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor*       primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode    = glfwGetVideoMode(primary);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    window = glfwCreateWindow(mode->width, mode->height, "OpenGL + GLFW", nullptr, nullptr);
    if (window == nullptr) {
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    postInitialization();
}

Backend::~Backend() {
    preFinalization();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    postFinalization();
}

void Backend::startLoop() const {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        mainLoop();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}
