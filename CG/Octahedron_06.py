import glfw
from OpenGL.GL import *
from OpenGL.GLU import *

W_INIT = 360
H_INIT = 300

VERTEX = [
    [1.0, 0.0, 0.0],   # A
    [0.0, 0.0, 1.0],   # B
    [-1.0, 0.0, 0.0],   # C
    [0.0, 0.0, -1.0],   # D
    [0.0, 1.0, 0.0],   # E
    [0.0, -1.0, 0.0],   # F
]

EDGE = [
    [0, 1], # a (A-B)
    [1, 2], # i (B-C)
    [2, 3], # u (C-D)
    [3, 0], # e (D-A)
    [4, 0], # o (E-F)
    [4, 1], # ka (F-G)
    [4, 2], # ki (G-H)
    [4, 3], # ku (H-E)
    [5, 0], # ke (A-E)
    [5, 1], # ko (B-F)
    [5, 2], # sa (C-G)
    [5, 3]  # shi (D-H)
]

def display():
    glClear(GL_COLOR_BUFFER_BIT)

    glBegin(GL_LINES)
    for edge1 in EDGE:
        for i in edge1:
            glVertex3dv(VERTEX[i])
    glEnd()

    glfw.swap_buffers(window)

def set_view(w, h):
    glLoadIdentity()
    gluPerspective(35.0, w/h, 1.0, 100.0)
#    glTranslated(0.0, 0.0, -5.0)   # 8.3
    gluLookAt(4.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)    #8.4

def resize(window, w, h):
    # for iconify on Windows
    if h==0:
        return
    glViewport(0, 0, w, h)
    set_view(w, h)

def init():
    gray = 0.6
    glClearColor(gray, gray, gray, 1.0)
    set_view(W_INIT, H_INIT)
    display()   # necessary only on Windows

def window_refresh(window):
    display()

if not glfw.init():
    raise RuntimeError('Could not initialize GLFW3')

window = glfw.create_window(W_INIT, H_INIT, 'Octahedron_06', None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_window_size_callback(window, resize)
glfw.set_window_refresh_callback(window, window_refresh)
glfw.make_context_current(window)

init()

while not glfw.window_should_close(window):
    glfw.wait_events()

glfw.terminate()
