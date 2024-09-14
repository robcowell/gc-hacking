# gc-hacking
Terrible gamecube coding with DevKitPro, libogc, GRRLib

14/9/2024 - Started experimenting with TEVs

### Texture Environment Units (TEVs)

The **GameCube's Texture Environment Unit (TEV)** is a powerful fixed-function hardware component that enables advanced per-pixel operations in the rendering pipeline. It allows developers to combine textures, colors, and constants in highly flexible ways, enabling effects like multi-texturing, light mapping, and complex blending without needing a programmable shader.

The TEV operates through multiple stages (up to 16), each of which can perform operations like addition, subtraction, or modulation on texture values and color channels. By configuring the TEV, developers can blend textures in creative ways, apply real-time lighting effects, and create various visual effects like bump mapping, shadowing, and film grain.

In this project, the TEV is used to overlay a procedurally generated film grain texture on top of the main scene texture. The grain is blended using the additive mode, creating a subtle effect that preserves the original colors of the scene.

Key capabilities of the TEV include:
- **Multi-texturing**: Combine multiple textures in one pass, reducing the need for multiple rendering passes.
- **Blending**: Apply various blending operations (addition, modulation, subtraction) between textures and color channels.
- **Color/Alpha Control**: Flexibly adjust how textures and colors contribute to the final image by controlling how RGB and alpha values are mixed.
- **Per-Pixel Effects**: TEV operates on a per-pixel basis, allowing for fine-grained control over visual effects and texture blending.

By leveraging the TEV's capabilities, developers can create rich, dynamic visual effects while maintaining optimal performance on the GameCube's hardware.


