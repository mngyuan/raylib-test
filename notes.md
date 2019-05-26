want to try new functions (DrawTextureQuad, FormatText -> TextFormat)
raylib master library builds fine, makes streaks?
raylib 2.5-dev download library doesn't build, has errors:
```
~/Downloads/raylib-2.5-dev/src  ➜  make
clang -c rglfw.c -O1 -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Werror=pointer-arith -fno-strict-aliasing -Werror=implicit-function-declaration -x objective-c -I. -Iexternal/glfw/include -Iexternal/glfw/deps/mingw
-DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
In file included from rglfw.c:111:
./external/glfw/src/cocoa_init.m:278:1: error: expected identifier or '('
@interface GLFWHelper : NSObject
^
./external/glfw/src/cocoa_init.m:288:1: error: expected external
      declaration
- (void)doNothing:(id)object
^
./external/glfw/src/cocoa_init.m:288:4: error: expected identifier or '('
- (void)doNothing:(id)object
   ^
./external/glfw/src/cocoa_init.m:288:4: error: expected ')'
./external/glfw/src/cocoa_init.m:288:3: note: to match this '('
- (void)doNothing:(id)object
  ^
./external/glfw/src/cocoa_init.m:292:1: error: expected identifier or '('
@end // GLFWHelper
^
./external/glfw/src/cocoa_init.m:366:9: error: expected expression
        [NSApp setDelegate:nil];
        ^
./external/glfw/src/cocoa_init.m:367:9: error: expected expression
        [_glfw.ns.delegate release];
        ^
./external/glfw/src/cocoa_init.m:373:9: error: expected expression
        [[NSNotificationCenter defaultCenter]
        ^
./external/glfw/src/cocoa_init.m:377:9: error: expected expression
        [[NSNotificationCenter defaultCenter]
        ^
./external/glfw/src/cocoa_init.m:379:9: error: expected expression
        [_glfw.ns.helper release];
        ^
./external/glfw/src/cocoa_init.m:384:9: error: expected expression
        [NSEvent removeMonitor:_glfw.ns.keyUpMonitor];
        ^
./external/glfw/src/cocoa_init.m:391:5: error: expected expression
    [_glfw.ns.autoreleasePool release];
    ^
In file included from rglfw.c:113:
./external/glfw/src/cocoa_monitor.m:377:9: error: use of undeclared
      identifier 'NSUInteger'
        NSUInteger i;
        ^
./external/glfw/src/cocoa_monitor.m:378:9: error: use of undeclared
      identifier 'NSArray'
        NSArray* screens = [NSScreen screens];
        ^
./external/glfw/src/cocoa_monitor.m:378:18: error: use of undeclared
      identifier 'screens'
        NSArray* screens = [NSScreen screens];
                 ^
./external/glfw/src/cocoa_monitor.m:378:28: error: expected expression
        NSArray* screens = [NSScreen screens];
                           ^
./external/glfw/src/cocoa_monitor.m:380:14: error: use of undeclared
      identifier 'i'
        for (i = 0;  i < [screens count];  i++)
             ^
./external/glfw/src/cocoa_monitor.m:380:26: error: expected expression
        for (i = 0;  i < [screens count];  i++)
                         ^
./external/glfw/src/cocoa_monitor.m:380:22: error: use of undeclared
      identifier 'i'
        for (i = 0;  i < [screens count];  i++)
                     ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
make: *** [rglfw.o] Error 1<Paste>
```
jumping to the commit 2.5-dev release was made on (1934f2a) builds fine, but has streaks
building with:
`gcc -o ships ships.c -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo libraylib.a`
gives streaks
also gives a pointer warning when compiling with TextFormat:
```
~/git/personal/raylib-test  ➜  gcc -o ships ships.c -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo libraylib.a
ships.c:111:26: warning: implicit declaration of function 'TextFormat' is
      invalid in C99 [-Wimplicit-function-declaration]
                DrawText(TextFormat("%02i FPS", framesSpeed), 575, ...
                         ^
ships.c:111:26: warning: incompatible integer to pointer conversion passing      'int' to parameter of type 'const char *' [-Wint-conversion]
                DrawText(TextFormat("%02i FPS", framesSpeed), 575, ...
                         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/usr/local/include/raylib.h:1003:33: note: passing argument to parameter
      'text' here
RLAPI void DrawText(const char *text, int posX, int posY, int fontS...
                                ^
2 warnings generated.
```
seems to cause a segfault:
```
INFO: Initializing raylib 2.5-dev
INFO: Display device initialized successfully
INFO: Display size: 2560 x 1440
INFO: Render size: 1280 x 720
INFO: Screen size: 1280 x 720
INFO: Viewport offsets: 0, 0
INFO: GPU: Vendor:   NVIDIA Corporation
INFO: GPU: Renderer: NVIDIA GeForce GT 750M OpenGL Engine
INFO: GPU: Version:  4.1 NVIDIA-12.0.23 355.11.10.50.10.103
INFO: GPU: GLSL:     4.10
INFO: Number of supported extensions: 47
INFO: [EXTENSION] DXT compressed textures supported
INFO: [EXTENSION] Anisotropic textures filtering supported (max: 16X)
INFO: [EXTENSION] Mirror clamp wrap texture mode supported
INFO: [EXTENSION] Debug Marker supported
INFO: [TEX ID 1] Texture created successfully (1x1 - 1 mipmaps)
INFO: [TEX ID 1] Base white texture loaded successfully
INFO: [SHDR ID 1] Shader compiled successfully
INFO: [SHDR ID 2] Shader compiled successfully
INFO: [SHDR ID 3] Shader program loaded successfully
INFO: [SHDR ID 3] Default shader loaded successfully
INFO: Internal buffers initialized successfully (CPU)
INFO: Internal buffers uploaded successfully (GPU)
INFO: OpenGL default states initialized successfully
INFO: [TEX ID 2] Texture created successfully (128x128 - 1 mipmaps)
INFO: [TEX ID 2] Default font loaded successfully
INFO: [resources/ships.png] Image loaded successfully (96x48)
INFO: [TEX ID 3] Texture created successfully (96x48 - 1 mipmaps)
INFO: [resources/ocean.png] Image loaded successfully (160x160)
INFO: [TEX ID 4] Texture created successfully (160x160 - 1 mipmaps)
INFO: [TEX ID 5] Texture created successfully (1280x720 - 1 mipmaps)
INFO: [FBO ID 1] Framebuffer object created successfully
INFO: [TEX ID 6] Texture created successfully (1280x720 - 1 mipmaps)
INFO: [FBO ID 2] Framebuffer object created successfully
INFO: Target time per frame: 16.667 milliseconds
[1]    71302 segmentation fault  ./ships
```
