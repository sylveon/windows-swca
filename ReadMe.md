# windows-swca

Invoke like this:

```js
const swca = require('window-swca');
swca.SetWindowCompositionAttribute(myWindow, myEffect, myColor);
```

Where the first parameter can either be an Electron `BrowserWindow` or a window handle stored as `Buffer`.

Second parameter is one of `ACCENT_DISABLED`, `ACCENT_ENABLE_TRANSPARENTGRADIENT`, `ACCENT_ENABLE_BLURBEHIND` or `ACCENT_ENABLE_FLUENT` from the module's `AccentState` export. `ACCENT_ENABLE_FLUENT` only works on Windows Insider build 17063 or higher as of January 2018.

Third parameter is just a color in the format `0xAARRGGBB`.

## Tips for usage on Electron

For best user and developer experience, **do not set** `transparent` to `true`. It has many shortcomings, such as no support for maximised window state and shadows. Instead set `backgroundColor` to `#00000000`.

Setting `frame` to `false` and creating custom window decorations is also recommended, the selected transparency effect will bleed over native window decorations if not.