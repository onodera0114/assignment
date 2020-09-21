import glfw
from OpenGL.GL import *
from math import *

N = 3
W = 1
r = 0.9

def display():
    global N
    glClear(GL_COLOR_BUFFER_BIT)

    glColor3d(0.0, 0.0, 1.0)
    glBegin(GL_POLYGON)

    if N % 2 == 0:
      phi = pi / N
    else:
      phi = pi / 2

    for i in range(1, N + 1):
      x = r * cos(2 * pi * i / N + phi)
      y = r * sin(2 * pi * i / N + phi)
      glVertex2d(x, y)
    glEnd()

    glfw.swap_buffers(window)

def init():
    gray = 0.90
    glClearColor(gray, gray, gray, 1.0)
    glOrtho(-W, W, -W, W, -1.0, 1.0)
    display()   # necessary only on Windows

def keyboard(window, key, scancode, action, mods):
    if key == glfw.KEY_UP and action == glfw.PRESS:
      count_number(1)
    if key == glfw.KEY_DOWN and action == glfw.PRESS:
      count_number(-1)

def mouse_button(window, button, action, mods):
    if button == glfw.MOUSE_BUTTON_LEFT and action == glfw.PRESS:
      count_number(1)
    if button == glfw.MOUSE_BUTTON_RIGHT and action == glfw.PRESS:
      count_number(-1)

def scroll(window, xoffset, yoffset):
    if yoffset == 1.0:
      count_number(1)
    if yoffset == -1.0:
      count_number(-1)

def count_number(count):
  global N
  N += count

  if N < 3:
    N = 12
  if N > 12:
    N = 3

  display()

def window_refresh(window):
    display()

if not glfw.init():
    raise RuntimeError('Could not initialize GLFW3')

window = glfw.create_window(300, 300, 'polygon_06', None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_key_callback(window, keyboard)
glfw.set_mouse_button_callback(window, mouse_button)
glfw.set_scroll_callback(window, scroll)
glfw.set_window_refresh_callback(window, window_refresh)
glfw.make_context_current(window)

init()

while not glfw.window_should_close(window):
    glfw.wait_events()

glfw.terminate()
