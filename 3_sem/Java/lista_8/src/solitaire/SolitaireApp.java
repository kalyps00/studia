package solitaire;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class SolitaireApp extends JFrame {
    private GameState gameState;
    private BoardPanel boardPanel;
    private JLabel statusLabel;
    
    private JRadioButtonMenuItem britishItem;
    private JRadioButtonMenuItem europeanItem;

    public SolitaireApp() {
        super("Samotnik");
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        setSize(600, 650);
        setLocationRelativeTo(null);
        loadState();
        if (gameState == null) {
            gameState = new GameState(GameState.BoardType.BRITISH);
        }
        boardPanel = new BoardPanel(gameState);
        statusLabel = new JLabel("Witaj w grze Samotnik!");
        statusLabel.setHorizontalAlignment(SwingConstants.CENTER);
        statusLabel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

        add(boardPanel, BorderLayout.CENTER);
        add(statusLabel, BorderLayout.SOUTH);

        createMenu();

        boardPanel.addPropertyChangeListener("moveMade", evt -> checkGameStatus());

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                exitGame();
            }
        });
        
        checkGameStatus(); 
    }

    private void createMenu() {
        JMenuBar menuBar = new JMenuBar();

        JMenu gameMenu = new JMenu("Gra");
        gameMenu.setMnemonic(KeyEvent.VK_G);

        JMenuItem newItem = new JMenuItem("Nowa", KeyEvent.VK_N);
        newItem.addActionListener(e -> newGame());
        gameMenu.add(newItem);

        gameMenu.addSeparator();

        JMenuItem exitItem = new JMenuItem("Koniec", KeyEvent.VK_K);
        exitItem.addActionListener(e -> exitGame());
        gameMenu.add(exitItem);

        menuBar.add(gameMenu);

        JMenu movesMenu = new JMenu("Ruchy");
        
        JMenuItem selectItem = new JMenuItem("Zaznacz");
        selectItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_SPACE, 0));
        selectItem.addActionListener(e -> boardPanel.toggleSelection());
        movesMenu.add(selectItem);
        
        movesMenu.addSeparator();
        
        JMenuItem upItem = new JMenuItem("Skok w górę");
        upItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_UP, InputEvent.CTRL_DOWN_MASK));
        upItem.addActionListener(e -> boardPanel.moveSelected(-1, 0));
        movesMenu.add(upItem);

        JMenuItem downItem = new JMenuItem("Skok w dół");
        downItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_DOWN, InputEvent.CTRL_DOWN_MASK));
        downItem.addActionListener(e -> boardPanel.moveSelected(1, 0));
        movesMenu.add(downItem);

        JMenuItem leftItem = new JMenuItem("Skok w lewo");
        leftItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, InputEvent.CTRL_DOWN_MASK));
        leftItem.addActionListener(e -> boardPanel.moveSelected(0, -1));
        movesMenu.add(leftItem);

        JMenuItem rightItem = new JMenuItem("Skok w prawo");
        rightItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, InputEvent.CTRL_DOWN_MASK));
        rightItem.addActionListener(e -> boardPanel.moveSelected(0, 1));
        movesMenu.add(rightItem);

        menuBar.add(movesMenu);

        JMenu settingsMenu = new JMenu("Ustawienia");
        ButtonGroup typeGroup = new ButtonGroup();
        britishItem = new JRadioButtonMenuItem("Plansza Brytyjska");
        europeanItem = new JRadioButtonMenuItem("Plansza Europejska");
        
        if (gameState.getType() == GameState.BoardType.BRITISH) britishItem.setSelected(true);
        else europeanItem.setSelected(true);
        
        britishItem.addActionListener(e -> {
            gameState.setType(GameState.BoardType.BRITISH);
            newGame();
        });
        europeanItem.addActionListener(e -> {
            gameState.setType(GameState.BoardType.EUROPEAN);
            newGame();
        });

        typeGroup.add(britishItem);
        typeGroup.add(europeanItem);
        settingsMenu.add(britishItem);
        settingsMenu.add(europeanItem);
        
        settingsMenu.addSeparator();

        JMenuItem boardColorItem = new JMenuItem("Kolor planszy...");
        boardColorItem.addActionListener(e -> {
            Color c = JColorChooser.showDialog(this, "Wybierz kolor planszy", Color.ORANGE);
            if (c != null) boardPanel.setBoardColor(c);
        });
        settingsMenu.add(boardColorItem);

        JMenuItem pegColorItem = new JMenuItem("Kolor pionów...");
        pegColorItem.addActionListener(e -> {
            Color c = JColorChooser.showDialog(this, "Wybierz kolor pionów", Color.BLACK);
            if (c != null) boardPanel.setPegColor(c);
        });
        settingsMenu.add(pegColorItem);

        JCheckBoxMenuItem filledItem = new JCheckBoxMenuItem("Wypełnione piony", true);
        filledItem.addActionListener(e -> boardPanel.setFilledPegs(filledItem.isSelected()));
        settingsMenu.add(filledItem);

        menuBar.add(settingsMenu);

        menuBar.add(Box.createHorizontalGlue()); 
        JMenu helpMenu = new JMenu("Pomoc");

        JMenuItem aboutGameItem = new JMenuItem("O grze");
        aboutGameItem.addActionListener(e -> showAboutGame());
        helpMenu.add(aboutGameItem);

        JMenuItem aboutAppItem = new JMenuItem("O aplikacji");
        aboutAppItem.addActionListener(e -> showAboutApp());
        helpMenu.add(aboutAppItem);

        menuBar.add(helpMenu);

        setJMenuBar(menuBar);
    }

    private void newGame() {
        GameState.BoardType type = britishItem.isSelected() ? GameState.BoardType.BRITISH : GameState.BoardType.EUROPEAN;
        gameState.setType(type);
        gameState.reset();
        boardPanel.setGameState(gameState);
        checkGameStatus();
        repaint();
    }

    private void checkGameStatus() {
        if (gameState.isGameOver()) {
            if (gameState.isWin()) {
                statusLabel.setText("GRATULACJE! Wygrałeś! (1 pion na środku)");
            } else {
                statusLabel.setText("KONIEC GRY. Pozostało pionów: " + gameState.countPegs());
            }
            britishItem.setEnabled(true);
            europeanItem.setEnabled(true);
        } else {
            statusLabel.setText("Gra w toku... Piony: " + gameState.countPegs());

            britishItem.setEnabled(false);
            europeanItem.setEnabled(false);
        }
    }

    private void exitGame() {
        if (gameState.isActive()) {
            saveState();
        }
        System.exit(0);
    }

    private void saveState() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("solitaire.ser"))) {
            oos.writeObject(gameState);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void loadState() {
        File f = new File("solitaire.ser");
        if (f.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(f))) {
                gameState = (GameState) ois.readObject();
                f.delete(); 
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }

    private void showAboutGame() {
        JOptionPane.showMessageDialog(this,
            "Samotnik to gra logiczna dla jednej osoby.\n" +
            "Celem gry jest pozostawienie na planszy tylko jednego piona,\n" +
            "Ruch polega na przeskoczeniu pionem sąsiedniego piona na puste pole.\n" +
            "Zbity pion jest usuwany z planszy.",
            "O grze", JOptionPane.INFORMATION_MESSAGE);
    }

    private void showAboutApp() {
        JOptionPane.showMessageDialog(this,
            "Samotnik v1.0\n" +
            "Autor: Kamil Pawlikowski\n" +
            "Data: Grudzień 2025",
            "O aplikacji", JOptionPane.INFORMATION_MESSAGE);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new SolitaireApp().setVisible(true);
        });
    }
}
