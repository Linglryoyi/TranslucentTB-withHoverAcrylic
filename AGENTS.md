# Hover Acrylic execution rules

This GPL-3.0 TranslucentTB fork implements transparent desktop, per-taskbar hover Acrylic, and maximized-window Acrylic. Preserve upstream authorship.

## Repository and roles
- Work only on `feature/hover-acrylic`, based on `release`.
- `origin` is Linglryoyi/TranslucentTB-withHoverAcrylic; `upstream` is TranslucentTB/TranslucentTB.
- Never force push, rewrite upstream history, or merge to release before real-machine acceptance.
- Codex implements, builds, tests, documents and deploys. The user's supplied master specification is the design reference. An existing ChatGPT architect conversation may provide review only when actually reached; never invent approval.
- Record phase checkpoints in project_state.md and maintain truthful checkboxes in tasks.md. Commit stable milestones; exclude generated files and credentials.

## Architecture
- Reuse taskbar discovery, per-monitor data, maximized detection, Explorer recovery, configuration and startup.
- Inspect TranslucentTB/taskbar/taskbarattributeworker.*, Common/config/*, ExplorerTAP/taskbarappearanceservice.*, TranslucentTB/managers/{configmanager,startupmanager}.cpp and settings.schema.json before behavior changes.
- Preserve Start/Search/Task View compatibility precedence. Hover must not override maximized Acrylic.
- Poll cursor lightly; debounce changes. Animate background only, asynchronously, reversibly, with no repeated identical writes.
- Never fade the taskbar HWND or icons, block the UI thread, replace system DLLs, patch Explorer binaries, weaken security, or modify unrelated settings.

## Build and acceptance
- Attempt unchanged baseline before implementation. Follow CONTRIBUTING.md and .vsconfig; do not alter logic to mask missing tools.
- Target Release x64; prefer upstream portable deployment if packaging requires signing.
- Verify desktop Clear, smooth hover entry/exit, maximized interactions, rapid boundary crossings, no icon corruption, Explorer recovery, startup, and local deployment.
- Mark visual/runtime acceptance only after observing actual behavior. Build success alone is not completion.
