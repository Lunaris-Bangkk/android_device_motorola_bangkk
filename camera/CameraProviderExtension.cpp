/*
 * Copyright (C) 2024 LibreMobileOS Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CameraProviderExtension.h"

#include <fstream>

#define TORCH_BRIGHTNESS_NODE \
    "/sys/devices/platform/soc/5c1b000.qcom,cci0/5c1b000.qcom,cci0:qcom,camera-flash@0/torch_brightness"

/**
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

/**
 * Read value from the path and close file.
 */
template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

bool supportsTorchStrengthControlExt() {
    return true;
}

int32_t getTorchDefaultStrengthLevelExt() {
    return 100;
}

int32_t getTorchMaxStrengthLevelExt() {
    return 255;
}

int32_t getTorchStrengthLevelExt() {
    int32_t val = get(std::string(TORCH_BRIGHTNESS_NODE), -1);
    return (val <= 0) ? getTorchDefaultStrengthLevelExt() : val;
}

void setTorchStrengthLevelExt(int32_t torchStrength) {
    set(std::string(TORCH_BRIGHTNESS_NODE), torchStrength);
}
