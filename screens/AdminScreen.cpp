#include "AdminScreen.h"
#include "AppState.h"
#include "AppData.h"

#include "imgui.h"

static bool movieAdded = false;
static bool movieRemoved = false;
void DrawAdmin()
{
    static char title[128] = "";
    static char genre[64] = "";

    static float rating = 0.0f;
    static int rentPrice = 0;
    static int buyPrice = 0;

    static int removeId = 0;

    ImGui::SetNextWindowSize(
        ImVec2(700,650),
        ImGuiCond_FirstUseEver);

    ImGui::Begin("Admin Dashboard");

    ImGui::TextColored(
        ImVec4(0.25f,0.7f,1,1),
        "Administrator Panel");

    ImGui::Separator();
    ImGui::Spacing();

    //---------------------------------------
    // Statistics
    //---------------------------------------
    //---------------------------------------


    ImGui::Text("Total Movies      : %d",
        manager.totalMovies());

    ImGui::Text("Available Movies  : %d",
        manager.availableMovies());

    ImGui::Text("Rented Movies     : %d",
        manager.rentedMovies());

    ImGui::Text("Registered Users  : %d",
        manager.totalUsers());

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();



    // Registered Users
//---------------------------------------

ImGui::TextColored(
    ImVec4(0.25f,0.7f,1.0f,1.0f),
    "Registered Users");

ImGui::Separator();

auto users = manager.getUsers();

if(ImGui::BeginTable(
        "UsersTable",
        3,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_SizingStretchProp))
{
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn("Username");
    ImGui::TableSetupColumn("Role");

    ImGui::TableHeadersRow();

    for(const auto &user : users)
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("%d", user.getId());

        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%s", user.getUsername().c_str());

        ImGui::TableSetColumnIndex(2);

        if(user.isAdmin())
            ImGui::TextColored(ImVec4(1.0f,0.85f,0.2f,1.0f),"Admin");
        else
            ImGui::Text("User");
    }

    ImGui::EndTable();
}

ImGui::Spacing();

ImGui::TextColored(
    ImVec4(0.25f,0.7f,1,1),
    "Rental History");

ImGui::Separator();

auto history = manager.getRentalHistory();

if(ImGui::BeginTable(
        "RentalHistory",
        4,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_SizingStretchProp))
{
    ImGui::TableSetupColumn("User");
    ImGui::TableSetupColumn("Movie");
    ImGui::TableSetupColumn("Date");
    ImGui::TableSetupColumn("Status");

    ImGui::TableHeadersRow();

    for(auto &r : history)
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("%s", r.username.c_str());

        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%s", r.movie.c_str());

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("%s", r.rentDate.c_str());

        ImGui::TableSetColumnIndex(3);

        if(r.status=="Rented")
            ImGui::TextColored(
                ImVec4(1,0.4f,0,1),
                "Rented");
        else
            ImGui::TextColored(
                ImVec4(0,1,0,1),
                "Returned");
    }

    ImGui::EndTable();
}

ImGui::Spacing();
ImGui::Separator();
ImGui::Spacing();

ImGui::TextColored(
    ImVec4(0.25f,0.7f,1.0f,1.0f),
    "Purchase History");

ImGui::Separator();

auto purchases = manager.getPurchases();

if(ImGui::BeginTable(
        "PurchaseHistory",
        3,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_SizingStretchProp))
{
    ImGui::TableSetupColumn("User");
    ImGui::TableSetupColumn("Movie");
    ImGui::TableSetupColumn("Purchase Date");

    ImGui::TableHeadersRow();

    for(const auto &p : purchases)
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("%s", p.username.c_str());

        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%s", p.movie.c_str());

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("%s", p.purchaseDate.c_str());
    }

    ImGui::EndTable();
}
ImGui::Separator();
ImGui::Spacing();

    //---------------------------------------
    // Add Movie
    //---------------------------------------

    ImGui::InputText(
        "Title",
        title,
        IM_ARRAYSIZE(title));

    ImGui::InputText(
        "Genre",
        genre,
        IM_ARRAYSIZE(genre));

    ImGui::InputFloat(
        "Rating",
        &rating);

    ImGui::InputInt(
        "Rent Price",
        &rentPrice);

    ImGui::InputInt(
        "Purchase Price",
        &buyPrice);

    ImGui::Spacing();

   if(ImGui::Button("Add Movie", ImVec2(200,45)))
{
    // Input validation
    if(strlen(title) == 0 || strlen(genre) == 0)
    {
        ImGui::OpenPopup("Invalid Input");
    }
    else
    {
        manager.addMovie(
            Movie(
                0,
                title,
                genre,
                rating,
                true,
                rentPrice,
                buyPrice));

        movieAdded = true;

        title[0] = '\0';
        genre[0] = '\0';

        rating = 0;
        rentPrice = 0;
        buyPrice = 0;
    }
}
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    //---------------------------------------
    // Remove Movie
    //---------------------------------------

    ImGui::InputInt(
        "Movie ID",
        &removeId);

    if(ImGui::Button("Remove Movie", ImVec2(200,45)))
{
    if(manager.removeMovie(removeId))
    {
        movieRemoved = true;
        removeId = 0;
    }
}
    ImGui::Spacing();

if(movieAdded)
{
    ImGui::OpenPopup("Movie Added");
    movieAdded = false;
}
if(ImGui::BeginPopupModal(
        "Movie Added",
        nullptr,
        ImGuiWindowFlags_AlwaysAutoResize))
{
    ImGui::Text("Movie added successfully.");

    if(ImGui::Button("OK"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}

if(ImGui::BeginPopupModal(
        "Invalid Input",
        nullptr,
        ImGuiWindowFlags_AlwaysAutoResize))
{
    ImGui::Text("Title and Genre cannot be empty.");

    if(ImGui::Button("OK"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}

if(movieRemoved)
{
    ImGui::OpenPopup("Movie Removed");
    movieRemoved = false;
}

if(ImGui::BeginPopupModal(
        "Movie Removed",
        nullptr,
        ImGuiWindowFlags_AlwaysAutoResize))
{
    ImGui::Text("Movie removed successfully.");

    if(ImGui::Button("OK"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}
    ImGui::Separator();

    if(ImGui::Button(
        "Logout",
        ImVec2(120,40)))
    {
        manager.logout();
        currentScreen = Screen::LOGIN;
    }

    ImGui::End();
}