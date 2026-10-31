# Shakti OS Foundation

An offline, owner-installed foundation for observing a 64-bit workload,
testing separate safe copies, and supporting Shakti through fixed memory
and a defined logical interface.

Status: blueprint and C99 interface skeleton. No bootable OS or successful
native compilation is claimed. See the current evidence for each job.

## Start here

Read `AGENTS.md`, then these readable repository files:

- `mcp/os_foundation/CONSTITUTION.md`
- `mcp/os_foundation/BLUEPRINT.txt`
- `mcp/os_foundation/CONTRACTS.txt`
- `mcp/os_foundation/ACCEPTANCE.txt`
- `mcp/os_foundation/WORK_ORDERS.txt`
- Your interface headers under `mcp/os_foundation/include/`

The repository contains extracted text and source files. Agents do not need
to open an archive. This dedicated OS repository is the target for these
work orders; older references to the current Shakti repository do not
authorize writes to a different repository.

## Branches

`foundation/integration` holds the readable seed and reviewed project work.
Each worker branches from its current tip as `work/W01`, `work/W02`, and so
on. Pull requests target `foundation/integration`.

Tyler or one designated agent acts as W00; no extra agent is required.
W00 coordinates ownership and integration. Reviewed source marked NOT_RUN
may be merged there so other agents can inspect and build on it. That merge
does not satisfy an execution or hardware acceptance gate. Only actual
evidence changes the corresponding test status.

`main` is reserved for an explicitly approved release. Workers do not push
or merge into it. Initial repository creation by Tyler is separate from
later release approval. No automatic merge or build workflow is supplied.

## Ownership

W00 owns shared headers, canonical contracts, the assignment register, and
the one test runner. Each other worker owns only its work-order files and
its job-specific review records. Request a narrow shared-contract change
through W00 before depending on a new interface.

Implementation and test source stays under `mcp/os_foundation`. Root files
are navigation and agent instructions, not executable tools.

## Entry points and evidence

Module tests export uniquely named functions and do not define `main`.
The integrator-owned `tests/validator_runner.c` supplies the test target's
entry point. Firmware and guest programs are separate explicit targets.

Record source SHA, profile, toolchain identity, tests actually run, outputs,
failures, and remaining NOT_RUN items. Never rewrite earlier run logs.
If a dependency changes, identify the new SHA and rerun affected checks.

## First assignments

W00 coordinates. W01 qualifies the non-GCC toolchain. W02-W08 can author
their independent source within the declared interfaces. Required module
and toolchain dependencies must exist before their tests can pass.

The code policy remains strict C99 portable logic, fixed static storage,
zero general heap, and no hidden runtime dependencies or remote controls.
The explicitly listed CPU adapter owns necessary architecture-specific
instructions. No compiler, model, credential, or script is bundled here.
