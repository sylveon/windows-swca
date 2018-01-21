"use strict";

const native = require('../build/Release/swca.node');

const AccentState = Object.freeze({
    ACCENT_DISABLED: 0,
    ACCENT_ENABLE_TRANSPARENTGRADIENT: 2,
    ACCENT_ENABLE_BLURBEHIND: 3,
    ACCENT_ENABLE_FLUENT: 4
});

const SetWindowCompositionAttribute = (window, accent, color) => {
    if (window.getNativeWindowHandle) {
        window = window.getNativeWindowHandle();
    }
    if (!(window instanceof Buffer)) {
        throw "window is not a native window handle or BrowserWindow!";
    }

    if (!Object.values(AccentState).includes(accent)) {
        throw "accent is not a valid value! Expected one of AccentState.";
    }

    if (typeof color !== "number") {
        throw "color is not a number!";
    }

    // SetWindowCompositionAttribute expects the color it in AABBGGRR, so let's bitshift to it.
    color = ((color & 0x00FF0000) >> 16) + (color & 0xFF00FF00) + ((color & 0x000000FF) << 16);

    // Call the native function
    native.swca(window, accent, color);
};

module.exports = { SetWindowCompositionAttribute, AccentState };