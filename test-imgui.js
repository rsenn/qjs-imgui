import * as ImGui from 'imgui';
import * as glfw from 'glfw';

Object.assign(globalThis, { ImGui, glfw });

let window;

let menuEnabled,
  floatValue = 0.5,
  intValue = 0,
  boolValue = true;

  let checked = true;

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
  }
}

function main() {
  window = new glfw.Window(800, 600, 'ImGui test');
  //window ??= [1280,800];

  ImGui.Init(window);
  console.log('ImGui.WindowFlags.MenuBar', ImGui.WindowFlags.MenuBar);

  while(!window.shouldClose) {
    glfw.poll();

    ImGui.NewFrame();
    ImGui.Begin('This is a window', null, ImGui.WindowFlags.MenuBar);
    ImGui.PushItemWidth(ImGui.GetFontSize() * -12);

    ImGui.Text('This is some useful text.');
    ImGui.Button('Button');
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

    let ptr = ImGui.Pointer(
      () => show_app_main_menu_bar,
      v => (show_app_main_menu_bar = v)
    );

    let ptr2 = ImGui.Pointer(false);
    let show_demo_window = ImGui.Pointer(false);

    /*console.log('ptr2()', ptr2());
    console.log((ptr2(true), 'ptr2(true)'));
    console.log('ptr2()', ptr2());
    console.log((ptr2(false), 'ptr2(false)'));*/

    ImGui.ShowDemoWindow(show_demo_window);

    // Menu Bar
    if(ImGui.BeginMenuBar()) {
      if(ImGui.BeginMenu('Menu')) {
        ShowExampleMenuFile();
        ImGui.EndMenu();
      }
      if(ImGui.BeginMenu('Examples')) {
        ImGui.MenuItem(
          'Main menu bar',
          null,
          ptr ?? (v => (v === undefined ? show_app_main_menu_bar : (show_app_main_menu_bar = v)))
        );

        //console.log('show_app_main_menu_bar', show_app_main_menu_bar);

        ImGui.MenuItem('Show Demo Window', null, show_demo_window);
        ImGui.MenuItem('Console', null, v => (v === undefined ? show_app_console : (show_app_console = v)));
        ImGui.MenuItem('Log', null, v => (v === undefined ? show_app_log : (show_app_log = v)));
        ImGui.MenuItem('Simple layout', null, v => (v === undefined ? show_app_layout : (show_app_layout = v)));
        ImGui.MenuItem('Property editor', null, v =>
          v === undefined ? show_app_property_editor : (show_app_property_editor = v)
        );
        ImGui.MenuItem('Long text display', null, v =>
          v === undefined ? show_app_long_text : (show_app_long_text = v)
        );
        ImGui.MenuItem('Auto-resizing window', null, v =>
          v === undefined ? show_app_auto_resize : (show_app_auto_resize = v)
        );
        ImGui.MenuItem('Constrained-resizing window', null, v =>
          v === undefined ? show_app_constrained_resize : (show_app_constrained_resize = v)
        );
        ImGui.MenuItem('Simple overlay', null, v =>
          v === undefined ? show_app_simple_overlay : (show_app_simple_overlay = v)
        );
        ImGui.MenuItem('Fullscreen window', null, v =>
          v === undefined ? show_app_fullscreen : (show_app_fullscreen = v)
        );
        ImGui.MenuItem('Manipulating window titles', null, v =>
          v === undefined ? show_app_window_titles : (show_app_window_titles = v)
        );
        ImGui.MenuItem('Custom rendering', null, v =>
          v === undefined ? show_app_custom_rendering : (show_app_custom_rendering = v)
        );
        ImGui.MenuItem('Documents', null, v => (v === undefined ? show_app_documents : (show_app_documents = v)));
        ImGui.EndMenu();
      }
      //if (ImGui.MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
      if(ImGui.BeginMenu('Tools')) {
        ImGui.MenuItem('Metrics/Debugger', null, v => (v === undefined ? show_app_metrics : (show_app_metrics = v)));
        ImGui.MenuItem('Style Editor', null, v =>
          v === undefined ? show_app_style_editor : (show_app_style_editor = v)
        );
        ImGui.MenuItem('About Dear ImGui', null, v => (v === undefined ? show_app_about : (show_app_about = v)));
        ImGui.EndMenu();
      }
      ImGui.EndMenuBar();
    }

    ImGui.End();

    ImGui.Render();

    let data = ImGui.GetDrawData();
    //console.log('data',data);

    ImGui.RenderDrawData(data);
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
