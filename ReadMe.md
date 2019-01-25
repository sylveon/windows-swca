# windows-swca

Wraps the Windows 10 undocumented SetWindowCompositionAttribute API, which allows to render windows with a blurry, acrylic or transparent background effect.

## Tips for usage on Electron

For best user and developer experience, **do not set** `transparent` to `true`. It has many shortcomings, such as no support for maximised window state and shadows. Instead set `backgroundColor` to `#00000000`.

Setting `frame` to `false` and creating custom window decorations is also recommended, the selected transparency effect will bleed over native window decorations if not.