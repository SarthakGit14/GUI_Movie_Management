#include "LoginScreen.h"
#include "AppState.h"
#include "AppData.h"
#include "imgui.h"

void DrawLogin()
{
    static char username[64] = "";
static char password[64] = "";

ImGuiViewport* viewport = ImGui::GetMainViewport();

ImGui::SetNextWindowPos(
    viewport->GetCenter(),
    ImGuiCond_Always,
    ImVec2(0.5f, 0.5f));

ImGui::SetNextWindowSize(
    ImVec2(450, 320),
    ImGuiCond_Always);
    ImGui::Begin("Movie Rental Management System");

ImGui::SetCursorPosX(90);
ImGui::Text("Movie Rental Management System");

ImGui::Spacing();
ImGui::Separator();
ImGui::Spacing();
 

    ImGui::Text("Username");
    ImGui::InputText("##username",
                     username,
                     IM_ARRAYSIZE(username));

    ImGui::Spacing();

    ImGui::Text("Password");
    ImGui::InputText("##password",
                     password,
                     IM_ARRAYSIZE(password),
                     ImGuiInputTextFlags_Password);

    ImGui::Spacing();

   float buttonWidth = (ImGui::GetContentRegionAvail().x - 10.0f) / 2.0f;

if (ImGui::Button("Login", ImVec2(buttonWidth, 45)))
{
    if(manager.login(username, password))
{
    if(manager.getCurrentUser()->isAdmin())
    {
        currentScreen = Screen::ADMIN;
    }
    else
    {
        currentScreen = Screen::DASHBOARD;
    }
}

else
{
    ImGui::OpenPopup("Login Failed");
}
}

ImGui::SameLine();

if (ImGui::Button("Signup", ImVec2(buttonWidth, 45)))
{
    currentScreen = Screen::SIGNUP;
}
    ImGui::Spacing();
    ImGui::Separator();

    ImGui::Text("Version 1.0");
    if(ImGui::BeginPopupModal("Login Failed",
                          nullptr,
                          ImGuiWindowFlags_AlwaysAutoResize))
{
    ImGui::Text("Invalid username or password.");

    if(ImGui::Button("OK"))
    {
        ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
}

    ImGui::End();
}