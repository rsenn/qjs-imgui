# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`qjs-imgui` is a native QuickJS C module that wraps [Dear ImGui](https://github.com/ocornut/imgui)
(plus its GLFW + OpenGL2/3 backends). It compiles to a single shared object `imgui.so` that
QuickJS loads via `import * as ImGui from 'imgui'`. The JS API mirrors the C++ `ImGui::` namespace
one-to-one — same function names, no prefix. See `README.md` for the full per-function JS signature
reference.

`imgui/` and `gl3w/` are git submodules. Run `git submodule update --init --recursive` before
the first build.

## Build

CMake builds into per-configuration directories named after the target triple + build type
(e.g. `build/x86_64-linux-gnu`, `build/x86_64-linux-debug`, `build/x86_64-linux-profile`).

```sh
cmake -S . -B build/x86_64-linux-debug -DCMAKE_BUILD_TYPE=Debug
make -C build/x86_64-linux-debug          # produces build/<dir>/imgui.so
make -C build/x86_64-linux-debug install  # installs into QUICKJS_C_MODULE_DIR
```

The build locates QuickJS via `cmake/FindQuickJS.cmake` (expects an installed QuickJS, default
prefix `/usr/local`) and GLFW via `cmake/FindGLFW.cmake`. `compile_commands.json` is generated in
each build dir.

Relevant CMake options: `USE_GL3W`, `USE_GLEW` (OpenGL loader choice; default is ImGui's internal
loader), `IMPL_OPENGL_ES2`, `IMGUI_DEMO` (build the upstream C++ demo), `BUILD_SHARED_MODULES`
(ON for native, forced OFF for WASI/Emscripten).

## Run / test

There is no automated test suite. `test-imgui.js` is a manual smoke test that opens a window and
renders the ImGui demo UI; it also imports `glfw` and `nanovg` modules, so those must be installed
alongside `imgui.so` in the QuickJS module path.

```sh
qjs -m test-imgui.js   # requires imgui.so + glfw + nanovg modules resolvable by qjs
```

## Architecture

**Single dispatch function.** Almost every ImGui call routes through one C function,
`js_imgui_functions` (quickjs-imgui.cpp:531), a giant `switch(magic)`. Each JS-visible name is an
entry in the `js_imgui_static_funcs[]` table (around quickjs-imgui.cpp:2659) declared with
`JS_CFUNC_MAGIC_DEF("Name", arity, js_imgui_functions, MAGIC_ENUM)`. The `MAGIC_ENUM` values come
from the `enum { IMGUI_INIT, ... }` at quickjs-imgui.cpp:201. **To add a binding:** add an enum
value, add a table row, and add a `case` in the switch — all three.

The dispatcher guards against a missing context: any magic greater than `IMGUI_CREATE_CONTEXT`
throws if `ImGui::GetCurrentContext()` is null. The whole switch body runs inside a `try` that maps
`ImGui::Exception` (thrown by `IM_ASSERT` via the override in
`quickjs-imgui-implementation.hpp`) into a JS exception.

**Value marshalling lives in `quickjs-imgui.hpp`.** This header is pure conversion machinery,
included first. Key pieces:
- `JSVal<T>::to/from` — scalar/string/`std::array` conversions between JS and C++.
- `OutputArg<T>` — RAII wrapper for ImGui's in/out pointer params. The JS side passes a ref object
  (`{ value: x }`, a single-element array, or a getter/setter function — see `JSRef`); `OutputArg`
  reads it on construction and writes back in its destructor. This is how `Checkbox`, `SliderFloat`,
  `InputText`, etc. mutate their arguments.
- `js_imgui_getimvec2/4`, `js_imgui_getcolor` — accept either `{x,y,...}` objects or arrays; color
  also accepts a packed u32 or hex string.
- `js_get_arraybuffer` / `JSRange<T>` — view into a JS ArrayBuffer/TypedArray (handles byteOffset).
- `ScalarType` / `ImGuiDataTypeUnion` / `js_to_scalar` / `js_from_scalar` — generic
  `ImGuiDataType`-tagged scalar handling for the `*Scalar` family.
- Opaque pointers: `js_imgui_newptr`/`getptr` round-trip raw pointers as `"%p"` strings.

**Wrapped ImGui structs** each get their own `quickjs-im*.hpp` header, all included by
quickjs-imgui.cpp. Each follows the QuickJS class idiom: a `thread_local JSClassID`, a `_proto`
and `_ctor`, `_constructor`/`_finalizer`/`_wrap` functions, a method table, and an internal
`enum` of method magics (same single-dispatch pattern as the top level). These are: `ImGuiIO`,
`ImGuiStyle`, `ImGuiInputTextCallbackData`, `ImGuiPayload`, `ImFont`, `ImFontAtlas`, `ImDrawData`.
They are registered as module exports in `js_imgui_init` (quickjs-imgui.cpp:3013) and declared in
`js_init_module` (quickjs-imgui.cpp:3107).

**Backends** (`quickjs-imgui-implementation.hpp`) expose `ImplGlfw`, `ImplOpenGL2`, `ImplOpenGL3`
as objects of method tables (via `js_imgui_impl_object`). `ImGui.Init(impl...)` records backend
objects and resolves their `InitFor<Type>` / `RenderDrawData` / `NewFrame` methods by name at
frame time.

**Constants** are defined as `JS_PROP_CONSTANT` tables in `quickjs-imgui-constants.hpp` and exposed
as **nested namespace objects** on the module via `JS_OBJECT_DEF` entries in `js_imgui_static_funcs`
(quickjs-imgui.cpp:~2960) — e.g. `ImGui.WindowFlags.NoTitleBar`, `ImGui.Cond.Always`,
`ImGui.Col.Text`. (Note: `README.md` writes some flags in the flat `ImGuiWindowFlags_*` form;
the actual exported shape is the nested `ImGui.<Group>.<Name>` object.)

## Code style

`.clang-format` defines the C++ style (notably: return type on its own line for top-level
definitions, 2-space access-modifier offset, short inline functions/case-labels allowed). Match it;
do not reformat untouched code.
