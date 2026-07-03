#include "DashboardScreen.h"
#include "AppState.h"
#include "AppData.h"

#include "imgui.h"

#include <cstring>
#include <string>
#include <vector>

void DrawDashboard()
{
    static char search[128] = "";
    static int selectedMovie = 1;

    std::vector<Movie>& movies = manager.getMovies();

    ImGui::SetNextWindowSize(ImVec2(1100,650), ImGuiCond_FirstUseEver);

    ImGui::Begin("Movie Rental Management System");

    ImGui::TextColored(
        ImVec4(0.25f,0.70f,1.0f,1.0f),
        "Movie Rental Management System");

    ImGui::Separator();
    ImGui::Spacing();

    ImGui::SetNextItemWidth(350);

    ImGui::InputTextWithHint(
        "##search",
        "Search movies...",
        search,
        IM_ARRAYSIZE(search));

    ImGui::Spacing();

    //--------------------------------------------------
    // LEFT PANEL
    //--------------------------------------------------

    ImGui::BeginChild(
        "MovieList",
        ImVec2(620,520),
        true);

    ImGui::Text("Available Movies");
    ImGui::Separator();
    ImGui::Spacing();

    if(ImGui::BeginTable(
            "Movies",
            5,
            ImGuiTableFlags_Borders |
            ImGuiTableFlags_RowBg |
            ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Title");
        ImGui::TableSetupColumn("Genre");
        ImGui::TableSetupColumn("Rating");
        ImGui::TableSetupColumn("Status");

        ImGui::TableHeadersRow();

        for(auto &movie : movies)
        {
            if(strlen(search) > 0)
            {
                if(movie.getTitle().find(search) == std::string::npos)
                    continue;
            }

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", movie.getId());

            ImGui::TableSetColumnIndex(1);

            if(ImGui::Selectable(
                    movie.getTitle().c_str(),
                    selectedMovie == movie.getId(),
                    ImGuiSelectableFlags_SpanAllColumns |
                    ImGuiSelectableFlags_AllowDoubleClick))
            {
                selectedMovie = movie.getId();
            }

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", movie.getGenre().c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%.1f", movie.getRating());

            ImGui::TableSetColumnIndex(4);

            if(movie.isAvailable())
            {
                ImGui::TextColored(
                    ImVec4(0.2f,0.85f,0.3f,1.0f),
                    "Available");
            }
            else
            {
                ImGui::TextColored(
                    ImVec4(1.0f,0.25f,0.25f,1.0f),
                    "Rented");
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();

    ImGui::SameLine();

    //--------------------------------------------------
    // RIGHT PANEL
    //--------------------------------------------------

    ImGui::BeginChild(
        "Details",
        ImVec2(420,520),
        true);

    ImGui::Text("Movie Details");
    ImGui::Separator();
    ImGui::Spacing();

    Movie* current = nullptr;

    for(auto &movie : movies)
    {
        if(movie.getId() == selectedMovie)
        {
            current = &movie;
            break;
        }
    }

    if(current)
    {          ImGui::TextDisabled("Title");
        ImGui::BulletText("%s", current->getTitle().c_str());

        ImGui::Spacing();

        ImGui::TextDisabled("Genre");
        ImGui::BulletText("%s", current->getGenre().c_str());

        ImGui::Spacing();

        ImGui::TextDisabled("Rating");
        ImGui::BulletText("%.1f / 5", current->getRating());

        ImGui::Spacing();

        ImGui::TextDisabled("Rent Price");
        ImGui::BulletText("Rs %d", current->getRentPrice());

        ImGui::Spacing();

        ImGui::TextDisabled("Purchase Price");
        ImGui::BulletText("Rs %d", current->getBuyPrice());

        ImGui::Spacing();

        ImGui::TextDisabled("Status");

        if(current->isAvailable())
        {
            ImGui::TextColored(
                ImVec4(0.2f,0.85f,0.3f,1.0f),
                "Available");
        }
        else
        {
            ImGui::TextColored(
                ImVec4(1.0f,0.25f,0.25f,1.0f),
                "Already Rented");
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if(current->isAvailable())
        {
            if(ImGui::Button("Rent", ImVec2(320,45)))
            {
                manager.rentMovie(current->getId());
            }

            ImGui::Spacing();

            if(ImGui::Button("Purchase", ImVec2(320,45)))
            {
                manager.purchaseMovie(current->getId());

                if(selectedMovie > 0 && !movies.empty())
                    selectedMovie = movies.front().getId();
            }
        }
        else
        {
            ImGui::BeginDisabled();

            ImGui::Button("Rent", ImVec2(320,45));

            ImGui::Spacing();

            ImGui::Button("Purchase", ImVec2(320,45));

            ImGui::EndDisabled();
        }

        ImGui::Spacing();

        if(ImGui::Button("Return", ImVec2(320,45)))
        {
            manager.returnMovie(current->getId());
        }
    }

    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::Separator();

    ImGui::SetCursorPosX(
        ImGui::GetWindowWidth() - 160
    );

    if(ImGui::Button("Logout", ImVec2(130,45)))
    {
        currentScreen = Screen::LOGIN;
    }

    ImGui::End();
}