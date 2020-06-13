/* Name: Margaret Coleman
 * Student ID: 
 * Last Updated: Nov. 2, 2017
 * CSC 473 Assignment 2- Lagrange
 */
#include <atlas/utils/Application.hpp>
#include <atlas/utils/WindowSettings.hpp>
#include <atlas/gl/ErrorCheck.hpp>

#include "Scene.hpp"

int main()
{
    using atlas::utils::WindowSettings;
    using atlas::utils::ContextVersion;
    using atlas::utils::Application;
    using atlas::utils::ScenePointer;
    using assignment2::Scene;

    atlas::gl::setGLErrorSeverity(ATLAS_GL_ERROR_SEVERITY_HIGH | 
        ATLAS_GL_ERROR_SEVERITY_MEDIUM);

    WindowSettings settings;
    settings.contextVersion = ContextVersion(4, 1);
    settings.isForwardCompat = true;
    settings.isMaximized = true;

    Application::getInstance().createWindow(settings);
    Application::getInstance().addScene(ScenePointer(new Scene));
    Application::getInstance().runApplication();

    return 0;
}
