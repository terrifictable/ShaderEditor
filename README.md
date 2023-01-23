# Shader Editor and Viewer using ImGui
This is supposed to become a opengl (glsl) shader editor and viewer<br>
its using [ImGui](https://github.com/ocornut/imgui)

<br>

## Showcase
![img.png](img.png)

<br>

## ToDo
- Use Zep instead of ImGuiColoredTextEditor
- Settings for shaders like custom uniforms and other things

<br>

#### Folder structure
shader_editor/
- comp/
  - *output of `make comp_libs`*
- include/
    - glad
    - GLFW
    - imgui
    - KHR
- lib/
  - glfw3.dll
  - glfw3_mt.lib
  - glfw3dll.lib
- out/
  - glfw3.dll
  - roboto.ttf
- shaders/
  - default.fsh
  - default.vsh
- src/
  - glad.c
  - imgui/
    - TextEditor.cpp (from https://github.com/BalazsJako/ColorTextEditorDemo)
    - TextEditor.h (also from https://github.com/BalazsJako/ColorTextEditorDemo)
  - *other files should already be there*
