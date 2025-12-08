package solitaire;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class BoardPanel extends JPanel {
    private GameState gameState;
    private int selectedR = -1;
    private int selectedC = -1;
    private int cursorR = 3;
    private int cursorC = 3;
    
    private Color boardColor = new Color(255, 204, 153);
    private Color pegColor = Color.BLACK;
    private boolean filledPegs = true;

    public BoardPanel(GameState gameState) {
        this.gameState = gameState;
        setFocusable(true);
        
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (!gameState.isActive()) return;
                requestFocusInWindow();
                
                int w = getWidth();
                int h = getHeight();
                int cellSize = Math.min(w, h) / 7;
                int offsetX = (w - cellSize * 7) / 2;
                int offsetY = (h - cellSize * 7) / 2;

                int c = (e.getX() - offsetX) / cellSize;
                int r = (e.getY() - offsetY) / cellSize;

                if (r >= 0 && r < 7 && c >= 0 && c < 7) {
                    cursorR = r;
                    cursorC = c;
                    handleInput(r, c);
                    repaint();
                }
            }
        });

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (!gameState.isActive()) return;
                
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_UP:
                        moveCursor(-1, 0);
                        break;
                    case KeyEvent.VK_DOWN:
                        moveCursor(1, 0);
                        break;
                    case KeyEvent.VK_LEFT:
                        moveCursor(0, -1);
                        break;
                    case KeyEvent.VK_RIGHT:
                        moveCursor(0, 1);
                        break;
                    case KeyEvent.VK_SPACE:
                    case KeyEvent.VK_ENTER:
                        handleInput(cursorR, cursorC);
                        repaint();
                        break;
                }
            }
        });
    }

    private void moveCursor(int dr, int dc) {
        int newR = cursorR + dr;
        int newC = cursorC + dc;
        if (newR >= 0 && newR < 7 && newC >= 0 && newC < 7) {
            cursorR = newR;
            cursorC = newC;
            repaint();
        }
    }

    public void setGameState(GameState gameState) {
        this.gameState = gameState;
        selectedR = -1;
        selectedC = -1;
        cursorR = 3;
        cursorC = 3;
        repaint();
    }

    public void handleInput(int r, int c) {
        if (gameState.get(r, c) == GameState.PEG) {
            selectedR = r;
            selectedC = c;
            repaint();
        } else if (gameState.get(r, c) == GameState.EMPTY) {
            if (selectedR != -1 && selectedC != -1) {
                if (gameState.isValidMove(selectedR, selectedC, r, c)) {
                    gameState.move(selectedR, selectedC, r, c);
                    selectedR = -1;
                    selectedC = -1;
                    repaint();
                    firePropertyChange("moveMade", false, true);
                }
            }
        }
    }
    
    public void moveSelected(int dr, int dc) {
        if (selectedR == -1) return;
        int newR = selectedR + dr * 2;
        int newC = selectedC + dc * 2;
        
        if (newR >= 0 && newR < 7 && newC >= 0 && newC < 7) {
             if (gameState.isValidMove(selectedR, selectedC, newR, newC)) {
                gameState.move(selectedR, selectedC, newR, newC);
                selectedR = -1; 
                selectedR = -1;
                selectedC = -1;
                repaint();
                firePropertyChange("moveMade", false, true);
            }
        }
    }
    public void toggleSelection() {
        if (!gameState.isActive()) return;
        handleInput(cursorR, cursorC);
        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(boardColor);
        g.fillRect(0, 0, getWidth(), getHeight());

        int w = getWidth();
        int h = getHeight();
        int cellSize = Math.min(w, h) / 7;
        int offsetX = (w - cellSize * 7) / 2;
        int offsetY = (h - cellSize * 7) / 2;

        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 7; c++) {
                int val = gameState.get(r, c);
                if (val == GameState.OUT) continue;

                int x = offsetX + c * cellSize;
                int y = offsetY + r * cellSize;
                
                g.setColor(Color.DARK_GRAY);
                g.fillOval(x + 5, y + 5, cellSize - 10, cellSize - 10);

                if (val == GameState.PEG) {
                    g.setColor(pegColor);
                    if (filledPegs) {
                        g.fillOval(x + 8, y + 8, cellSize - 16, cellSize - 16);
                    } else {
                        g.drawOval(x + 8, y + 8, cellSize - 16, cellSize - 16);
                        ((Graphics2D)g).setStroke(new BasicStroke(2));
                        g.drawOval(x + 8, y + 8, cellSize - 16, cellSize - 16);
                        ((Graphics2D)g).setStroke(new BasicStroke(1));
                    }
                    
                    if (r == selectedR && c == selectedC) {
                        g.setColor(Color.RED);
                        ((Graphics2D)g).setStroke(new BasicStroke(3));
                        g.drawOval(x + 8, y + 8, cellSize - 16, cellSize - 16);
                        ((Graphics2D)g).setStroke(new BasicStroke(1));
                    }
                }
                if (r == cursorR && c == cursorC && gameState.isActive()) {
                    g.setColor(Color.BLUE);
                    g.drawRect(x + 2, y + 2, cellSize - 4, cellSize - 4);
                }
            }
        }
    }

    public void setBoardColor(Color boardColor) {
        this.boardColor = boardColor;
        repaint();
    }

    public void setPegColor(Color pegColor) {
        this.pegColor = pegColor;
        repaint();
    }

    public void setFilledPegs(boolean filledPegs) {
        this.filledPegs = filledPegs;
        repaint();
    }
    
    public boolean hasSelection() {
        return selectedR != -1;
    }
}
