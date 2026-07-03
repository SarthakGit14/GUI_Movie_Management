#include "SignupScreen.h"
#include "AppState.h"
#include "AppData.h"
#include "imgui.h"

void DrawSignup()
{
    static char username[64] = "";
    static char password[64] = "";
    static char confirmPassword[64] = "";

    ImGui::SetNextWindowSize(ImVec2(450, 350), ImGuiCond_FirstUseEver);

    ImGui::Begin("Signup");

    ImGui::Text("Create a New Account");
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

    ImGui::Text("Confirm Password");
    ImGui::InputText("##confirm",
                     confirmPassword,
                     IM_ARRAYSIZE(confirmPassword),
                     ImGuiInputTextFlags_Password);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

   if(ImGui::Button("Create Account", ImVec2(180,45)))
{
    if(std::string(password) == std::string(confirmPassword))
    {
        if(manager.signup(username, password))
        {
            currentScreen = Screen::LOGIN;
        }
    }
}

    ImGui::SameLine();

    if(ImGui::Button("Back", ImVec2(120,40)))
    {
        currentScreen = Screen::LOGIN;
    }

    ImGui::End();
}