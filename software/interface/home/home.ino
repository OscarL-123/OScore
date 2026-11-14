// OScore home screen for the LILYGO T-Watch S3 Plus.

#include <LilyGoLib.h>
#include <LV_Helper.h>

// Make a simple colored rectangle on the current screen.
// x and y are its top-left position; width and height are measured in pixels.
static lv_obj_t *addBlock(int x, int y, int width, int height, uint32_t color)
{
    lv_obj_t *block = lv_obj_create(lv_screen_active());
    lv_obj_remove_style_all(block); // Remove the default padding, border, and rounded corners.
    lv_obj_set_pos(block, x, y);
    lv_obj_set_size(block, width, height);
    lv_obj_set_style_bg_color(block, lv_color_hex(color), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(block, LV_OPA_COVER, LV_PART_MAIN);
    return block;
}

// Make a text label. Keeping this in one helper means each screen item needs only a short call.
static lv_obj_t *addText(const char *text, int x, int y, int width, int height,
                         const lv_font_t *font, uint32_t color,
                         lv_text_align_t alignment, int letterSpacing)
{
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, width, height);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(color), LV_PART_MAIN);
    lv_obj_set_style_text_align(label, alignment, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(label, letterSpacing, LV_PART_MAIN);
    return label;
}

static void drawHomeScreen()
{
    // These colors define the restrained arcade palette.
    const uint32_t background = 0x0C111B; // Deep blue-black
    const uint32_t cyan       = 0x56F4E7; // Main arcade glow
    const uint32_t amber      = 0xFFB547; // Small highlight
    const uint32_t muted      = 0x91A6B2; // Quiet supporting text

    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(background), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);

    // Four small corner marks make a simple arcade-style frame.
    addBlock(23, 34, 12, 3, cyan);
    addBlock(23, 34, 3, 12, cyan);
    addBlock(205, 34, 12, 3, cyan);
    addBlock(214, 34, 3, 12, cyan);
    addBlock(23, 203, 12, 3, cyan);
    addBlock(23, 194, 3, 12, cyan);
    addBlock(205, 203, 12, 3, cyan);
    addBlock(214, 194, 3, 12, cyan);

    // OScore sits in a small title plate near the top-left corner.
    lv_obj_t *brandPlate = lv_obj_create(screen);
    lv_obj_set_pos(brandPlate, 34, 26);
    lv_obj_set_size(brandPlate, 62, 22);
    lv_obj_set_style_bg_color(brandPlate, lv_color_hex(0x151F2B), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(brandPlate, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_color(brandPlate, lv_color_hex(0x344553), LV_PART_MAIN);
    lv_obj_set_style_border_width(brandPlate, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(brandPlate, 3, LV_PART_MAIN);
    lv_obj_set_style_pad_all(brandPlate, 0, LV_PART_MAIN);
    lv_obj_clear_flag(brandPlate, LV_OBJ_FLAG_SCROLLABLE);
    addText("OSCORE", 34, 30, 62, 16, &lv_font_montserrat_12, 0xE6F4F5,
            LV_TEXT_ALIGN_CENTER, 1);

    // Battery outline, terminal, and fill bar. The 82% value is a placeholder.
    lv_obj_t *batteryOutline = lv_obj_create(screen);
    lv_obj_set_pos(batteryOutline, 165, 31);
    lv_obj_set_size(batteryOutline, 25, 12);
    lv_obj_set_style_bg_opa(batteryOutline, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_color(batteryOutline, lv_color_hex(0x8A9CA9), LV_PART_MAIN);
    lv_obj_set_style_border_width(batteryOutline, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(batteryOutline, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_all(batteryOutline, 0, LV_PART_MAIN);
    lv_obj_clear_flag(batteryOutline, LV_OBJ_FLAG_SCROLLABLE);
    addBlock(191, 34, 3, 6, 0x8A9CA9);
    addBlock(168, 34, 15, 6, amber);
    addText("82%", 194, 28, 25, 18, &lv_font_montserrat_10, amber,
            LV_TEXT_ALIGN_RIGHT, 0);

    // Date and time are fixed sample text until we connect them to the watch's clock.
    addText("SAT / 14 NOV", 30, 68, 180, 22, &lv_font_montserrat_12, muted,
            LV_TEXT_ALIGN_CENTER, 2);
    addText("09:41", 5, 99, 230, 66, &lv_font_montserrat_48, cyan,
            LV_TEXT_ALIGN_CENTER, -2);

    // Small status marker and year complete the lower part of the face.
    addBlock(72, 177, 96, 1, 0x253B48);
    addBlock(105, 188, 30, 4, amber);
    addText("2026", 45, 196, 150, 20, &lv_font_montserrat_12, muted,
            LV_TEXT_ALIGN_CENTER, 2);
}

void setup()
{
    Serial.begin(115200);

    // LILYGO's library initializes the watch hardware and its screen.
    instance.begin();

    // LVGL is the graphics library used to place text and shapes on the screen.
    beginLvglHelper(instance);

    drawHomeScreen();
}

void loop()
{
    // LVGL needs regular turns to draw and refresh the display.
    lv_timer_handler();
    delay(5);
}
