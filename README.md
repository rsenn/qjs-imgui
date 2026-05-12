# qjs-imgui Reference

Dear ImGui bindings for QuickJS. Wraps the immediate-mode GUI library.
The JS API mirrors the C++ ImGui:: namespace directly — function names are
identical (no prefix).

Import: `import * as ImGui from 'imgui.so';`

## Typical frame loop (with GLFW + OpenGL)

```js
import * as ImGui from 'imgui.so';
import { Window, poll, ... } from 'glfw.so';

// --- init (once) ---
ImGui.CreateContext();
ImGui.StyleColorsDark();
// Backend init (ImGui_ImplGlfw_InitForOpenGL, ImGui_ImplOpenGL3_Init)
// handled by the binding or done separately

// --- per frame ---
ImGui.ImplOpenGL3_NewFrame();
ImGui.ImplGlfw_NewFrame();
ImGui.NewFrame();

// --- build UI ---
ImGui.Begin('My Window');
ImGui.Text('Hello, world!');
if (ImGui.Button('Click me')) {
  console.log('clicked');
}
ImGui.End();

// --- render ---
ImGui.Render();
ImGui.ImplOpenGL3_RenderDrawData(ImGui.GetDrawData());
```

## Core lifecycle

```js
ImGui.CreateContext([sharedFontAtlas])
ImGui.DestroyContext([ctx])
ImGui.GetCurrentContext()
ImGui.SetCurrentContext(ctx)
ImGui.NewFrame()
ImGui.EndFrame()
ImGui.Render()
ImGui.GetDrawData()           // → ImDrawData (pass to renderer backend)
```

## Windows

```js
ImGui.Begin(name[, open[, flags]])   // → bool (is expanded); open is { value: bool }
ImGui.End()
ImGui.BeginChild(id[, size[, border[, flags]]])
ImGui.EndChild()
ImGui.IsWindowCollapsed()
ImGui.IsWindowFocused([flags])
ImGui.IsWindowHovered([flags])
ImGui.GetWindowPos()         // → { x, y }
ImGui.GetWindowSize()        // → { x, y }
ImGui.SetNextWindowPos(pos[, cond[, pivot]])
ImGui.SetNextWindowSize(size[, cond])
ImGui.SetNextWindowSizeConstraints(min, max)
ImGui.SetNextWindowContentSize(size)
ImGui.SetNextWindowCollapsed(collapsed[, cond])
ImGui.SetNextWindowFocus()
ImGui.SetNextWindowBgAlpha(alpha)
ImGui.SetWindowPos(pos[, cond])
ImGui.SetWindowSize(size[, cond])
ImGui.SetWindowCollapsed(collapsed[, cond])
ImGui.SetWindowFocus()
```

## Layout

```js
ImGui.Separator()
ImGui.SameLine([offsetFromStartX[, spacing]])
ImGui.NewLine()
ImGui.Spacing()
ImGui.Dummy(size)
ImGui.Indent([width])
ImGui.Unindent([width])
ImGui.BeginGroup()
ImGui.EndGroup()
ImGui.GetCursorPos()          // → { x, y }
ImGui.SetCursorPos(pos)
ImGui.GetCursorScreenPos()    // → absolute { x, y }
ImGui.SetCursorScreenPos(pos)
ImGui.AlignTextToFramePadding()
ImGui.GetTextLineHeight()
ImGui.GetFrameHeight()
ImGui.Columns([count[, id[, border]]])
ImGui.NextColumn()
ImGui.GetColumnIndex()
ImGui.SetColumnWidth(idx, width)
ImGui.SetColumnOffset(idx, offset)
```

## Widgets — Text

```js
ImGui.Text(fmt, ...)
ImGui.TextColored(color, fmt, ...)   // color: { x,y,z,w } (RGBA 0–1)
ImGui.TextDisabled(fmt, ...)
ImGui.TextWrapped(fmt, ...)
ImGui.LabelText(label, fmt, ...)
ImGui.BulletText(fmt, ...)
ImGui.Bullet()
```

## Widgets — Buttons

```js
ImGui.Button(label[, size])           // → bool (clicked)
ImGui.SmallButton(label)              // → bool
ImGui.InvisibleButton(id, size)       // → bool
ImGui.ArrowButton(id, dir)            // dir: ImGuiDir_Left/Right/Up/Down
ImGui.Image(textureId, size[, uv0[, uv1[, tintCol[, borderCol]]]])
ImGui.ImageButton(id, textureId, size[, uv0[, uv1[, bgCol[, tintCol]]]])
ImGui.Checkbox(label, { value: bool })      // → bool (changed)
ImGui.CheckboxFlags(label, flagsRef, flagsValue)
ImGui.RadioButton(label, active)            // → bool (clicked)
ImGui.ProgressBar(fraction[, size[, overlay]])
```

## Widgets — Input

```js
ImGui.InputText(label, { value: string }[, flags[, callback]])
ImGui.InputTextMultiline(label, { value: string }[, size[, flags[, callback]]])
ImGui.InputTextWithHint(label, hint, { value: string }[, flags[, callback]])
ImGui.InputFloat(label, { value: number }[, step[, stepFast[, format[, flags]]]])
ImGui.InputFloat2(label, [x, y][, format[, flags]])
ImGui.InputFloat3(label, [x, y, z][, format[, flags]])
ImGui.InputFloat4(label, [x, y, z, w][, format[, flags]])
ImGui.InputInt(label, { value: int }[, step[, stepFast[, flags]]])
ImGui.InputInt2(label, [x, y][, flags])
ImGui.InputInt3(label, [x, y, z][, flags])
ImGui.InputInt4(label, [x, y, z, w][, flags])
ImGui.InputDouble(label, { value: number }[, step[, stepFast[, format[, flags]]]])
```

## Widgets — Sliders

```js
ImGui.SliderFloat(label, { value: number }, min, max[, format[, flags]])
ImGui.SliderFloat2(label, [x,y], min, max)
ImGui.SliderFloat3(label, [x,y,z], min, max)
ImGui.SliderFloat4(label, [x,y,z,w], min, max)
ImGui.SliderAngle(label, { value: number }[, minDeg[, maxDeg]])
ImGui.SliderInt(label, { value: int }, min, max[, format[, flags]])
ImGui.SliderInt2(label, [x,y], min, max)
ImGui.SliderInt3(label, [x,y,z], min, max)
ImGui.SliderInt4(label, [x,y,z,w], min, max)
ImGui.VSliderFloat(label, size, { value: number }, min, max)
ImGui.VSliderInt(label, size, { value: int }, min, max)
```

## Widgets — Drag

```js
ImGui.DragFloat(label, { value: number }[, speed[, min[, max[, format[, flags]]]]])
ImGui.DragFloat2(label, [x,y][, speed[, min[, max]]])
ImGui.DragFloat3(label, [x,y,z][, ...])
ImGui.DragFloat4(label, [x,y,z,w][, ...])
ImGui.DragFloatRange2(label, { value: number }, { value: number }[, speed[, min[, max]]])
ImGui.DragInt(label, { value: int }[, speed[, min[, max[, format[, flags]]]]])
ImGui.DragInt2(label, [x,y][, ...])
ImGui.DragInt3(label, [x,y,z][, ...])
ImGui.DragInt4(label, [x,y,z,w][, ...])
```

## Widgets — Color

```js
ImGui.ColorEdit3(label, [r, g, b][, flags])
ImGui.ColorEdit4(label, [r, g, b, a][, flags])
ImGui.ColorPicker3(label, [r, g, b][, flags])
ImGui.ColorPicker4(label, [r, g, b, a][, flags[, refColor]])
ImGui.ColorButton(descId, color[, flags[, size]])
ImGui.SetColorEditOptions(flags)
```

## Trees & Collapsibles

```js
ImGui.TreeNode(label)                         // → bool (expanded)
ImGui.TreeNodeEx(label[, flags])
ImGui.TreePush(id)
ImGui.TreePop()
ImGui.GetTreeNodeToLabelSpacing()
ImGui.CollapsingHeader(label[, flags])        // → bool
ImGui.CollapsingHeader(label, { value: bool }[, flags])
ImGui.SetNextItemOpen(isOpen[, cond])
```

## Selectables & Lists

```js
ImGui.Selectable(label[, selected[, flags[, size]]])  // → bool (clicked)
ImGui.ListBox(label, { value: int }, items[, height])
ImGui.ListBoxHeader(label[, size])
ImGui.ListBoxFooter()
```

## Dropdowns

```js
ImGui.BeginCombo(label, previewValue[, flags])  // → bool
ImGui.EndCombo()
ImGui.Combo(label, { value: int }, items[, popupMaxHeight])
```

## Menus

```js
ImGui.BeginMenuBar()
ImGui.EndMenuBar()
ImGui.BeginMainMenuBar()
ImGui.EndMainMenuBar()
ImGui.BeginMenu(label[, enabled])  // → bool
ImGui.EndMenu()
ImGui.MenuItem(label[, shortcut[, selected[, enabled]]])  // → bool
```

## Popups & Modals

```js
ImGui.OpenPopup(id[, flags])
ImGui.OpenPopupOnItemClick(id[, flags])
ImGui.BeginPopup(id[, flags])           // → bool
ImGui.BeginPopupContextItem(id[, flags])
ImGui.BeginPopupContextWindow(id[, flags])
ImGui.BeginPopupModal(name[, open[, flags]])  // → bool
ImGui.EndPopup()
ImGui.CloseCurrentPopup()
ImGui.IsPopupOpen(id)
```

## Tabs

```js
ImGui.BeginTabBar(id[, flags])  // → bool
ImGui.EndTabBar()
ImGui.BeginTabItem(label[, open[, flags]])  // → bool
ImGui.EndTabItem()
ImGui.SetTabItemClosed(label)
```

## Tables

```js
ImGui.BeginTable(id, columns[, flags[, outerSize[, innerWidth]]])
ImGui.EndTable()
ImGui.TableSetupColumn(label[, flags[, initWidthOrWeight[, userId]]])
ImGui.TableSetupScrollFreeze(cols, rows)
ImGui.TableHeadersRow()
ImGui.TableHeader(label)
ImGui.TableNextRow([flags[, minRowHeight]])
ImGui.TableNextColumn()           // → bool (column visible)
ImGui.TableSetColumnIndex(idx)
ImGui.TableGetColumnCount()
ImGui.TableGetColumnName([idx])
ImGui.TableGetColumnFlags([idx])
```

## Plots

```js
ImGui.PlotLines(label, values[, valuesOffset[, overlayText[, scaleMin[, scaleMax[, graphSize]])]])
ImGui.PlotHistogram(label, values[, valuesOffset[, overlayText[, scaleMin[, scaleMax[, graphSize]])]])
```

## IO & Input

```js
const io = ImGui.GetIO();
io.DisplaySize          // { x, y }
io.DeltaTime
io.FontGlobalScale
io.MousePos             // { x, y }
io.MouseDown            // [bool × 5]
io.MouseWheel
io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper
io.WantCaptureMouse
io.WantCaptureKeyboard

ImGui.IsItemHovered([flags])
ImGui.IsItemActive()
ImGui.IsItemFocused()
ImGui.IsItemClicked([mouseButton])
ImGui.IsItemVisible()
ImGui.IsItemEdited()
ImGui.IsItemActivated()
ImGui.IsItemDeactivated()
ImGui.IsItemDeactivatedAfterEdit()
ImGui.IsAnyItemHovered()
ImGui.IsAnyItemActive()
ImGui.GetItemRectMin()     // → { x, y }
ImGui.GetItemRectMax()     // → { x, y }
ImGui.GetItemRectSize()    // → { x, y }

ImGui.IsKeyDown(key)
ImGui.IsKeyPressed(key[, repeat])
ImGui.IsKeyReleased(key)
ImGui.IsMouseDown(button)
ImGui.IsMouseClicked(button[, repeat])
ImGui.IsMouseReleased(button)
ImGui.IsMouseDoubleClicked(button)
ImGui.IsMouseHoveringRect(rMin, rMax[, clip])
ImGui.GetMousePos()        // → { x, y }
ImGui.GetMouseDragDelta([button[, lockThreshold]])
ImGui.ResetMouseDragDelta([button])
```

## Style

```js
ImGui.StyleColorsDark([dst])
ImGui.StyleColorsLight([dst])
ImGui.StyleColorsClassic([dst])
ImGui.GetStyle()              // → ImGuiStyle reference
ImGui.PushStyleColor(idx, col)
ImGui.PopStyleColor([count])
ImGui.PushStyleVar(idx, val)
ImGui.PopStyleVar([count])
ImGui.GetColorU32(idx[, alphaMul])
```

## Utilities

```js
ImGui.SetNextItemWidth(width)
ImGui.PushItemWidth(width)
ImGui.PopItemWidth()
ImGui.CalcTextSize(text[, textEnd[, hideTextAfterDoubleHash[, wrapWidth]]])
ImGui.GetFrameCount()
ImGui.GetTime()
ImGui.PushID(id)
ImGui.PopID()
ImGui.GetID(id)
ImGui.SetTooltip(fmt, ...)
ImGui.BeginTooltip()
ImGui.EndTooltip()
ImGui.SetClipboardText(text)
ImGui.GetClipboardText()
```

## Common flag constants

| Group | Examples |
|-------|---------|
| Window flags | `ImGuiWindowFlags_NoTitleBar`, `_NoResize`, `_NoMove`, `_NoScrollbar`, `_AlwaysAutoResize` |
| Input text flags | `ImGuiInputTextFlags_Password`, `_ReadOnly`, `_EnterReturnsTrue`, `_CallbackEdit` |
| TreeNode flags | `ImGuiTreeNodeFlags_DefaultOpen`, `_Leaf`, `_Selected`, `_Framed` |
| Selectable flags | `ImGuiSelectableFlags_AllowDoubleClick`, `_Disabled` |
| ComboBox flags | `ImGuiComboFlags_PopupAlignLeft`, `_HeightLargest` |
| TabBar flags | `ImGuiTabBarFlags_Reorderable`, `_AutoSelectNewTabs` |
| Table flags | `ImGuiTableFlags_Borders`, `_RowBg`, `_ScrollY`, `_Resizable`, `_Sortable` |
| Color edit flags | `ImGuiColorEditFlags_NoAlpha`, `_Float`, `_PickerHueWheel` |
| Direction | `ImGuiDir_Left`, `ImGuiDir_Right`, `ImGuiDir_Up`, `ImGuiDir_Down` |
| Condition | `ImGuiCond_Always`, `ImGuiCond_Once`, `ImGuiCond_FirstUseEver`, `ImGuiCond_Appearing` |
