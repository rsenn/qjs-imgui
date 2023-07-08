import { context } from 'glfw';
import { CONTEXT_VERSION_MAJOR } from 'glfw';
import { CONTEXT_VERSION_MINOR } from 'glfw';
import { OPENGL_CORE_PROFILE } from 'glfw';
import { OPENGL_FORWARD_COMPAT } from 'glfw';
import { OPENGL_PROFILE } from 'glfw';
import { poll } from 'glfw';
import { RESIZABLE } from 'glfw';
import { SAMPLES } from 'glfw';
import { Window } from 'glfw';
import * as ImGui from 'imgui';
import * as nvg from 'nanovg';
let window /*, nvg*/;

export function Clear(color = nvg.RGB(0, 0, 0)) {
  const { size } = window;

  nvg.Save();
  nvg.BeginPath();
  nvg.Rect(0, 0, ...size);
  nvg.FillColor(color);
  nvg.Fill();
  nvg.Restore();
}

let menuEnabled,
  floatValue = 0.5,
  intValue = 0,
  boolValue = true;

let running = true,
  checked = true;

// Note that shortcuts are currently provided for display only
// (future version will add explicit flags to BeginMenu() to request processing shortcuts)
function ShowExampleMenuFile() {
  ImGui.MenuItem('(demo menu)', null, false, false);

  if(ImGui.MenuItem('New')) {
  }
  if(ImGui.MenuItem('Open', 'Ctrl+O')) {
  }
  if(ImGui.BeginMenu('Open Recent')) {
    ImGui.MenuItem('fish_hat.c');
    ImGui.MenuItem('fish_hat.inl');
    ImGui.MenuItem('fish_hat.h');
    if(ImGui.BeginMenu('More..')) {
      ImGui.MenuItem('Hello');
      ImGui.MenuItem('Sailor');
      if(ImGui.BeginMenu('Recurse..')) {
        ShowExampleMenuFile();
        ImGui.EndMenu();
      }
      ImGui.EndMenu();
    }
    ImGui.EndMenu();
  }
  if(ImGui.MenuItem('Save', 'Ctrl+S')) {
  }
  if(ImGui.MenuItem('Save As..')) {
  }

  ImGui.Separator();
  if(ImGui.BeginMenu('Options')) {
    ImGui.MenuItem('Enabled', '', val => (val === undefined ? menuEnabled : (menuEnabled = val)));
    ImGui.BeginChild('child', [0, 60], true);
    for(let i = 0; i < 10; i++) ImGui.Text('Scrolling Text %d', i);
    ImGui.EndChild();

    ImGui.SliderFloat('Value', val => (val === undefined ? floatValue : (floatValue = val)), 0.0, 1.0);
    ImGui.InputFloat('Input', val => (val === undefined ? floatValue : (floatValue = val)), 0.1);
    ImGui.Combo('Combo', val => (val === undefined ? intValue : (intValue = val)), 'Yes\0No\0Maybe\0\0');
    ImGui.EndMenu();
  }

  if(ImGui.BeginMenu('Colors')) {
    let sz = ImGui.GetTextLineHeight();
    for(let i = 0; i < ImGui.Col.COUNT; i++) {
      let name = ImGui.GetStyleColorName(i);
      let p = ImGui.GetCursorScreenPos();

      let dl = ImGui.GetWindowDrawList();

      if(dl) {
        console.log('GetWindowDrawList() =', dl);
        dl.AddRectFilled(p, [p.x + sz, p.y + sz], ImGui.GetColorU32(i));
      }
      ImGui.Dummy([sz, sz]);
      ImGui.SameLine();
      ImGui.MenuItem(name);
    }
    ImGui.EndMenu();
  }

  // Here we demonstrate appending again to the 'Options' menu (which we already created above)
  // Of course in this demo it is a little bit silly that this function calls BeginMenu('Options') twice.
  // In a real code-base using it would make senses to use this feature from very different code locations.
  if(ImGui.BeginMenu('Options')) {
    // <-- Append!
    ImGui.Checkbox('SomeOption', val => (val === undefined ? boolValue : (boolValue = val)));
    ImGui.EndMenu();
  }

  if(ImGui.BeginMenu('Disabled', false)) {
    // Disabled
    throw new Error(`IM_ASSERT(0)`);
  }
  if(ImGui.MenuItem('Checked', null, checked)) {
    checked = !checked;
    console.log('checked =', checked);
  }
  if(ImGui.MenuItem('Quit', 'Alt+F4')) {
    running = false;
  }
}

let show_app_main_menu_bar,
  show_app_console,
  show_app_log,
  show_app_layout,
  show_app_property_editor,
  show_app_long_text,
  show_app_auto_resize,
  show_app_constrained_resize,
  show_app_simple_overlay,
  show_app_fullscreen,
  show_app_window_titles,
  show_app_custom_rendering,
  show_app_documents,
  show_app_metrics,
  show_app_style_editor,
  show_app_about;
// let show = {};

const wrapGetSet = (gfn, fn) => [
  gfn,
  value => {
    let old = gfn();
    if(value !== old) {
      fn(value);
      console.log('value changed from', old, 'to', value);
    }
  }
];

let ptr = ImGui.Pointer(
  ...wrapGetSet(
    () => show_app_main_menu_bar,
    v => (show_app_main_menu_bar = v)
  )
);

let ptr2 = ImGui.Pointer(false);

let show_about_box = ImGui.Pointer(
  () => show_app_about,
  value => (show_app_about = value)
);
let show_demo_window = ImGui.Pointer(false);
let show_light_bg = ImGui.Pointer(true);
let slider_value = ImGui.Pointer(0);
let text_buf = new ArrayBuffer(4096);
let text_buf2 = new ArrayBuffer(4096 * 16);
let slider2_value = [0, 0];
let float_value = ImGui.Pointer(0.0);
let scalar_value = new Float64Array([0]);

let combo_index = 1;
let combo_value = ImGui.Pointer(
  ...wrapGetSet(
    () => combo_index,
    value => (combo_index = value)
  )
);

function main() {
  for(let [prop, value] of [
    [CONTEXT_VERSION_MAJOR, 3],
    [CONTEXT_VERSION_MINOR, 2],
    [OPENGL_PROFILE, OPENGL_CORE_PROFILE],
    [OPENGL_FORWARD_COMPAT, true],
    [RESIZABLE, true],
    [SAMPLES, 4]
  ])
    Window.hint(prop, value);

  window = context.current = ImGui.ImplGlfw.CreateWindow = new Window(1280, 800, 'ImGui test');
  console.log('new Window() =', window.id);

  window.handleChar = c => {
    let s = String.fromCharCode(c);
    if(s == 'q') {
      running = false;
    } else {
      console.log('handleChar', { c, s });
    }
  };

  let ok = nvg.CreateGL3(nvg.STENCIL_STROKES | nvg.ANTIALIAS | nvg.DEBUG);
  console.log('nvg.CreateGL3() =', ok);

  ImGui.Init(ImGui.ImplGlfw, ImGui.ImplOpenGL3);
  ImGui.CreateContext(window);
  ImGui.StyleColorsDark();

  // import('nanovg').then(m => ((nvg = m), nvg.CreateGL3(nvg.STENCIL_STROKES | nvg.ANTIALIAS | nvg.DEBUG)));

  console.log('ImGui.WindowFlags.MenuBar', ImGui.WindowFlags.MenuBar);

  while(!window.shouldClose && running) {
    poll();

    ImGui.NewFrame();

    ImGui.Begin('This is a window', null, ImGui.WindowFlags.MenuBar);

    ImGui.SetWindowSize([800, 600]);

    ImGui.PushItemWidth(ImGui.GetFontSize() * -12);

    ImGui.Text('This is some Text');

    ImGui.Checkbox('Show About', show_about_box);
    ImGui.Checkbox('Show Demo Window', show_demo_window);
    ImGui.Checkbox('Light Background', show_light_bg);
    ImGui.SliderFloat('Slider', slider_value, 0, 300, '%3.0f', 0);
    ImGui.SliderFloat2('Slider2', slider2_value, 0, 300, '%3.0f', 0);
    let items = ['beer', 'salad', 'pizza', 'pineapple'];

    ImGui.Combo('Combo', combo_value, idx => items[idx], items.length);

    //ImGui.InputScalar('Scalar', ImGui.DataType.Double, scalar_value, 1, 10, '%3.0f', ImGui.InputTextFlags.CallbackAlways);
    let s8_v = new Int8Array(1);
    let u8_v = new Uint8Array(1);
    let s16_v = new Int16Array(1);
    let u16_v = new Uint16Array(1);
    let s32_v = new Int32Array([-1337]);
    let u32_v = new Uint32Array([1337]);
    let s64_v = new BigInt64Array([-1000n]);
    let u64_v = new BigUint64Array([1000n]);
    let f32_v = new Float32Array([Math.PI]);
    let f64_v = new Float64Array([Math.E]);

    ImGui.InputScalar('input s8', ImGui.DataType.S8, s8_v, 1, 10, '%d');
    ImGui.InputScalar('input u8', ImGui.DataType.U8, u8_v, 1, 10, '%u');
    ImGui.InputScalar('input s16', ImGui.DataType.S16, s16_v, 1, 10, '%d');
    ImGui.InputScalar('input u16', ImGui.DataType.U16, u16_v, 1, 10, '%u');
    ImGui.InputScalar('input s32', ImGui.DataType.S32, s32_v, 1, 10, '%d');
    ImGui.InputScalar('input s32 hex', ImGui.DataType.S32, s32_v, 1, 10, '%08X');
    ImGui.InputScalar('input u32', ImGui.DataType.U32, u32_v, 1, 10, '%u');
    ImGui.InputScalar('input u32 hex', ImGui.DataType.U32, u32_v, 1, 10, '%08X');
    ImGui.InputScalar('input s64', ImGui.DataType.S64, s64_v, 1, 10);
    ImGui.InputScalar('input u64', ImGui.DataType.U64, u64_v, 1, 10);
    ImGui.InputScalar('input float', ImGui.DataType.Float, f32_v, 1, 10);
    ImGui.InputScalar('input double', ImGui.DataType.Double, f64_v, 1, 10);

    ImGui.InputTextMultiline('Text', text_buf2, text_buf2.byteLength, [100, 30], ImGui.InputTextFlags.CallbackAlways, data => console.log('InputTextMultiline event', data));
    ImGui.InputFloat('Float', float_value, 1, 10, null, 0); //ImGui.InputTextFlags.CallbackAlways, data => console.log('InputFloat event', data));
    false &&
      ImGui.InputText('Text', text_buf, text_buf.byteLength, ImGui.InputTextFlags.CallbackAlways, data => {
        /* prettier-ignore */ const {EventFlag, Flags, EventChar, EventKey, buf, BufTextLen, BufSize, BufDirty, CursorPos, SelectionStart, SelectionEnd, DeleteChars, InsertChars, SelectAll, ClearSelection } = data;
        /* prettier-ignore */ console.log('InputText event', {EventFlag, Flags, EventChar, EventKey, buf, BufTextLen, BufSize, BufDirty, CursorPos, SelectionStart, SelectionEnd, DeleteChars, InsertChars, SelectAll, ClearSelection });
      });

    //if(ImGui.Button(!show_light_bg() ? 'Light' : 'Dark')) show_light_bg(!show_light_bg());
    //if(ImGui.Button((!show_about_box() ? 'Show' : 'Hide') + ' about')) show_about_box(!show_about_box());
    //if(ImGui.Button((!show_demo_window() ? 'Show' : 'Hide') + ' demo')) show_demo_window(!show_demo_window());

    if(show_about_box()) ImGui.ShowAboutWindow(show_about_box);

    if(show_demo_window()) ImGui.ShowDemoWindow(show_demo_window);

    // Menu Bar
    if(ImGui.BeginMenuBar()) {
      if(ImGui.BeginMenu('Menu')) {
        ShowExampleMenuFile();
        ImGui.EndMenu();
      }
      if(ImGui.BeginMenu('Examples')) {
        ImGui.MenuItem('Main menu bar', null, ptr ?? (v => (v === undefined ? show_app_main_menu_bar : (show_app_main_menu_bar = v))));

        //console.log('show_app_main_menu_bar', show_app_main_menu_bar);

        ImGui.MenuItem('Show Demo Window', null, show_demo_window);
        ImGui.MenuItem('Console', null, v => (v === undefined ? show_app_console : (show_app_console = v)));
        ImGui.MenuItem('Log', null, v => (v === undefined ? show_app_log : (show_app_log = v)));
        ImGui.MenuItem('Simple layout', null, v => (v === undefined ? show_app_layout : (show_app_layout = v)));
        ImGui.MenuItem('Property editor', null, v => (v === undefined ? show_app_property_editor : (show_app_property_editor = v)));
        ImGui.MenuItem('Long text display', null, v => (v === undefined ? show_app_long_text : (show_app_long_text = v)));
        ImGui.MenuItem('Auto-resizing window', null, v => (v === undefined ? show_app_auto_resize : (show_app_auto_resize = v)));
        ImGui.MenuItem('Constrained-resizing window', null, v => (v === undefined ? show_app_constrained_resize : (show_app_constrained_resize = v)));
        ImGui.MenuItem('Simple overlay', null, v => (v === undefined ? show_app_simple_overlay : (show_app_simple_overlay = v)));
        ImGui.MenuItem('Fullscreen window', null, v => (v === undefined ? show_app_fullscreen : (show_app_fullscreen = v)));
        ImGui.MenuItem('Manipulating window titles', null, v => (v === undefined ? show_app_window_titles : (show_app_window_titles = v)));
        ImGui.MenuItem('Custom rendering', null, v => (v === undefined ? show_app_custom_rendering : (show_app_custom_rendering = v)));
        ImGui.MenuItem('Documents', null, v => (v === undefined ? show_app_documents : (show_app_documents = v)));
        ImGui.EndMenu();
      }
      //if (ImGui.MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
      if(ImGui.BeginMenu('Tools')) {
        ImGui.MenuItem('Metrics/Debugger', null, v => (v === undefined ? show_app_metrics : (show_app_metrics = v)));
        ImGui.MenuItem('Style Editor', null, v => (v === undefined ? show_app_style_editor : (show_app_style_editor = v)));
        ImGui.MenuItem('About Dear ImGui', null, v => (v === undefined ? show_app_about : (show_app_about = v)));
        ImGui.EndMenu();
      }
      ImGui.EndMenuBar();
    }

    ImGui.End();

    ImGui.Render();

    if(ok) {
      nvg.BeginFrame(...window.size, 1);
      Clear(nvg.RGB(...(show_light_bg() ? [0x66, 0x88, 0xff] : [0, 0, 0])));

      nvg.BeginPath();

      nvg.Translate(window.size.width / 2, window.size.height / 2);
      nvg.Scale(3, 3);
      nvg.Translate(-50, -50);

      nvg.MoveTo(50, 0);
      nvg.LineTo(100, 50);
      nvg.LineTo(50, 100);
      nvg.LineTo(0, 50);
      nvg.ClosePath();

      nvg.StrokeColor(nvg.RGB(255, 255, 40));
      nvg.StrokeWidth(2);
      nvg.Stroke();

      nvg.EndFrame();
    }

    let data = ImGui.GetDrawData();
    ImGui.RenderDrawData(data);

    /*let { id, Valid, CmdListsCount, TotalIdxCount, TotalVtxCount, DisplayPos, DisplaySize, FramebufferScale } = data;
    console.log('data', id, { Valid, CmdListsCount, TotalIdxCount, TotalVtxCount, DisplayPos, DisplaySize, FramebufferScale });*/

    window.swapBuffers();
  }
}

const runMain = () => {
  try {
    main(...scriptArgs.slice(1));
    std.exit(0);
  } catch(error) {
    console.log('ERROR:', error);
  }
};
import('console') .catch(runMain) .then(({ Console }) => ((globalThis.console = new Console({ inspectOptions: {} })), runMain()));