# windows-swca

Wraps Windows 10's undocumented `SetWindowCompositionAttribute` API, which allows to render a window with a blurry, acrylic or transparent background effect.

## Dependencies

This module only depends on a [properly set up Windows build environment](https://github.com/Microsoft/nodejs-guidelines/blob/master/windows-environment.md#environment-setup-and-configuration).

## Screenshots

![](https://i.imgur.com/yFjenBw.png)
![](https://i.imgur.com/t2I4dyU.png)
![](https://i.imgur.com/cgE6UzN.png)

*Note: all the applications showed above except Terminus do not use this module, they have been personally modified by me*

## Documentation

There's no fancy docs website for now, but every publically facing API component is documented using JSDoc, so a quick look in the source or your IDE's autocomplete and info tips should give you all need.

## Tips for usage on Electron

Don't forget to install `electron-rebuild` from NPM if not already done and to run `npx electron-rebuild` after installing to avoid ABI version mismatch issues.

For best user and developer experience, **do not set** `transparent` to `true` in your browser create options. It has many shortcomings, such as no support for maximised window state and shadows. Instead set `backgroundColor` to `#00000000`.

Setting `frame` to `false` and creating custom window decorations is also recommended, the selected transparency effect will bleed over native window decorations if not.