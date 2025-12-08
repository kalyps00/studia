package solitaire;

import java.io.Serializable;

public class GameState implements Serializable {
    private static final long serialVersionUID = 1L;

    public enum BoardType {
        BRITISH, EUROPEAN
    }

    public static final int OUT = 0;
    public static final int EMPTY = 1;
    public static final int PEG = 2;

    private int[][] board;
    private BoardType type;
    private boolean active;

    public GameState(BoardType type) {
        this.type = type;
        reset();
    }

    public void reset() {
        board = new int[7][7];
        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 7; c++) {
                board[r][c] = OUT;
            }
        }

        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 7; c++) {
                boolean valid = false;
                if (r >= 2 && r <= 4) valid = true;
                if (c >= 2 && c <= 4) valid = true;
                
                if (valid) {
                    board[r][c] = PEG;
                }
            }
        }

        if (type == BoardType.EUROPEAN) {
            board[1][1] = PEG;
            board[1][5] = PEG;
            board[5][1] = PEG;
            board[5][5] = PEG;
        }
        board[3][3] = EMPTY;
        active = true;
    }

    public int get(int r, int c) {
        if (r < 0 || r >= 7 || c < 0 || c >= 7) return OUT;
        return board[r][c];
    }

    public boolean isValidMove(int r1, int c1, int r2, int c2) {
        if (!active) return false;
        if (get(r1, c1) != PEG) return false;
        if (get(r2, c2) != EMPTY) return false;

        int dr = Math.abs(r2 - r1);
        int dc = Math.abs(c2 - c1);

        if (!((dr == 2 && dc == 0) || (dr == 0 && dc == 2))) {
            return false;
        }

        int mr = (r1 + r2) / 2;
        int mc = (c1 + c2) / 2;
        
        return get(mr, mc) == PEG;
    }

    public void move(int r1, int c1, int r2, int c2) {
        if (isValidMove(r1, c1, r2, c2)) {
            board[r1][c1] = EMPTY;
            board[r2][c2] = PEG;
            int mr = (r1 + r2) / 2;
            int mc = (c1 + c2) / 2;
            board[mr][mc] = EMPTY;
        }
    }

    public boolean isGameOver() {
        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 7; c++) {
                if (board[r][c] == PEG) {
                    if (isValidMove(r, c, r+2, c)) return false;
                    if (isValidMove(r, c, r-2, c)) return false;
                    if (isValidMove(r, c, r, c+2)) return false;
                    if (isValidMove(r, c, r, c-2)) return false;
                }
            }
        }
        active = false;
        return true;
    }

    public int countPegs() {
        int count = 0;
        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 7; c++) {
                if (board[r][c] == PEG) count++;
            }
        }
        return count;
    }

    public boolean isWin() {
        return countPegs() == 1 && board[3][3] == PEG;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public BoardType getType() {
        return type;
    }
    
    public void setType(BoardType type) {
        this.type = type;
    }
}
