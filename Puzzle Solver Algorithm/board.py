class Board:
    def __init__(self, dimension, blocks):
        self._dimension = dimension
        self._blocks = blocks

    def dimension(self):
        return self._dimension

    def hamming(self) -> int:
        # геммінгтонова дистанція(скільки блоків не на своєму місці)
        count = []
        for i in range(self._dimension):
            for j in range(self._dimension):
                # print(self._blocks[i][j])
                # print(i+j+1)
                if self._blocks[i][j] != i+j+1 and self._blocks[i][j] != 0:
                    count.append(self._blocks[i][j])
        print("Hamming dist:", len(count))
        return count

    def manhattan(self):
        # менгеттенівська відстань(найкоротший шлях для вершин не на своїй позиції до вершини,що розглядається як їх
        # позиція)
        count = self.hamming()
        for i in range(self._dimension):
            for j in range(self._dimension):
                if self._blocks[i][j] != i + j + 1:
                    dist = self.min_moves_to_match(i, j)
                    count += dist
        # -1, бо не враховуємо перевірку позиції пустої ячейки
        print("Mahhattan dist:", count - 1)
        return count

    def min_moves_to_match(self, i: int, j: int) -> int:
        element = self._blocks[i][j]
        target_i = (element - 1) // self._dimension
        target_j = (element - 1) % self._dimension

        return abs(i - target_i) + abs(j - target_j)


    def is_goal(self):
        # Перевірка: чи ця дошка є метою/рішенням
        goal = 1
        for i in range(self._dimension):
            for j in range(self._dimension):
                if i == self._dimension - 1 and j == self._dimension - 1:
                    if self._blocks[i][j] != 0:
                        return False
                elif self._blocks[i][j] != goal:
                    return False
                goal += 1
        return True

    def __eq__(self, other):
        # еревірка: чи ця дошка дорівнює іншій
        if self._dimension != other.dimension():
            return False
        for i in range(self._dimension):
            for j in range(self._dimension):
                if self._blocks[i][j] != other._blocks[i][j]:
                    return False
        return True

    def neighbors(self):
        # Створення списку сусідніх плат
        neighbors = []
        empty_row, empty_col = self.find_empty()
        moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # праворуч, ліворуч, вниз, вгору
        for move in moves:
            new_row = empty_row + move[0]
            new_col = empty_col + move[1]
            if 0 <= new_row < self._dimension and 0 <= new_col < self._dimension:
                new_blocks = [row[:] for row in self._blocks]  # Створення глибокої копії блоків
                new_blocks[empty_row][empty_col] = new_blocks[new_row][new_col]
                new_blocks[new_row][new_col] = 0
                neighbor = Board(self._dimension, new_blocks)
                neighbors.append(neighbor)
        return neighbors

    def find_empty(self):
        # Пошук позиції порожнього блоку (нуль)
        for i in range(self._dimension):
            for j in range(self._dimension):
                if self._blocks[i][j] == 0:
                    return i, j

    def inversions(self):
        # Підрахунок кількості інверсій на дошці
        count = 0
        flattened = [num for row in self._blocks for num in row if num != 0]
        for i in range(len(flattened)):
            for j in range(i + 1, len(flattened)):
                if flattened[j] < flattened[i]:
                    count += 1
        return count

    def __str__(self):
        # Рядкове представлення дошки
        string = ""
        for i in range(self._dimension):
            for j in range(self._dimension):
                string += f"{self._blocks[i][j]:2d} "
            string += "\n"
        return string

    def __hash__(self):
        # Хеш-функція для об’єктів дошки
        return hash(tuple(map(tuple, self._blocks)))
