import glfw
import time
from OpenGL.GL import *
from OpenGL.GLU import *
from math import *

W_INIT = 360
H_INIT = 360

class Face:
    def __init__(self, i_vertex, normal):
        self.i_vertex = i_vertex
        self.normal = normal

FACE = (
    Face((3, 2, 1, 0), ( 0.0,  0.0, -1.0)),
    Face((2, 6, 5, 1), ( 1.0,  0.0,  0.0)),
    Face((6, 7, 4, 5), ( 0.0,  0.0,  1.0)),
    Face((7, 3, 0, 4), (-1.0,  0.0,  0.0)),
    Face((0, 1, 5, 4), ( 0.0, -1.0,  0.0)),
    Face((7, 6, 2, 3), ( 0.0,  1.0,  0.0)))

GROUND = (
    (1.5, 1.5, 34.5),
    (1.5, 1.5, 7.5),
    (1.5, 1.5, 32.0),
    (1.5, 1.5, 18.5),
    (1.5, 1.5, 8.0))
BLOCK = (
    (0.5, 0.5, 0.5),
    (0.5, 0.5, 4.0),
    (0.5, 0.5, 1.5),
    (0.5, 0.5, 1.0),
    (0.5, 1.0, 0.5),
    (0.5, 1.5, 0.5),
    (0.5, 2.0, 0.5),
    (0.5, 2.5, 0.5),
    (0.5, 3.0, 0.5),
    (0.5, 3.5, 0.5),
    (0.5, 4.0, 0.5))
PIPE =(
    (0.9, 0.75, 0.9),
    (1.0, 0.25, 1.0),
    (0.9, 1.25, 0.9),
    (0.9, 1.75, 0.9))
GOAL =(
    (0.5, 0.5, 0.5),
    (0.15, 4.5, 0.15),
    (0.3, 0.3, 0.3),
    (1.5, 1.5, 2.5),
    (1.5, 1.0, 1.5))

LIGHTPOS = (3.0, 4.0, 5.0, 1.0)
GREEN = (0.392, 0.8, 0.224, 1.0)
BROWN = (0.627, 0.33, 0.133, 1.0)
GRAY = (1.0, 1.0, 1.0, 1.0)
YELLOW = (0.812, 0.69, 0.224, 1.0)
GRAY = (0.55, 0.533, 0.53, 1.0)
JUMPING = False
MODE = 'Subjective'

sy = -1.0
sz = 0.5
oz = 10.0

def vertex_box(x, y, z):
    vertex = (
        (-x, -y, -z),   # A
        ( x, -y, -z),   # B
        ( x,  y, -z),   # C
        (-x,  y, -z),   # D
        (-x, -y,  z),   # E
        ( x, -y,  z),   # F
        ( x,  y,  z),   # G
        (-x,  y,  z))   # H
    return vertex

def create_Box(vertex):
    glBegin(GL_QUADS)
    for face1 in FACE:
        glNormal3dv(face1.normal)
        for i in face1.i_vertex:
            glVertex3dv(vertex[i])
    glEnd()

def display():
    global DeltaMove, sy, sz, MODE, oz
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )
    glLoadIdentity()
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS)

    if MODE == 'Subjective':
        glRotated(0.0, 0.0, 1.0, 0.0)
        glTranslated(0.0, sy, sz)
        sz += DeltaMove
    if MODE == 'Objective':
        glRotated(-90.0, 0.0, 1.0, 0.0)
        glTranslated(-25.0, -5.0, oz)
        oz += DeltaMove

    gen_Field()

    glfw.swap_buffers(window)

def gen_Field():
    glTranslated(0.0, -1.5, -34.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(GROUND[0][0], GROUND[0][1], GROUND[0][2]))

    glTranslated(0.0, 0.0, -44)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(GROUND[1][0], GROUND[1][1], GROUND[1][2]))

    glTranslated(0.0, 0.0, -42.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(GROUND[2][0], GROUND[2][1], GROUND[2][2]))

    glTranslated(0.0, 0.0, -52.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(GROUND[3][0], GROUND[3][1], GROUND[3][2]))

    glTranslated(0.0, 0.0, -26.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(GROUND[4][0], GROUND[4][1], GROUND[4][2]))

    glTranslated(0.0, 1.5, 199.5)
    glTranslated(0.0, 3.5, -17)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -4)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 4.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, -4.0, -1)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -52)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 4, -4.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[1][0], BLOCK[1][1], BLOCK[1][2]))

    glTranslated(0.0, 0.0, -8.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[2][0], BLOCK[2][1], BLOCK[2][2]))

    glTranslated(0.0, 0.0, -2.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, -4.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -6.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[3][0], BLOCK[3][1], BLOCK[3][2]))

    glTranslated(0.0, 0.0, -5.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -3.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 4.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, -4.0, -3.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -6.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 4.0, -4.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[2][0], BLOCK[2][1], BLOCK[2][2]))

    glTranslated(0.0, 0.0, -6.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[3][0], BLOCK[3][1], BLOCK[3][2]))

    glTranslated(0.0, -4.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[3][0], BLOCK[3][1], BLOCK[3][2]))

    glTranslated(0.0, 4.0, -1.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, -7.0, -3.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[4][0], BLOCK[4][1], BLOCK[4][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[5][0], BLOCK[5][1], BLOCK[5][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[6][0], BLOCK[6][1], BLOCK[6][2]))

    glTranslated(0.0, 0.0, -3.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[6][0], BLOCK[6][1], BLOCK[6][2]))

    glTranslated(0.0, -0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[5][0], BLOCK[5][1], BLOCK[5][2]))

    glTranslated(0.0, -0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[4][0], BLOCK[4][1], BLOCK[4][2]))

    glTranslated(0.0, -0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -5.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[4][0], BLOCK[4][1], BLOCK[4][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[5][0], BLOCK[5][1], BLOCK[5][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[6][0], BLOCK[6][1], BLOCK[6][2]))

    glTranslated(0.0, 0.0, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[6][0], BLOCK[6][1], BLOCK[6][2]))

    glTranslated(0.0, 0.0, -3.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[6][0], BLOCK[6][1], BLOCK[6][2]))

    glTranslated(0.0, -0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[5][0], BLOCK[5][1], BLOCK[5][2]))

    glTranslated(0.0, -0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[4][0], BLOCK[4][1], BLOCK[4][2]))

    glTranslated(0.0, -0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 3.0, -10.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[3][0], BLOCK[3][1], BLOCK[3][2]))

    glTranslated(0.0, 0.0, -1.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, YELLOW)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.0, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, -3.0, -10.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[0][0], BLOCK[0][1], BLOCK[0][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[4][0], BLOCK[4][1], BLOCK[4][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[5][0], BLOCK[5][1], BLOCK[5][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[6][0], BLOCK[6][1], BLOCK[6][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[7][0], BLOCK[7][1], BLOCK[7][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[8][0], BLOCK[8][1], BLOCK[8][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[9][0], BLOCK[9][1], BLOCK[9][2]))

    glTranslated(0.0, 0.5, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[10][0], BLOCK[10][1], BLOCK[10][2]))

    glTranslated(0.0, 0.0, -1.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(BLOCK[10][0], BLOCK[10][1], BLOCK[10][2]))

    glTranslated(0.0, -3.5, 189)
    glTranslated(0.0, 0.25, -28.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[0][0], PIPE[0][1], PIPE[0][2]))
    glTranslated(0.0, 1.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[1][0], PIPE[1][1], PIPE[1][2]))

    glTranslated(0.0, -0.50, -10)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[2][0], PIPE[2][1], PIPE[2][2]))
    glTranslated(0.0, 1.5, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[1][0], PIPE[1][1], PIPE[1][2]))

    glTranslated(0.0, -1.0, -8.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[3][0], PIPE[3][1], PIPE[3][2]))
    glTranslated(0.0, 2.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[1][0], PIPE[1][1], PIPE[1][2]))

    glTranslated(0.0, -2.0, -10.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[3][0], PIPE[3][1], PIPE[3][2]))
    glTranslated(0.0, 2.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[1][0], PIPE[1][1], PIPE[1][2]))

    glTranslated(0.0, -3.0, -107)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[0][0], PIPE[0][1], PIPE[0][2]))
    glTranslated(0.0, 1.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[1][0], PIPE[1][1], PIPE[1][2]))

    glTranslated(0.0, -1.0, -16)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[0][0], PIPE[0][1], PIPE[0][2]))
    glTranslated(0.0, 1.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(PIPE[1][0], PIPE[1][1], PIPE[1][2]))

    glTranslated(0.0, -1.5, -18.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(GOAL[0][0], GOAL[0][1], GOAL[0][2]))

    glTranslated(0.0, 5.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRAY)
    create_Box(vertex_box(GOAL[1][0], GOAL[1][1], GOAL[1][2]))

    glTranslated(0.0, 4.5, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN)
    create_Box(vertex_box(GOAL[2][0], GOAL[2][1], GOAL[2][2]))

    glTranslated(0.0, -8.5, -6.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(GOAL[3][0], GOAL[3][1], GOAL[3][2]))

    glTranslated(0.0, 2.5, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BROWN)
    create_Box(vertex_box(GOAL[4][0], GOAL[4][1], GOAL[4][2]))

def set_view(w, h):
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(34.0, w/h, 1.0, 100.0)
    glMatrixMode(GL_MODELVIEW)

def resize(window, w, h):
    # for iconify on Windows
    if h==0:
        return
    glViewport(0, 0, w, h)
    set_view(w, h)

def init():
    gray = 1.0
    glClearColor(0, 0.623, 1.0, 1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    set_view(W_INIT, H_INIT)
    display()   # necessary only on Windows

def window_refresh(window):
    display()

def keyboard(window, key, scancode, action, mods):
    global DeltaMove, JUMPING, sy, sz, MODE
    if (action == glfw.PRESS or action == glfw.REPEAT):
        if key  == glfw.KEY_UP and MODE == "Subjective":
            DeltaMove = 1.0
        if key ==  glfw.KEY_DOWN and MODE == "Subjective":
            DeltaMove = -1.0
        if key  == glfw.KEY_RIGHT and MODE == "Objective":
            DeltaMove = 1.0
        if key ==  glfw.KEY_LEFT and MODE == "Objective":
            DeltaMove = -1.0
    elif action == glfw.RELEASE:
            DeltaMove = 0

    if action == glfw.PRESS:
        if key == glfw.KEY_Z and MODE == 'Subjective':
            MODE = 'Objective'
        elif key == glfw.KEY_Z and MODE == 'Objective':
            MODE = 'Subjective'

    if key  == glfw.KEY_SPACE:
        if(action == glfw.PRESS or action == glfw.REPEAT) and JUMPING == False:
            JUMPING = True
            for i in range(0, 7):
                #time.sleep(0.01)
                sy -= 0.75
                display()
            for i in range(0, 7.0):
                #time.sleep(0.01)
                sy += 0.75
                display()

        else:
            JUMPING = False
    else:
        JUMPING = False

    display()


DeltaMove = 0

if not glfw.init():
    raise RuntimeError('Could not initialize GLFW3')

window = glfw.create_window(W_INIT, H_INIT, "06", None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_window_size_callback(window, resize)
glfw.set_window_refresh_callback(window, window_refresh)
glfw.set_key_callback(window, keyboard)
glfw.make_context_current(window)

init()

while not glfw.window_should_close(window):
    glfw.wait_events()

glfw.terminate()
