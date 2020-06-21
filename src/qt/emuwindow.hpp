#ifndef EMUWINDOW_HPP
#define EMUWINDOW_HPP
#include <QMainWindow>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>

#include <cstdint>

#include "emuthread.hpp"
#include "settingswindow.hpp"

enum HID_PAD_STATE
{
    PAD_A,
    PAD_B,
    PAD_SELECT,
    PAD_START,
    PAD_RIGHT,
    PAD_LEFT,
    PAD_UP,
    PAD_DOWN,
    PAD_R,
    PAD_L,
    PAD_X,
    PAD_Y
};

class EmuWindow : public QMainWindow
{
    Q_OBJECT
    private:
        EmuThread emuthread;
        SettingsWindow* settings_window;
        bool running;
        QImage top_image, bottom_image;

        uint16_t pad_state;

        bool touchscreen_pressed;
        uint16_t touchscreen_x, touchscreen_y;

        void press_key(HID_PAD_STATE state);
        void release_key(HID_PAD_STATE state);

        void init_menu_bar();

        void boot_emulator(QString cart_path);
    public:
        EmuWindow();

        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        void closeEvent(QCloseEvent* event) override;

        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;

        void paintEvent(QPaintEvent* event) override;
    public slots:
        void display_boot_error(QString message);
        void draw(uint8_t* top_screen, uint8_t* bottom_screen);
        void display_emu_error(QString message);
};

#endif // EMUWINDOW_HPP
