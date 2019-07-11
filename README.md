# EmbeddedGraphics
Bachelor thesis for HTW Media and Computing: "Implementation and optimization of graphics algorithms on resource limited hardware". 
## Requirments
- A STM32F746G Discovery board
  - needs external SDRAM
  - needs screen attached to the LTDC peripheral
- gcc compiler
- make utility
## Implementation
- 2D rendering algorithms:
  - dot
  - line
  - rectangle
  - circle
  - triangle
  - text
  - (not tested) images
- low level system initialization (no library headers used)
- implemented in C (C++ is not supported yet)
- framebuffer is located in it's own section in memory
- double buffering
- vertical synchronization
