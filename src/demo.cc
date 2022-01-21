#include <camera.h>
#include <imgui.h>
#include <raylib.h>
#include <rlImGui.h>
#include <iostream>

struct Viewer {
  Camera3D camera;
  Vector2 previousMousePosition;

  Viewer(Vector3 camera_position, Vector3 camera_target, Vector3 camera_up,
         float FoV) {
    this->camera = (Camera3D){0};
    this->camera.position = camera_position;
    this->camera.target = camera_target;
    this->camera.up = camera_up;
    this->camera.fovy = FoV;
    this->camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(this->camera, CAMERA_CUSTOM);
  }

  void UpdateViewer() {
    Vector2 mousePositionDelta = {0.0f, 0.0f};
    Vector2 mousePosition = GetMousePosition();
    float mouseWheelMove = GetMouseWheelMove();

    mousePositionDelta.x = mousePosition.x - this->previousMousePosition.x;
    mousePositionDelta.y = mousePosition.y - this->previousMousePosition.y;

    this->previousMousePosition = mousePosition;
  }
};

int main(int argc, char *argv[]) {
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 1280;
  int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "Demo");
  SetTargetFPS(60);
  rlImGuiSetup(true);

  // setup initial camera data
  FreeCamera freeCam;
  Camera3D viewCam = {0};
  FreeCam_Init(&freeCam, (Vector3){0, 1, 0}, (Vector3){0, 1, 0});
  viewCam.fovy = 45;

  Vector2 lastMousePos = GetMousePosition();

  Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 delta = Vector2Subtract(GetMousePosition(), lastMousePos);
      FreeCam_RotateYaw(&freeCam, delta.x * -0.2f);
      FreeCam_RotatePitch(&freeCam, delta.y * 0.2f);
    }
    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
      Vector2 delta = Vector2Subtract(GetMousePosition(), lastMousePos);
      FreeCam_MoveRight(&freeCam, delta.x * -0.02f);
      FreeCam_MoveUp(&freeCam, delta.y * 0.02f);
    }
    if (GetMouseWheelMove() != 0) {
      FreeCam_MoveForward(&freeCam, GetMouseWheelMove() * 0.2f);
    }
    lastMousePos = GetMousePosition();

    if (IsKeyDown(KEY_ZERO)) {
      FreeCam_SetPosition(&freeCam, (Vector3){0, 10, 0});
      FreeCam_LookAt(&freeCam, (Vector3){0, 0, 0}, (Vector3){0, 0, 1});
    }

    FreeCam_ToCamera(&freeCam, &viewCam);
    std::cout << viewCam.position.x << " " << viewCam.position.y << " " << viewCam.position.z << "\n";
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(viewCam);

    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

    DrawGrid(10, 1.0f);

    EndMode3D();

    DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

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
