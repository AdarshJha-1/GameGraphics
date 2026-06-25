#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

class Shape
{
public:
    int cx;
    int cy;

    int red;
    int green;
    int blue;
    int alpha;

    int vx;
    int vy;

    bool isMoving = false;

    virtual void
    Draw(SDL_Renderer *renderer) = 0;
};

class Circle : public Shape
{
public:
    int radius;

    Circle(int cx, int cy, int radius, int red, int blue, int green, int alpha, int vx, int vy)
    {
        this->radius = radius;
        this->cx = cx;
        this->cy = cy;
        this->vx = vx;
        this->vy = vy;
        this->red = red;
        this->blue = blue;
        this->green = green;
        this->alpha = alpha;
    }

    void Draw(SDL_Renderer *renderer) override
    {
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        for (int y = -radius; y <= radius; y++)
        {
            for (int x = -radius; x <= radius; x++)
            {
                if (x * x + y * y <= radius * radius)
                {
                    SDL_RenderDrawPoint(renderer, cx + x, cy + y);
                }
            }
        }
    }

    void Move()
    {
        // now i need to learn collision detection

        this->cx += vx;
        this->cy += vy;

        // LEFT
        if (this->cx - this->radius <= 0)
        {
            vx = -vx;
        }

        // RIGHT
        if (this->cx + this->radius >= WINDOW_WIDTH)
        {
            vx = -vx;
        }

        // TOP
        if (this->cy - this->radius <= 0)
        {
            vy = -vy;
        }

        // DOWN
        if (this->cy + this->radius >= WINDOW_HEIGHT)
        {
            vy = -vy;
        }
    }
};

class Rectangle : public Shape
{
};

int main(int argc, char const *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return -1;
    }

    window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Circle
    Circle c1(100, 100, 50, 255, 0, 0, 255, 1, 1);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            ImGui_ImplSDL2_ProcessEvent(&event);
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Shape Controller");

        ImGui::SliderInt("Radius", &c1.radius, 1, 300);
        ImGui::Checkbox("Move", &c1.isMoving);

        ImGui::SliderInt("Center X", &c1.cx, 0 + c1.radius, 1080 - c1.radius);
        ImGui::SliderInt("Center Y", &c1.cy, 0 + c1.radius, 720 - c1.radius);

        ImGui::SliderInt("VX", &c1.vx, -10, 10);
        ImGui::SliderInt("VY", &c1.vy, -10, 10);

        ImGui::SliderInt("Red", &c1.red, 0, 255);
        ImGui::SliderInt("Green", &c1.green, 0, 255);
        ImGui::SliderInt("Blue", &c1.blue, 0, 255);
        ImGui::SliderInt("Alpha", &c1.alpha, 0, 255);

        ImGui::End();
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 60, 56, 54, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

        c1.Draw(renderer);

        if (c1.isMoving)
        {
            c1.Move();
        }

        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
