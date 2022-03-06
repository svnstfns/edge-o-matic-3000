#ifndef __User_Interface_h
#define __User_Interface_h

#include "config.h"

#define BUTTON_HEIGHT 9
#define BUTTON_WIDTH 42 // (SCREEN_WIDTH / 3)
#define BUTTON_START_Y (SCREEN_HEIGHT - BUTTON_HEIGHT)

#define CHART_START_Y 20
#define CHART_END_Y (SCREEN_HEIGHT - BUTTON_HEIGHT - 2)
#define CHART_HEIGHT (CHART_END_Y - CHART_START_Y)
#define CHART_START_X 2
#define CHART_END_X (SCREEN_WIDTH)
#define CHART_WIDTH (CHART_END_X - CHART_START_X)

#define STATUS_SIZE 16
#define TOAST_WIDTH 18
#define TOAST_LINES 4

#define WIFI_ICON_IDX 0
#define SD_ICON_IDX 1
#define RECORD_ICON_IDX 2
#define UPDATE_ICON_IDX 3

#include "DisplayPolyfill.hpp"
#include "UIMenu.h"
#include <functional>

#include "eom-hal.h"
#include <string>

typedef std::function<void(void)> ButtonCallback;
typedef std::function<void(int)> RotaryCallback;

typedef struct {
    uint8_t status = 0;
    long flash_delay = 0;
    long last_flash = 0;
    bool show = false;
    // uint8_t *icon = nullptr;
} UIIcon;

typedef struct {
    bool show = false;
    char text[7] = "";
    ButtonCallback fn = nullptr;
} UIButton;

class UserInterface {
  public:
    bool begin(u8g2_t* display);
    void tick();

    // Common Element Drawing Functions
    void drawChartAxes();
    void drawChart(int peakLimit);
    void drawStatus(const char* status = nullptr);
    void drawPattern(int start_x, int start_y, int width, int height, int pattern = 2,
                     int color = 1);

    // Chart Data
    void addChartReading(int index, int value);
    void setMotorSpeed(uint8_t perc);

    // Render Controls
    void fadeTo(uint8_t color = 0, bool half = false);
    void clear(bool render = true);
    void render();
    void displayOff() { display_on = false; }
    void displayOn() { display_on = true; }

    // Icons
    void drawWifiIcon(uint8_t strength = 255, long flash_ms = 0);
    void drawSdIcon(uint8_t status = 255, long flash_ms = 0);
    void drawRecordIcon(uint8_t status = 255, long flash_ms = 0);
    void drawUpdateIcon(uint8_t status = 255, long flash_ms = 0);
    void drawIcon(uint8_t icon_idx, uint8_t icon[][8], uint8_t status, long flash_ms);
    void drawIcons();

    // Buttons
    void clearButtons();
    void clearButton(uint8_t i);
    void setButton(uint8_t i, const char* text, ButtonCallback fn = nullptr);
    void drawButtons();
    void onKeyPress(uint8_t i);
    void onEncoderChange(int value);

    // Toast
    void toast(const char* message, long duration = 3000, bool allow_clear = true);
    void toast(std::string message, long duration = 3000, bool allow_clear = true);
    void toastNow(const char* message, long duration = 3000, bool allow_clear = true);
    void toastNow(std::string message, long duration = 3000, bool allow_clear = true);
    void toastProgress(const char* message, float progress);
    void toastProgress(std::string message, float progress);
    void drawToast();
    bool toastRenderPending();
    bool hasToast();

    // Basic UI Elements
    void drawCompactBar(int x, int y, int width, int value, int maximum = 255, int lowerValue = 0,
                        int lowerMaximum = 255);
    void drawBar(int y, char label, int value, int maximum, int limit = 0, int peak = 0);

    // Menu Handling
    void openMenu(UIMenu* menu, bool save_history = true, bool reenter = true, void* arg = nullptr);
    UIMenu* closeMenu();
    bool isMenuOpen();
    bool isPreviousMenu(UIMenu* m) {
        return current_menu != nullptr && current_menu->isPreviousMenu(m);
    }

    // Debug
    void screenshot(char* outpath, size_t len);

    u8g2_t* display_ptr;
    DisplayPolyfill* display;

  private:
    bool display_on = true;
    bool initialized = false;

    // Chart Data:
    int chartReadings[2][CHART_WIDTH] = {{0}, {0}};
    uint8_t chartCursor[2] = {0, 0};

    // Buttons
    UIButton buttons[3];

    // Header Data
    char status[STATUS_SIZE + 1] = {0};
    UIIcon icons[4];

    // Toast Data
    char toast_message[(TOAST_WIDTH * TOAST_LINES) + 1] = "";
    long toast_expiration = 0;
    bool toast_render_pending = false;
    bool toast_allow_clear = true;

    // Menu
    UIMenu* current_menu = nullptr;
};

extern UserInterface UI;

#endif