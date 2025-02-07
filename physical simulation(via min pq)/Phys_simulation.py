#TASK: create a plot with physical elements(balls), set the specifir parametres of the elements
# and use them to create a interaction between objects. the main task is to simulate the movement and the
# collision between balls not using the full sorting (because of the time complexity and luck of efficiency)
#
# In this task i used min pq to interact with the nearest collision

# IMPORTANT!
# Before running the code, go to Settings => Python Scientific => turn of the "Show plots on the tool window"

import functools
import math
import random
import warnings
import heapq

import matplotlib.pyplot as plt
import matplotlib.animation as animation

# disable warnings
warnings.filterwarnings("ignore")
# matplotlib configuration
# bounds of the room
x_lim = (0, 30)
y_lim = (0, 20)
# scaler for bigger points in plots
PLT_RADIUS_SCALER = 25

# set up plot to draw animations
fig = plt.figure()
ax = fig.add_subplot(111, autoscale_on=False, xlim=x_lim, ylim=y_lim)
# disable x and y axes labels
ax.set_yticks([])
ax.set_xticks([])


class Particle:
    def __init__(self, rx, ry, vx, vy, radius, mass):
        self._rx = rx
        self._ry = ry
        self._vx = vx
        self._vy = vy
        self._radius = radius
        self._mass = mass
        self._collisions_count = 0

        # scatter plot for drawing point
        self._scatter, = ax.plot([], [], 'o', markersize=self._radius * PLT_RADIUS_SCALER)

    @property
    def rx(self):
        return self._rx

    @property
    def ry(self):
        return self._ry

    @property
    def vx(self):
        return self._vx

    @property
    def vy(self):
        return self._vy

    @vx.setter
    def vx(self, value):
        self._vx = value

    @vy.setter
    def vy(self, value):
        self._vy = value

    @property
    def radius(self):
        return self._radius

    @property
    def mass(self):
        return self._mass

    @property
    def collisions_count(self):
        return self._collisions_count

    @collisions_count.setter
    def collisions_count(self, value):
        self._collisions_count = value

    @property
    def scatter(self):
        return self._scatter

    def move(self, dt):
        new_rx = self._rx + self._vx * dt
        new_ry = self._ry + self._vy * dt
        # перевіряєм, чи не зіштовхнеться куля з гор. стінкою
        if new_rx - self._radius < x_lim[0] or new_rx + self._radius > x_lim[1]:
            self.bounceoff_vert_lim()
        else:
            self._rx = new_rx
        # тут те саме, тільки з вертикальною
        if new_ry - self._radius < y_lim[0] or new_ry + self._radius > y_lim[1]:
            self.bounceoff_horiz_lim()
        else:
            self._ry = new_ry
        # оновлюємо позицію кулі
        self._scatter.set_data([self._rx, self._ry])

    def bounceoff_vert_lim(self):
        self._vx = -self._vx
        self._collisions_count += 1

    def bounceoff_horiz_lim(self):
        self._vy = -self._vy
        self._collisions_count += 1

    def bounce_off(self, that):
        # тут відштовхування саме 2 куль
        dx = that.rx - self.rx
        dy = that.ry - self.ry

        dvx = that.vx - self.vx
        dvy = that.vy - self.vy

        dvdr = dx * dvx + dy * dvy

        dist = self.radius + that.radius

        j = 2 * self.mass * that.mass * dvdr / ((self.mass + that.mass) * dist)

        j_x = j * dx / dist

        j_y = j * dy / dist

        self.vx += j_x / self.mass
        self.vy += j_y / self.mass

        that.vx -= j_x / that.mass
        that.vy -= j_y / that.mass

        self.collisions_count += 1
        that.collisions_count += 1

    def time_to_hit(self, that):
        # показник того, скільки часу лишилось до зіштовхування 2х куль
        if self == that:
            return math.inf

        dx = that.rx - self.rx
        dy = that.ry - self.ry

        dvx = that.vx - self.vx
        dvy = that.vy - self.vy

        dvdr = dx * dvx + dy * dvy

        if dvdr > 0:
            return math.inf

        dvdv = dvx * dvx + dvy * dvy
        drdr = dx * dx + dy * dy

        sigma = self.radius + that.radius

        d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma)

        if d < 0:
            return math.inf
        if dvdv == 0:
            dvdv = 0.0000001
        return -(dvdr + math.sqrt(d)) / dvdv

    # повертаєм значення "час зіштовхнення зі стінкою"  по гориз. і верт. як додаткові івенти
    def time_to_hit_verticalWall(self):
        if self._vx > 0:
            time_to_hit = (30 - self.radius - self.rx) / self.vx
        elif self._vx <= 0:
            time_to_hit = (1 - self.radius - self.rx) / self.vx
        return time_to_hit

    def time_to_hit_horizontalWall(self):
        if self._vy > 0:
            time_to_hit = (20 - self.radius - self.ry) / self.vy
        elif self._vy <= 0:
            time_to_hit = (1 - self.radius - self.ry) / self.vy
        return time_to_hit


class  Collision_detec:

    def __init__(self, time, ball_n, ball_n_plus_1):
        self.time = time  # час, коли певний івент станеться
        self.ball_n = ball_n
        self.ball_n_plus_1 = ball_n_plus_1
        self.count_n = 0 # рахує зіштовхування
        self.count_n_plus_1 = 0  # рахує зіштовхування

    def __lt__(self, other):
        return self.time < other.time

    # перевіряємо, чи подія з черги на момент розгляду лишається актуальною
    def is_valid(self):
        # якщо к-сть зіштовхувань м'яча більша, за передбачену к-сть - подія не актуальна
        if self.ball_n is not None and self.ball_n_plus_1 is not None:
            if self.ball_n.collisions_count != self.count_n or self.ball_n_plus_1.collisions_count != self.count_n_plus_1:
                return False
            else:
                return True
        # якщо передбачено колізії лише для одного з м'ячів, ми перевіряємо ті самі умови, проте лише для нього
        elif self.ball_n is not None:
            if self.ball_n.collisions_count != self.count_n:
                return False
            else:
                return True
        elif self.ball_n_plus_1 is not None:
            if self.ball_n_plus_1.collisions_count != self.count_n_plus_1:
                return False
            else:
                return True


class CollisionSystem:
    def __init__(self, balls):
        self.pq = []
        self.t = 0.0
        self.balls = balls
        self.temp_event = None

    # передбачаємо зіштовхування
    def queue_cast(self, ball_n):
        if ball_n is None:
            return
        # тут ми обчислюємо час зіткнення для м'яча з усіма іншими задопомогою tth
        # і додаєм його в чергу за визначеним пріоритетом
        for i in range(len(self.balls)):
            dt = ball_n.time_to_hit(self.balls[i])
            event_1 = Collision_detec(self.t + dt, ball_n, self.balls[i])
            event_1.countA = ball_n.collisions_count
            event_1.countB = self.balls[i].collisions_count
            # якщо подія близька, додаємо в чергу
            if event_1.time != math.inf:
                heapq.heappush(self.pq, event_1)
        # не забуваємо про зіткнення зі стінками
        event_2 = Collision_detec(self.t + ball_n.time_to_hit_verticalWall(), ball_n, None)
        event_2.countA = ball_n.collisions_count
        event_3 = Collision_detec(self.t + ball_n.time_to_hit_horizontalWall(), None, ball_n)
        event_3.countB = ball_n.collisions_count
        # якщо вони також близькі, то додаємо і їх
        if event_3.time != math.inf and event_2.time != math.inf:
            heapq.heappush(self.pq, event_2)
            heapq.heappush(self.pq, event_3)

        # перебираємо всі комбінації і додаєм в чергу виключно ті, що є найближчими(не мат.інф)
        for i in range(len(self.balls)):
            for j in range(i + 1, len(self.balls)):
                dt = self.balls[i].time_to_hit(self.balls[j])
                event = Collision_detec(self.t + dt, self.balls[i], self.balls[j])
                event.count_n = self.balls[i].collisions_count
                event.count_n_plus_1 = self.balls[j].collisions_count
                if event.time != math.inf:
                    heapq.heappush(self.pq, event)

    def nearest(self):
        # вилучаємо останній(насправді ж перший) пріоритетний елемент з черги
        # це будуть 2 кулі, що зіштовхнуться найближчим часом першиим
        for i in range(len(self. balls)):
            self.queue_cast(self. balls[i])
        self.event = heapq.heappop(self.pq)

    def simulate(self):
        # оголошуємо подію для 2 куль
        ball_n = self.event.ball_n
        ball_n_plus_1 = self.event.ball_n_plus_1
        # рухаємо кулі, допоки не настане час події
        for i in range(len(self. balls)):
            self. balls[i].move(self.event.time - self.t)
        self.t = self.event.time
        # тут обираємо дію по ситуації, так би мовити.
        if ball_n is not None and ball_n_plus_1 is not None:
            ball_n.bounce_off(ball_n_plus_1)
        elif ball_n is not None and ball_n_plus_1 is None:
            ball_n.bounceoff_vert_lim()
        elif ball_n is None and ball_n_plus_1 is not None:
            ball_n_plus_1.bounceoff_horiz_lim()
        # усуваємо колізію!
        else:
            pass
        # оновлюємо інформацію про зіткнення для наших точок
        self.queue_cast(ball_n)
        self.queue_cast(ball_n_plus_1)
        # обираємо нову найближчу подію(нові кульки, що скоро зіштовхнуться)
        while self.pq:
           self.event = heapq.heappop(self.pq)
           # якщо подія актуальна - починаємо цикл знову. інакше перебираємо найпріоритетніші події
           # через heappop() допоки не знайдем найближчу актуальну
           if self.event.is_valid():
               break

    def next_event(self):
        # переходимо до нової події
        if self.t > self.event.time:
            self.simulate()


# this function moves all objects passing delta time, returns
# scatter plot of points that should be drawn
# the last parameter is time in seconds, it goes from matplotlib animator

def animate(objects, dt, _t):
    # рухаємо всі кульки
    for obj in objects:
        obj.move(dt)
    # постійно оновлюємо час
    collision.t += dt
    # переходимо до simulate, що знаходить й усуває найближчу колізію
    collision.next_event()
    # оновлюємо
    return [obj.scatter for obj in objects]


if __name__ == "__main__":
    # 10 milliseconds delta t
    dt = 1
    num = 10
    balls = []

    for i in range( num):
        radius = (random.random() + 0.7)
        x = (random.randint(1, 25)+radius)
        y = (random.randint(1, 15)+radius)
        vx = random.randint(1, 20)
        vy = random.randint(1, 20)
        mass = random.random()
        print(f"Creating a new Particle({x}, {y}, {vx}, {vy}, {radius}, {mass})")
        balls.append(Particle(x, y, vx, vy, radius, mass))
    collision = CollisionSystem(balls)
    collision.nearest()
    ani = animation.FuncAnimation(
        fig, functools.partial(animate, balls,  dt / 1_000), interval= dt, blit=True, save_count=100,
    )

    plt.show()








