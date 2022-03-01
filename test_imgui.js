import * as ImGui from 'imgui';
import * as glfw from 'glfw';
import { Console } from 'console';

function main() {
  globalThis.console = new Console(process.stdout, {
    inspectOptions: {
      colors: true,
      depth: 10,
      //stringBreakNewline: false,
      maxArrayLength: Infinity,
      compact: 1,
      maxStringLength: 60
    }
  });

  console.log('ImGui', ImGui);
  //console.log('glfw', Object.keys(glfw).filter(n => typeof glfw[n] == 'function'));

  let window;

  window = new glfw.Window(800, 600, 'ImGui test');
  //window ??= [1280,800];

  ImGui.Init(window);
  console.log('window.id', window.id);

  while(!window.shouldClose) {
    glfw.poll();

    ImGui.NewFrame();
    ImGui.Begin('This is a window');
    ImGui.Text('This is some useful text.');
    ImGui.Button('Button');
    ImGui.End();

    ImGui.Render();

    let data = ImGui.GetDrawData();
    //console.log('data',data);

    ImGui.RenderDrawData(data);
    window.swapBuffers();
  }
}

try {
  main(...scriptArgs.slice(1));
} catch(error) {
  console.log(`FAIL: ${error.message}\n${error.stack}`);
  std.exit(1);
} finally {
  console.log('SUCCESS');
}
