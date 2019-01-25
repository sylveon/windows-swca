# windows-swca

Wraps the Windows 10 undocumented SetWindowCompositionAttribute API, which allows to render a window with a blurry, acrylic or transparent background effect.

![](https://i.imgur.com/yFjenBw.png)
![](https://i.imgur.com/t2I4dyU.png)
![](https://i.imgur.com/cgE6UzN.png)

*Note: all the applications showed above except Terminus do not use this module, they have been personally modified by me*

## Tips for usage on Electron

For best user and developer experience, **do not set** `transparent` to `true` in your browser create options. It has many shortcomings, such as no support for maximised window state and shadows. Instead set `backgroundColor` to `#00000000`.

Setting `frame` to `false` and creating custom window decorations is also recommended, the selected transparency effect will bleed over native window decorations if not.