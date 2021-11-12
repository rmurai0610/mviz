#include <imgui.h>
#include <raylib.h>
#include <rlImGui.h>
int main(int argc, char *argv[]) {
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 1280;
  int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight,
             "raylib-Extras [ImGui] example - simple ImGui Demo");
  SetTargetFPS(144);
  rlImGuiSetup(true);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    // start ImGui Conent
    rlImGuiBegin();

    // show ImGui Content
    bool open = true;
    ImGui::ShowDemoWindow(&open);

    // end ImGui Content
    rlImGuiEnd();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  rlImGuiShutdown();

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
