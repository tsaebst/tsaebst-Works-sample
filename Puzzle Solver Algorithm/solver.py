from practices.practice5.markeer.board import Board


class Solver:
    def __init__(self, board):
        self._initial_board = board

    def is_solvable(self) -> bool:
        flatten_blocks = [element for row in self._initial_board._blocks for element in row]
        inversion_count = 0

        for i in range(len(flatten_blocks)):
            for j in range(i + 1, len(flatten_blocks)):
                if flatten_blocks[i] != 0 and flatten_blocks[j] != 0 and flatten_blocks[i] > flatten_blocks[j]:
                    inversion_count += 1

        dimension_even = self._initial_board._dimension % 2 == 0
        inversion_even = (inversion_count-1) % 2 == 0

        return dimension_even == inversion_even

    def min_moves_to_solve(self) -> int:
        if not self.is_solvable():
            return -1

        priority_queue = MinPQ()
        priority_queue.insert(self._initial_board, 0)

        distance_to = {}
        distance_to[self._initial_board] = 0

        while not priority_queue.is_empty():
            current_board = priority_queue.delete_min()

            if current_board.is_goal():
                return distance_to[current_board]

            for neighbor in current_board.neighbors():
                if neighbor not in distance_to:
                    distance_to[neighbor] = distance_to[current_board] + 1
                    priority_queue.insert(neighbor, distance_to[neighbor])

        return -1

    def solution(self) -> list:
        # список послідовності дошок для найшвидшого розв'язку (або -1, якщо рішення нема)
        if not self.is_solvable():
            return -1

        priority_queue = MinPQ()
        priority_queue.insert(self._initial_board, 0)

        distance_to = {}
        distance_to[self._initial_board] = 0

        edge_to = {}
        edge_to[self._initial_board] = None

        while not priority_queue.is_empty():
            current_board = priority_queue.delete_min()

            if current_board.is_goal():
                break

            for neighbor in current_board.neighbors():
                if neighbor not in distance_to:
                    distance_to[neighbor] = distance_to[current_board] + 1
                    priority_queue.insert(neighbor, distance_to[neighbor])
                    edge_to[neighbor] = current_board

        solution_boards = []
        while current_board is not None:
            solution_boards.append(current_board)
            current_board = edge_to[current_board]

        solution_boards.reverse()
        return solution_boards


class MinPQ:
    # прописуєм логіку розставлення елементів в черзі
    def __init__(self):
        # ліст з чергою
        self._pq = []
        self._size = 0

    def is_empty(self):
        return self._size == 0

    def size(self):
        return self._size

    def insert(self, board, priority):
        # додаємо вершину в дерево, збільшуємо його розмір
        self._pq.append((board, priority))
        self._size += 1
        # підіймаємо її за потреби(якщо вона має вищу пріоритетність)
        self._swim(self._size)

    def delete_min(self):
        # зменшуємо чергу видаляючи найнижчий за пріоритетністю елемент і
        # занурюємо той, що перед ним на його місце
        # ну і черга зменшується на 1 позицію
        if self._size == 0:
            raise IndexError("Priority queue underflow")
        self._exchange(1, self._size)
        board, _ = self._pq.pop()
        self._size -= 1
        # занурюємо передостанню вершину нижче по дереву
        self._sink(1)
        return board

    def _swim(self, k):
        # допоки батько має меншу пріоритетність за нащадка - міняємо їх місцями
        while k > 1 and self._greater(k // 2, k):
            self._exchange(k, k // 2)
            k = k // 2

    def _sink(self, k):
        while 2 * k <= self._size:
            j = 2 * k
            if j < self._size and self._greater(j, j + 1):
                j += 1
            if not self._greater(k, j):
                break
            self._exchange(k, j)
            k = j

    def _greater(self, i, j):
        # порівнюємо, хто з двох елементів є пріоритетнішим
        _, priority_i = self._pq[i - 1]
        _, priority_j = self._pq[j - 1]
        return priority_i > priority_j

    def _exchange(self, i, j):
        # міняємо місцями елементи
        self._pq[i - 1], self._pq[j - 1] = self._pq[j - 1], self._pq[i - 1]


def read_data_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        dimension = int(lines[0])
        matrix = []

        for line in lines[1:]:
            row = [int(num) for num in line.split()]
            matrix.append(row)

        return Board(dimension, matrix)


def main():
    filename = "puzzle31.txt"
    board = read_data_from_file(filename)
    solver = Solver(board)
    print(board)
    if not solver.is_solvable():
        print("Board does not have solutions")
    else:
        print(f"Minimal number of steps {solver.min_moves_to_solve()}")

        for board in solver.solution():
            if board.is_goal():
                print("Результат виконанн програми:")
                print(board)


if __name__ == "__main__":
    main()
