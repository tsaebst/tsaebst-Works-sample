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
