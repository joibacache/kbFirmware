/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>
#include "kbConfig.h"
#include "keymap.h"

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    scanMatrix();
  }
}

bool keystates[ROWS][COLS];

void scanMatrix()
{
    for (uint8_t i = 0; i < ROWS; i++)
    {
        pinMode(ROW_PINS[i], INPUT);
    }

    for (uint8_t col = 0; col < COLS; col++)
    {
        pinMode(COL_PINS[col], OUTPUT);
        digitalWrite(COL_PINS[col], HIGH);

        for (uint8_t row = 0; row < ROWS; row++)
        {
            bool pressedKeyState = digitalRead(ROW_PINS[row]);
            if (pressedKeyState != keystates[row][col])
            {
                keystates[row][col] = pressedKeyState;
                if (pressedKeyState)
                {
                    //TODO: INCLUDE
                    bleKeyboard.press('1');
                    //String str = "Pressed : (";
                    //Serial.println(str + (row + 1) + ":" + (col + 1) + ")(" + ROW_PINS[row] + ":" + COL_PINS[col] + ")(" + KEYMAP[row][col] + ")");
                    keystates[row][col] = true;
                    delay(50); // for debounce -- have to check with key matrix
                }
                else
                {
                    bleKeyboard.releaseAll();
                    keystates[row][col] = false;
                }
            }
        }
        digitalWrite(COL_PINS[col], LOW);
        pinMode(COL_PINS[col], INPUT);
    }
}
