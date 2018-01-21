/// <reference types='@types/node'/>
/// <reference types='electron'/>
import { BrowserWindow } from 'electron';


export enum AccentState {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_FLUENT = 4
}

export function SetWindowCompositionAttribute(window: Buffer | BrowserWindow, accent: AccentState, color: number): void;