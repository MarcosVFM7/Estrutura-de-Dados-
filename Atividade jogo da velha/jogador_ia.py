# -*- coding: utf-8 -*-
from random import randint
from jogador import Jogador
from tabuleiro import Tabuleiro

class JogadorIA(Jogador):
    def __init__(self, tabuleiro: Tabuleiro, tipo: int):
        super().__init__(tabuleiro, tipo)
        self.oponente = Tabuleiro.JOGADOR_0 if tipo == Tabuleiro.JOGADOR_X else Tabuleiro.JOGADOR_X

    def getJogada(self) -> (int, int):
        
        def primeira_regra(jogador):
            for i in range(3):
                
                if self.matriz[i].count(jogador) == 2 and Tabuleiro.DESCONHECIDO in self.matriz[i]:
                    return (i, self.matriz[i].index(Tabuleiro.DESCONHECIDO))
                
                coluna = [self.matriz[x][i] for x in range(3)]
                if coluna.count(jogador) == 2 and Tabuleiro.DESCONHECIDO in coluna:
                    return (coluna.index(Tabuleiro.DESCONHECIDO), i)
            
            diagonal1 = [self.matriz[x][x] for x in range(3)]
            diagonal2 = [self.matriz[x][2 - x] for x in range(3)]
            if diagonal1.count(jogador) == 2 and Tabuleiro.DESCONHECIDO in diagonal1:
                return (diagonal1.index(Tabuleiro.DESCONHECIDO), diagonal1.index(Tabuleiro.DESCONHECIDO))
            if diagonal2.count(jogador) == 2 and Tabuleiro.DESCONHECIDO in diagonal2:
                idx = diagonal2.index(Tabuleiro.DESCONHECIDO)
                return (idx, 2 - idx)
            return None

        jogada = primeira_regra(self.tipo) 
        if jogada:
            return jogada
        jogada = primeira_regra(self.oponente)  
        if jogada:
            return jogada

        def segunda_regra():
            for l in range(3):
                for c in range(3):
                    if self.matriz[l][c] == Tabuleiro.DESCONHECIDO:
                        self.matriz[l][c] = self.tipo
                        count = sum(
                            primeira_regra(self.tipo) is not None
                            for _ in range(2)
                        )
                        self.matriz[l][c] = Tabuleiro.DESCONHECIDO
                        if count >= 2:
                            return (l, c)
            return None

        jogada = segunda_regra()
        if jogada:
            return jogada

        # Terceira regra:
        if self.matriz[1][1] == Tabuleiro.DESCONHECIDO:
            return (1, 1)

        quarta_regra = [(0, 0, 2, 2), (0, 2, 2, 0), (2, 0, 0, 2), (2, 2, 0, 0)]
        for x1, y1, x2, y2 in quarta_regra:
            if self.matriz[x1][y1] == self.oponente and self.matriz[x2][y2] == Tabuleiro.DESCONHECIDO:
                return (x2, y2)

        # Quinta regra:
        for l, c in [(0, 0), (0, 2), (2, 0), (2, 2)]:
            if self.matriz[l][c] == Tabuleiro.DESCONHECIDO:
                return (l, c)

        # Sexta regra:
        for l in range(3):
            for c in range(3):
                if self.matriz[l][c] == Tabuleiro.DESCONHECIDO:
                    return (l, c)

        return None
