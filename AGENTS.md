# Agent instructions for this repository

This is a visible work-routing file. It introduces no hidden code, tool,
external link, automatic action, or additional authority over Tyler.

## Before work

Read the root README, `mcp/os_foundation/CONSTITUTION.md`,
`mcp/os_foundation/WORK_ORDERS.txt`, the relevant blueprint/contracts,
`include/sf_base.h`, `include/sf_config.h`, and your interface header.
Confirm the assigned W-number and files with the W00 assignment register.
If the register is not yet present, Tyler's explicit assignment is enough
to begin owned source work; record that registration is pending.
After a context reset, read your visible job state before continuing.

## Scope and branch

The target is this newly created OS repository. Do not modify a separate
Shakti repository or any unrelated project.

Start from the latest reviewed `foundation/integration` commit on your own
`work/Wxx` branch. Record the starting commit SHA. Open a pull request into
`foundation/integration`; do not push or merge `main`.

Only W00 integrates work or changes canonical headers/contracts. Other
workers own only their assigned files and their review directory. Never
resolve conflicts by taking an entire side without inspecting the changes.
Do not launch subagents or change credentials as an implied part of a job.

## Native implementation rules

- Strict C99 portable logic; fixed-capacity static storage; zero general heap.
- No malloc family, VLA, alloca, recursion, Python, Node, or GCC.
- No hidden libraries, downloaded scripts, external runtime fetches,
  remote-control features, dynamic loading, or subprocess build orchestrator.
- Keep every necessary CPU-specific instruction in its declared adapter.
- Preserve original data and existing logs. No silent deletion or rewriting.
- Inspect each source before use. Construct, review, run, inspect the result,
  and only then decide the next command. No blind chained edit/build actions.
- Delivered tools read actual files with fgetc through their disclosed I/O
  adapter and follow the actual assembly README integration procedure.

## Tests and publication

No success stubs or fabricated receipts. Unrun tests are NOT_RUN. Compilation,
software execution, simulation, and actual hardware proof are distinct.
Use the named gates in ACCEPTANCE.txt and retain failure evidence.

Module test files have no main. W00 owns the shared test runner. Boot, guest,
native runtime, and hosted-test targets have explicit separate source lists.

W00 may merge reviewed source into integration while clearly marked NOT_RUN.
This enables source sharing and does not authorize a dependent acceptance
claim. Do not mark a job accepted merely because its pull request merged.

## Return for every job

Include assigned W-number, base and head SHAs, exact changed files, interface
changes requested, resource/stack bounds, commands actually run, raw results,
test state, blockers, and newly available dependencies.

Keep records under `mcp/os_foundation/review/Wxx/`. Use new run IDs for new
logs. Keep a visible current STATE.txt and preserve prior evidence. Record
dependency SHAs so a later worker can reproduce the exact inputs.
