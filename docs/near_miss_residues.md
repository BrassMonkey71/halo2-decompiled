# Near-miss residues: one matched, six diagnosed

Retail ranges covered: `0x9d1c0`, `0x2d97a0`, `0x156b30`, `0x31a770`,
`0x1e3480`, the blocked `0xba300`, and `0x185a30`. This is one analysis note
over seven functions that are already written in `src/` and differ from
retail by a small, precisely diagnosed residue. **Analysis only:** it claims
nothing, and the one source change it records (the `0x9d1c0` fix below) is
now verified by the plain full `check.py`. Names are provisional. It is
written for whoever picks any of these up.

**Outcome so far:** `0x9d1c0` **matches** (the game total moved 9347 → 9348,
with no other row changed); it carries a policy question about `volatile` on
a global that a maintainer should settle. `0x185a30` was analysed after this
note was first written and is diagnosed as a *compiler-behaviour* residue
rather than a source-shape one. The rest are unchanged.

Method for each: `python tools/disasm.py <va>` for retail,
`python tools/check.py --fast <va>` for the residue, and — for the two that
were chased to the end — a standalone loop that compiles one function with
the SDK's `CL` and disassembles the object with capstone (see "How these
were measured"). The baseline these were measured against is a full
`python tools/check.py` that reproduced the README's status exactly at the
time (9315 of 11321 game functions, with `config/functions.csv`
byte-identical to `HEAD`). The tree has since moved on — upstream batches
take it to 9347, and the `0x9d1c0` fix below takes it to 9348 — but none of
the pulls touched a file this note covers, and the callers and callees below
were re-checked against the current inventory.

## Boundary

Five of the seven have their callers and callees all matched, so nothing
outside them decides their bytes; `0xba300` does not, and is included as a
warning rather than a target. `0x185a30` is fully bounded: its callers
`0x183ee0` and `0x183f00` and its callee `0xb5920` are all matched, so
nothing outside it decides its bytes either. None is in a person's claim in
issue #9 as of the 2026-10-20 19:59 snapshot (checked with
`open_work.person_claims`): `0x1e3480` sits in lane X, `0xba300` in lane AB,
`0x2d97a0` and `0x31a770` in the Havok lane, and `0x156b30` in nothing at
all. Claims change, so re-check before starting.

## `0x9d1c0`: matched — the CSE needs two stores to one address

`src/unknown_09a5e0.cpp`, 53 bytes, `c_breakable_surface_group_entity_definition::v25`.
It bounds-checks `entity->slot` into 0–7, clears `g_4eca60[slot]` to `NONE`
if it was set, stores `entity->id`, and returns true. **Now `matched`**: the
plain full `check.py` prints `MATCH 0009d1c0
c_breakable_surface_group_entity_definition::v25`, and the game total moved
9347 → 9348, with `config/functions.csv`'s only changed row being this one.

The source had a `#pragma optimize("s", on)` scoped to this one function.
Removing it was the first half — 40 → 53 bytes, score 23 → 11 — and touched
nothing else (the file's other functions were re-checked).

What was left was the constant CSE. The compiler materialised `NONE` (`-1`)
into a register for its two uses, the compare and the clear, where retail
folds both into immediates:

```
ours                                    retail
!! push esi                             mov ecx, dword ptr [eax*4 + 0x4eca60]
!! mov esi, dword ptr [eax*4 + 0x4c332c] cmp ecx, -1
!! or ecx, 0xffffffff                    je 0x9d1e7
!! cmp esi, ecx                          mov dword ptr [eax*4 + 0x4eca60], 0xffffffff
!! pop esi                               mov ecx, dword ptr [edx]
!! je 0x401b67                           mov dword ptr [eax*4 + 0x4eca60], ecx
```

**What triggers it**, isolated in the standalone harness: not the two uses of
`-1` by themselves. One use folds (`g_4eca60[slot] = NONE;` alone gives
`mov [mem], -1`), and two uses fold when the *second store goes to a
different address* (`g_4eca60[slot + 1] = entity->id;` gives `cmp dword ptr
[eax*4], -1` plus an immediate store). It is **two stores to the same
address** — the clear and the `entity->id` store — that makes MSVC keep `-1`
in a register for the first of them.

**The fix** keeps the load in a register, so the constant does not need one:

```
	long id = *(volatile long *)&g_4eca60[slot];

	if (id != NONE)
		g_4eca60[slot] = NONE;
	g_4eca60[slot] = entity->id;
```

That reproduces retail's instruction sequence exactly, and the full check
agrees. Ruled out first, all still materialising: `~0`, `0xffffffff`,
`(dword)NONE`, `(long)(char)NONE`, `(short)NONE`, a file-scope `const`, an
enum, a `memset` fill (which folds, but moves the store to a `lea` and
changes the allocation, 50 bytes), `__forceinline` helpers, `#pragma
optimize("t"/"g"/"s", …)`, and `/O1`, `/Os`, `/Ot`, `/Ob0|1|2`, `/Og-`,
`/Oi-`, `/Gs-`, `/GF-`, `/Gy-`.

**Policy question, unresolved here.** `docs/DECOMPILING.md` allows a
`volatile` access only on a parameter, a local or data reached through a
pointer, "never on a global"; the fix is a `volatile` read of a global.
`src/` has precedents for that shape with a comment (`unknown_2b116a.cpp:857`,
`unknown_02b400.cpp:704`, `unknown_12b070.cpp:66`) and this change carries
one, but a maintainer should decide. No plain-source shape was found that
folds the constant without it.

## `0x2d97a0`: a one-instruction residue with a conflicting fix

`src/unknown_2d97a0.cpp`, 40 bytes, a Havok deleting destructor
(`class_2d97a0`, tag `0x19`), generated from a class declaration. `--fast`
score 1: the only difference is the *call target*.

```
ours:   call 0x401080      (c_reference_a9f20::~c_reference_a9f20, retail 0xdc370)
retail: call 0x3192b0      (kind_object_3192b0::~kind_object_3192b0, a 5-byte `jmp 0xdc370`)
```

So `class_2d97a0` must derive from `kind_object_3192b0`, and the deleting
destructor must call that destructor **out of line**. Changing the base alone
does not do it: the compiler inlines the implicit destructor and threads the
call through to `0xdc370`.

The project has a working pattern for exactly this —
`include/reference_base_318970.h` declares its destructor out of line
(`virtual ~reference_base_318970();`) and `src/unknown_318970.cpp` defines it
under a plain `// @retail 0x318970` marker, which is what makes the matched
`0x2da270` emit `call 0x318970`. Applying the same to `kind_object_3192b0`
**does fix `0x2d97a0`**:

```
MATCH  002d97a0 class_2d97a0::`deleting destructor'
```

**but it breaks `0x3192b0`**, which was matched:

```
DIFF   003192b0 kind_object_3192b0::~kind_object_3192b0 (11 bytes, retail 5)
  !! mov dword ptr [ecx], 0x47c198     |   jmp 0xdc370
  !! jmp 0x401080                      |
```

A user-defined destructor stores the vptr; retail's `0x3192b0` is a bare
5-byte `jmp`, which only an *implicit* destructor produces — and an implicit
destructor is exactly what gets inlined away in the derived class. The two
requirements conflict, and keeping the change would break the project's
hardest rule, so it was reverted.

**Lead:** the base's destructor has to stay implicit for `0x3192b0`, so the
out-of-line call in `class_2d97a0` must come from somewhere else. Worth
checking whether `class_2d97a0` should take the base destructor's address
(which forces it out of line), or whether the two functions belong to a
different class shape than `kind_object_3192b0 : c_reference_a9f20`.

## `0x156b30`: a stack-homed local that retail copies with SSE

`src/unknown_01e930.cpp`, 46 bytes, `function_156b30` — a Bink sound
callback returning track `track`'s volume when `type == 0x3000577`, else
`0.0f`. The semantics are plainly right; the residue is where `result` lives.

Retail homes `result` in a stack slot and moves floats with SSE, loading
`st(0)` only for the return:

```
push ecx
cmp dword ptr [esp + 0xc], 0x3000577
xorps xmm0, xmm0
movss dword ptr [esp], xmm0          ; result = 0.0f
jne 0x156b57
mov eax, dword ptr [esp + 8]
shl eax, 5
movss xmm0, dword ptr [eax + 0x4e9304]
movss dword ptr [esp], xmm0          ; result = volume
fld dword ptr [esp]
pop ecx
ret 8
```

Ours keeps `result` in the x87 register (`fld` the constant, `fstp st(0)`,
`fld` the volume) and never allocates a slot.

A `volatile real result` reproduces retail's **exact control flow and memory
homing** — `push ecx`, the same `cmp`, the store, `jne`, `shl eax, 5`, the
store, `fld [esp]`, `pop ecx`, `ret 8` — and differs only in instruction
selection: it emits `mov dword ptr [esp], 0` and GP-register `mov`s where
retail emits `xorps`/`movss`. (`volatile` on a local is permitted by the
rules with a comment, but this variant is not the answer yet.)

**Lead:** the question is now narrow — how to get a *non-volatile*
memory-homed `float` local that MSVC copies with SSE. Direct returns, a
`real result = 0` initialiser, and the plain form were all tried and are
worse.

## `0x31a770`: seven zeroed rows, stored in the wrong order

`src/unknown_31a750.cpp`, 54 bytes, `class_31a750::function_31a770` — sets a
kind byte and zeroes seven `__m128` rows, returning `out + 0x80`. `--fast`
score 5, and every difference is *store ordering*:

```
ours                                    retail
!! mov byte ptr [eax], 2                xorps xmm0, xmm0
!! xorps xmm0, xmm0                     mov byte ptr [eax], 2
!! movaps xmmword ptr [eax + 0x10], xmm0 movaps xmmword ptr [eax + 0x30], xmm0
!! movaps xmmword ptr [eax + 0x20], xmm0 movaps xmmword ptr [eax + 0x10], xmm0
!! movaps xmmword ptr [eax + 0x30], xmm0 movaps xmmword ptr [eax + 0x20], xmm0
   (from +0x40 on, identical, including the `and esp` before the last store)
```

The matched sibling `0x31a750` zeroes its three rows **ascending**, so
retail's `+0x30` first is the anomaly, not the norm. Tried, with scores:
`kind` last (9), explicit retail order (8), `memset` (41), a `for` loop
(195), the helper rewritten with `_mm_store_ps` (5), and a hoisted `__m128
zero` with the retail order (8). **Nothing beat the current 5.**

**Lead:** this looks like an instruction-scheduling artefact rather than a
source-order one — `and esp, 0xfffffff0` is likewise interleaved before the
last store, which is not a source-level choice.

## `0x1e3480`: an add that lands in the other register

`src/unknown_1e3480.cpp`, 86 bytes — returns an object's actor index, and for
a creature (`type == 12`) follows `creature_offset` at `+0x13a` to a nested
creature's actor index. `--fast` score 2: an `add` accumulates the sum into
`edx` for us and `ecx` for retail, so the following load differs
(`[edx + 4]` against `[ecx + 4]`).

Tried, all identical codegen: the operand flip, `i + p` and `p + i` as
integers, `(byte *)p + (long)i`, `(char *)p + i`, and a local for the offset.
A fresh `creature` variable did change the shape to retail's — accumulate
into the *offset's* register — but chose `eax` where retail chooses `ecx`.
`tools/permute.py --fast --anneal` annealed about eleven minutes without a
match.

**Lead:** the shape is reachable and the register is not, which points at
register pressure or ordering elsewhere in the function rather than at this
expression.

## `0xba300`: blocked, not a residue — check the callers first

`src/unknown_0b8bd0.cpp`, 72 bytes, `object_get_root_location`. It is
`todo`, it is already written, and it looks like an obvious small target —
but **all twelve of its callers are unmatched** (`0xc2d00`, `0xca0b0`,
`0xcf040`, `0xd9e70`, `0xfc330`, `0x104150`, `0x10b4d0`, `0x189210`,
`0x18c060`, `0x18c3b0`, `0x18cbc0`, `0x242660`). Under LTCG a function's
*incoming* argument registers are decided by its callers, and retail takes
this one in `ecx`/`eax` where we take it in `eax`/`esi`. It cannot be fixed
from inside the function.

**This is the general lesson:** `tools/open_work.py` filters on *callees*
being done, but for a function whose arguments travel in registers, the
callers matter just as much. It lists 421 source files with unmatched
functions outside every person's claim; requiring the callers _and_ the
callees to be matched, and excluding person claims, narrows that to 310
individual functions.

## `0x185a30`: an index loop retail did not strength-reduce

`src/unknown_183ee0.cpp`, 61 bytes, `function_185a30` — for each of the eight
slots, calls `function_b5920` with the identifier when the game is not in
mode 4, clears the slot, and zeroes `g_4ea95c`. `--fast` score 6; of the six
differing instructions, two differ only in the reduced image's addresses and
the other four are the loop's induction variable:

```
ours                                    retail
!! mov eax, dword ptr [esi + 0x4c230c]  mov eax, dword ptr [esi*4 + 0x4eca60]
!! mov dword ptr [esi + 0x4c230c], -1   mov dword ptr [esi*4 + 0x4eca60], 0xffffffff
!! add esi, 4                           inc esi
!! cmp esi, 0x20                        cmp esi, 8
```

Retail walks the **index** (`[esi*4 + 0x4eca60]`, `inc esi`, `cmp esi, 8`);
our build strength-reduces the loop to a pointer walk (`add esi, 4`,
`cmp esi, 0x20`). Everything else — `push esi`, `xor esi, esi`, the
`cmp eax, -1`, the mode check, the call, the `jb` — matches. The full build
agrees with the fast check: score 6, 61 bytes on both sides.

**Why this looks like a compiler difference rather than a source shape.**
MSVC 7.1 strength-reduces an index that is used *only* in array subscripts
when the bound is a compile-time constant, and keeps the index otherwise.
The project's own matched code shows both halves of that rule:

- A precise scan of the retail image (an `inc R` with `cmp R, imm`, a
  backward `jcc`, and `[R*4 + disp]` in the body) finds 39 index-form loops
  in matched game functions. In every one whose source index could be
  attributed, the index is used for something besides indexing: passed as an
  argument (`function_192ce0`, `function_192d40`, `function_10e9a0`), shifted
  (`1 << team`, `0x157970`), scaled (`bn[i * 2]`, `0x1650a0`), assigned to a
  result (`result = type`, `0x1088a0`) — or the bound is a runtime value
  (`g_transport_globals.transition_function_count`, `0x8d730`;
  `g_51f40c.count`, `0x20770`).
- Retail does reduce where the shape allows: `transport_shutdown`'s second
  loop — `&g_4cf7d4[key]`, bound 8, index used only in subscripts — compiles
  in retail to a pointer walk (`add esi, 0x20`, `cmp esi, 0x4cf8d4`), and our
  build matches it (`0x8d970`).

`0x185a30` fits neither half: a constant bound of 8, the index used only in
subscripts, and retail kept the index anyway.

**Tried, all still strength-reducing** (each compiled standalone and compared
against retail instruction for instruction): 41 loop and bound variants —
`long`/`dword`/`short`/`ushort` index, `NUMBEROF(g_4eca60)` against the
literal `8`, `while`, `do/while`, `!=`, `<=`, `*(g_4eca60 + i)`, an `id`
temp, a pointer loop, the index declared outside the `for`, `i & 7`,
`i - 0`, `i | 0`, a redundant `i < N` guard, a volatile read of the index, a
volatile read of the element, a local pointer to the array, struct-member
access, `sizeof` and `const`/`enum` bounds, a `long count = 8` local, and an
unsigned element type — plus 16 flag sets (`/O1`, `/Os`, `/O2 /Os`, `/Ot`,
`/Ob0|1|2`, `/Og-`, `/Oy-`, `/GF-`, `/Gs`). The one thing that keeps the
index form is a **runtime** bound, and that turns `cmp esi, 8` into a
register compare, so it cannot match either.

**Lead:** none. Recorded so nobody spends the time again. If a second VC7.1
build ever turns up, this function and `0x9d1c0` are the two to re-check:
both are places where retail's build made the *less* optimised choice.

## A tooling note: `permute.py --fast` built the whole project

`python tools/permute.py 0x9d1c0 --fast --anneal --jobs 1 --time-limit 900
--write-only-match` did not anneal. It created
`build/permute/scratch_a87821e4/full/` and began compiling **every** source
into it (`actor_behavior.obj`, `ai.obj`, …), 360 MB, still running after 18
minutes with no output on stdout and nothing written by the time limit. The
run was stopped by hand, so its result is *inconclusive* rather than
negative.

That may be intended (there is a commit "permute.py: make scratch folders a
sandboxed agent can write"), but the practical effect is that `--fast` needs
a cold full rebuild and is unusable for iterating on a near miss. Worth a
look by whoever owns the tool.

## How these were measured

```sh
python tools/check.py --fast <va> ...        # the residue, seconds
python tools/disasm.py <va>                  # retail, annotated with matches
```

For the two that were chased to the end, the loop was much tighter: compile
one function on its own with the SDK's `CL` and disassemble the object with
capstone, then compare the instruction sequence against retail's, with
absolute references normalised to `G`, calls to `C` and branches to relative
offsets (`build/ctest.py` plus a small per-function matcher; the scratch
sweeps are in `build/`, which is git-ignored). A variant costs about a
second against roughly 15 s for `--fast`, which is what made sweeps of
40-odd shapes and 16 flag sets practical. `--fast` stays the judge of record
for a near miss, and only the plain full `check.py` updates
`config/functions.csv`.

Where the Wine `binfmt_misc` registration is not in place (it does not
survive a reboot), every `check.py` run needs the SDK pointed at a shim whose
`bin/vc71/{CL,Link,Lib}.Exe` launch the real tools through Wine:

```sh
XDK_DIR=$PWD/build/xdk-shim python tools/check.py --fast <va>
```
