# Project state

## Current checkpoint — deployed, awaiting visual acceptance
- Successful binary source: 65bf7056025d91d695b4bc86ab4e9430630230ed. CI run 34451139531: Release x64, zero warnings/errors, all 86 tests passed.
- Portable artifact SHA256: 486538ff82c14943eed10cf73f8e1abc2bd7dff2b2929e46a189e4f49a5899a6 (verified after download).
- Deployed to ../HoverAcrylic/TranslucentTB.exe; settings.json currently enables debug diagnostics for acceptance.
- First launch exited with the upstream restart-required message because the old HUXSoft Translucent Taskbar component remained in Explorer. Restarted Explorer; new application runs successfully.
- Disabled only the old Translucent Taskbar startup item through Task Manager. Created and read back the standard current-user Startup-folder shortcut, TranslucentTB Hover Acrylic.lnk.
- Real hover enter/leave and maximized-window insertion/removal events appear in the debug log. User visual feedback is pending; event detection alone does not prove the appearance or animation.
- Running application survived a subsequent Explorer restart; new taskbar discovered and connection restored within about two seconds. Only the fork TAP DLL is present in the new Explorer. Transient RPC/COM errors occurred during shell teardown, followed by successful recovery.
- Approximate memory: 78–90 MiB working set. CPU increased about 0.08 seconds during an approximately one-minute idle interval; broader performance testing not performed.
- Remaining: user visual results A–H, visible recovery confirmation, actual next-sign-in startup test, available multi-monitor checks. Keep debug logging until diagnosis is complete, then return verbosity to warn. No release tag or merge before acceptance.

## Phase 0 — Repository setup (historical)
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
- A–H: visual acceptance PENDING; hover and maximized event detection observed in logs.
- I: automatic reconnection PASS; visible appearance after reconnection awaits user confirmation.
- J: startup shortcut configured and target verified; actual sign-in test PENDING.
- Application deployed and running. No release tag or completion claimed.

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


## Functional appearance and transition implementation (awaiting validation)
- e299a14 connects hover after maximized rules and before visible-window rules. Battery Saver, Task View, Peek, Start and Search keep upstream precedence.
- Added hovered_appearance configuration/schema; defaults enable hover Acrylic and existing maximized Acrylic. Existing explicit user overrides remain respected.
- Windows 11 background-only compositor transition: enter 200 ms, leave 280 ms. Retain the same native Acrylic brush while clear, fading only the background Shape visual to zero. A new animation starts from the compositor's current value; identical appearance requests do not restart animations.
- Restore the background visual's original opacity before stock/blur/other appearances or process-exit recovery. No taskbar HWND layering or icon fading added.
- Legacy taskbar rendering retains upstream immediate appearance changes; smooth animation targets the Windows 11 XAML service.
- Compile, animation reversal and real-machine visual acceptance remain pending. No completion tag or deployment yet.

## Baseline CI diagnosis
- Baseline d715bb0 run 34448203180 failed with MSB4006, a circular CppWinRTComputeGetResolvedWinMD target graph in TranslucentTB.vcxproj, and dependent DesktopBridge MSB4181. Zero compiler warnings. Xaml library built; complete application build did not pass.
- Change CI to x64 MSBuild and serialize project builds (/m:1, BuildInParallel=false) to avoid simultaneous metadata requests. No application logic changed to mask this environment/build-order failure.
- Windows 11 25H2 build 26200.8037 has x64 Microsoft.UI.Xaml.2.8 and VCLibs.140.00 meeting the upstream minimum versions.


## Configuration test dependency correction
- Full feature run 34448648855 additionally exposed missing spdlog/common.h in Tests, whose new configuration tests include Config. Declare spdlog in Tests/vcpkg.json, matching the application's existing dependency.
- Serialized build ff85fe6 is still running; no successful binary or runtime result yet.


## Serialized build result
- Run 34450778644 at ff85fe6: ExplorerHooks.dll, ExplorerTAP.dll, ProgramLog.dll, Xaml.dll and TranslucentTB.exe compiled successfully, zero warnings. MSB4006 is resolved by serialized builds.
- Overall solution failed only on Tests missing spdlog/common.h; fix 65bf705 already pushed and run 34451139531 is in progress. Keep metadata settings unchanged because no additional workaround is required.
- No portable artifact from the failed run; local launch and acceptance remain pending.

