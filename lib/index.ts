const native: any = require("../build/Release/swca.node");

/**
 * The possible accents.
 */
export enum ACCENT_STATE {
    /**
     * Default accent. No transparency, background is black.
     */
    ACCENT_DISABLED = 0,

    /**
     * Background is determined by color. (alpha channel ignored)
     */
    ACCENT_ENABLE_GRADIENT = 1,

    /**
     * Background is determined by color.
     */
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,

    /**
     * Background is determined by color, with a blur for transparent areas.
     */
    ACCENT_ENABLE_BLURBEHIND = 3,

    /**
     * Background is determined by color, with an acrylic blur for transparent areas.
     * Note that the module will replace an alpha of 0 with an alpha of 1 (out of 255)
     * because Windows has bugs with a fully transparent alpha.
     */
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,

    /**
     * Behavior unknown, left for completeness's sake.
     */
    ACCENT_ENABLE_HOSTBACKDROP = 5,

    /**
     * Fully transparent background.
     * Note that this tends to be buggy and to change value across Windows versions
     * (for example it was initially the value of {@link ACCENT_STATE#ACCENT_ENABLE_ACRYLICBLURBEHIND})
     * so it is more reliable to use {@link ACCENT_STATE#ACCENT_ENABLE_TRANSPARENTGRADIENT} with an alpha of 0.
     * (you also get the benefit of less bugs)
     */
    ACCENT_INVALID_STATE = 6
}

/**
 * Sets a window's composition attribute
 * @param window The target window.
 * @param accent The desired accent.
 * @param color The background color in 0xRRGGBBAA
 */
export function SetWindowCompositionAttribute(window: Buffer, accent: ACCENT_STATE, color: number) {
    // SetWindowCompositionAttribute expects the color it in AABBGGRR, so let's bitshift to it from RRGGBBAA.
    const red   = (color & 0xFF000000) >> 24;
    const blue  = (color & 0x00FF0000) >> 16;
    const green = (color & 0x0000FF00) >> 8;
    let alpha   = (color & 0x000000FF) >> 0;

    // Acrylic is buggy with a full alpha but ok with an alpha of 1.
    if (alpha === 0 && accent === ACCENT_STATE.ACCENT_ENABLE_ACRYLICBLURBEHIND) {
        alpha = 1;
    }

    // Call the native function
    return native.swca(window, accent, (alpha << 24) + (blue << 16) + (green << 8) + red);
};