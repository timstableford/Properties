#include <Arduino.h>
#include <FS.h>

#include "Properties.h"

bool getValue(String path, String key, String &value) {
    File file = SPIFFS.open(path, "r");
    if (file) {
        String line;
        do {
            line = file.readStringUntil('\n');
            if (line.length() > 0) {
                if (line.indexOf('=') > 0) {
                    if (line.substring(0, line.indexOf('=')).equals(key)) {
                        value = line.substring(line.indexOf('=') + 1,
                                               line.length());
                        file.close();
                        return true;
                    }
                }
            }
        } while (line.length() > 0);

        file.close();
    }
    return false;
}

bool setValue(String path, String key, String value) {
    File original = SPIFFS.open(path, "r");

    File config = SPIFFS.open(path + "~", "w+");
    if (!config) {
        original.close();
        return false;
    }

    bool found = false;

    if (original) {
        String line;
        do {
            line = original.readStringUntil('\n');
            if (line.length() > 0) {
                if (line.indexOf('=') > 0) {
                    if (line.substring(0, line.indexOf('=')).equals(key)) {
                        config.printf("%s=%s\n", key.c_str(), value.c_str());
                        found = true;
                    } else {
                        config.printf("%s\n", line.c_str());
                    }
                }
            }
        } while (line.length() > 0);
    }

    if (!found) {
        config.printf("%s=%s\n", key.c_str(), value.c_str());
    }

    if (original) {
        original.close();
        SPIFFS.remove(path);
    }
    config.close();

    SPIFFS.rename(path + "~", path);

    return true;
}
