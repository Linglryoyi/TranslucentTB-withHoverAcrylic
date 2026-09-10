# Hover Acrylic fork

## Behavior

The default desktop background is fully Clear. Hovering a taskbar or having a relevant maximized window on that monitor requests Acrylic. Each taskbar tracks hover independently. Configuration remains the existing `settings.json`; `hovered_appearance` is an optional appearance object using the same fields as other states:

```json
"hovered_appearance": {
  "enabled": true,
  "accent": "acrylic",
  "color": "#00000000",
  "show_peek": false,
  "show_line": false
}
```

Maximized Acrylic is enabled by default. Explicit settings and maximized-window rules still override defaults. Precedence is: enabled battery saver, enabled Task View, Peek desktop, enabled Start, enabled Search, enabled maximized-window rules/appearance, enabled hover, enabled visible-window rules/appearance, desktop.

On Windows 11 XAML taskbars, the background Shape's compositor visual fades between native Acrylic and zero opacity. This affects the background only. The same Acrylic brush is retained during hover reversals, and identical requests do not restart animation. Other appearance modes restore the original background opacity before applying their brush. The legacy composition-attribute path remains immediate.

Entry and exit durations are currently constants (200/280 ms). Hover confirmation is 40 ms; leaving confirmation is 80 ms, with up to one polling interval of scheduling latency. Covered taskbars do not count as hovered. Auto-hide and monitor hot-plug behavior require real-machine validation.

## Develop with VS Code

Open this repository folder in VS Code. No Visual Studio IDE is required for editing. The `Hover Acrylic Windows build` GitHub Actions workflow builds `feature/hover-acrylic` on `windows-2025`, restores NuGet/vcpkg packages, runs the tests, and uploads a portable x64 artifact and diagnostics. This avoids installing a local IDE or compiler toolchain.

Local compilation still requires MSBuild, MSVC, Windows SDK and UWP/XAML build targets (see `.vsconfig` and `CONTRIBUTING.md`). VS Code extensions alone do not supply these components. Standalone Build Tools is a possible alternative; this project has not yet validated that local installation path.

## Portable deployment

Download the successful feature-branch run's `hover-acrylic-portable-x64` artifact. Extract it to a stable folder and run `TranslucentTB.exe`. Keep the executable, DLLs, assets and `resources.pri` together. `build-commit.txt` records the source commit. The upstream portable startup mechanism is a shortcut to that executable in the current user's Startup folder; remove that shortcut to disable startup.

The app uses upstream's single-instance behavior. Exit an existing TranslucentTB first. Explorer pins its injected TAP DLL: changing from upstream or an older fork build can require restarting Explorer. The fork uses a distinct TAP behavior version so it cannot silently reuse an older non-animating service. Explorer restart temporarily closes/recreates shell windows; avoid doing it during file operations.

No Store publication, certificate trust changes, system DLL replacement or security-policy changes are required. A successful build is not final acceptance: consult the test ledger for visual, recovery and startup results.
