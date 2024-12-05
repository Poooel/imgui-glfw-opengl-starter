#pragma once

#include "GLFW/glfw3.h"

#include <functional>

class Backend {
    public:
        explicit Backend(
            const std::function<void()>& mainLoop,
            const std::function<void()>& postInitialization = [] {},
            const std::function<void()>& preFinalization    = [] {},
            const std::function<void()>& postFinalization   = [] {}
        );
        ~Backend();

        void startLoop() const;

    private:
        std::function<void()> mainLoop;
        std::function<void()> preFinalization;
        std::function<void()> postFinalization;

        GLFWwindow* window;
};
