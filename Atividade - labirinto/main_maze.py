# -*- coding: utf-8 -*-
import time
from maze import Maze
from collections import deque

def solve_maze(maze):
    stack = deque()
    start_pos = maze.get_init_pos_player()
    stack.append(start_pos)

    while stack:
        current_pos = stack.pop()

        if maze.find_prize(current_pos):
            print("Caminho encontrado!")
            return True

        maze.mov_player(current_pos)

        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        for direction in directions:
            next_pos = (current_pos[0] + direction[0], current_pos[1] + direction[1])

            if maze.is_free(next_pos):
                stack.append(next_pos)

    print("Não encontrou o caminho.")
    return False

maze_csv_path = "labirinto1.txt"
maze = Maze()
maze.load_from_csv(maze_csv_path)

maze.run()
maze.init_player()

solve_maze(maze)
