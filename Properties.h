#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

#include <Arduino.h>
#include <FS.h>

#define CONFIG_FILE "/config.prop"

bool getValue(String path, String key, String &value);
bool setValue(String path, String key, String value);

#endif  // __PROPERTIES_H__
