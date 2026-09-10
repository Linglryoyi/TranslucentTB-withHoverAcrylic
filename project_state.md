# Project state

## Phase 0 — Repository setup (in progress)
- Branch: feature/hover-acrylic, created from origin/release.
- Baseline commit: d4636e439865df0a1a1419db408e055740ce5c74.
- Current commit: see `git rev-parse HEAD`; phase documentation records the preceding checkpoint to avoid self-referential hashes.
- origin: https://github.com/Linglryoyi/TranslucentTB-withHoverAcrylic.git
- upstream: https://github.com/TranslucentTB/TranslucentTB.git
- Working copy created under this task's outputs directory; no pre-existing source was overwritten.
- Bundled Git lacked HTTPS discovery. Downloaded workspace-local MinGit 2.55.0.5 and cloned successfully.
- Added AGENTS.md, project_state.md, tasks.md.
- Build documentation requires Visual Studio 2026 and .vsconfig components; default installation locations and PATH do not expose MSBuild/C++ tools.
- Baseline build and runtime tests: not yet run.
- Architect browser checkpoint: not sent; local durable checkpoint fallback in effect until existing conversation is identified.
- Next: fetch upstream, commit/push setup, inspect required modules and attempt baseline.

## Acceptance ledger
All runtime tests A–J are NOT RUN. No application deployed, startup enabled, release tag created, or completion claimed.

## Phase 1 — Architecture and baseline
- Setup checkpoint 6ebdde0 pushed successfully to origin/feature/hover-acrylic; upstream fetched.
- Read required worker/configuration/ExplorerTAP/startup modules, schema, CONTRIBUTING.md, common build props and upstream CI/portable scripts.
- Existing precedence: battery saver > Task View > Peek desktop > Start > Search/Find-in-Start > maximized window (including rules) > visible window (including rules) > desktop.
- Planned addition: hover after maximized and before visible window. Keep special states unchanged. Enable existing maximized Acrylic default in this fork.
- Discovery and maximized membership are already per HMONITOR in MonitorInfo; reuse this map, WinEvent updates and ResetState recovery.
- Windows 11 XAML uses ITaskbarAppearanceService to set the background Shape.Fill; icons are separate. Legacy fallback uses SetWindowCompositionAttribute.
- Preferred animation candidate: compositor opacity on background Shape visual only, reusing Acrylic brush through clear/hover cycles; compositor should handle reversals without application frame polling. Must verify interruption semantics and actual rendering before acceptance.
- StartupManager uses packaged StartupTask; upstream portable README prescribes a Startup-folder shortcut. No new service needed.
- Unmodified application baseline attempted: dotnet msbuild TranslucentTB.slnx /restore /p:Configuration=Release /p:Platform=x64 /p:SkipSigning=True. Failed before compilation: no .NET SDK installed; standalone MSBuild and VC tools absent.
- Downloaded Microsoft-signed Visual Studio 2026 stable bootstrapper (signature valid) and launched installation using repository .vsconfig filtered to x64 (ARM64 excluded). Installation pending; no functional source changes yet.
- Runtime tests: all NOT RUN. Next: finish toolchain installation and successful baseline, then hover prototype.

## User correction — prefer VS Code
- User requested using existing VSC in place of Visual Studio where practical.
- Confirmed D:\Microsoft VS Code\Code.exe, version 1.114.0.
- Community installer UI reports download stopped at 4%, installation 0%; bootstrapper and some package files already exist. Do not resume full IDE installation.
- Evaluate standalone Build Tools + Windows SDK/XAML support, with VS Code as editor. No source behavior changes yet.


## 2026-09-10 — Stop unwanted installer startup
- User explicitly requested stopping VS2026 downloads and boot popups.
- Found two setup.exe processes resuming the Community install and HKLM RunOnce entry 6EA26FFDFC3C3CADAF6C.
- Stopped both verified installer processes and removed only that installer resume entry. Backup retained outside repository in work/.
- Do not resume Community installation or install replacement build tooling without returning to the user's development request. Feature development remains paused.


## Resumed development — hosted builds and hover prototype
- Use GitHub Actions windows-2025 to build and test; no local IDE installer launched or resumed.
- Baseline run 34448203180 restored NuGet dependencies and is compiling unmodified application logic at d715bb0.
- Added pure TaskbarHoverState, per-monitor storage, 40 ms WM_TIMER polling, 40/80 ms enter/leave confirmation and three behavioral tests. Prototype logs state changes only; appearance is not connected yet.
- Hit testing requires both taskbar bounds and the top-level window under the pointer, avoiding activation through an overlapping app.
- Runtime acceptance still not run.

