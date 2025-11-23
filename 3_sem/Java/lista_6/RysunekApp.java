package lista_6;

import java.awt.*;
import java.awt.event.*;

public class RysunekApp extends Frame {
    private Powierzchnia powierzchnia;

    public RysunekApp() {
        super("Kolorowy Rysunek");
        setSize(800, 600);
        setLayout(new BorderLayout());

        powierzchnia = new Powierzchnia();
        add(powierzchnia, BorderLayout.CENTER);

        Panel panelKolorow = new Panel();
        panelKolorow.setLayout(new GridLayout(0, 1));

        CheckboxGroup grupaKolorow = new CheckboxGroup();
        Checkbox czerwony = new Checkbox("Czerwony", grupaKolorow, false);
        Checkbox zielony = new Checkbox("Zielony", grupaKolorow, false);
        Checkbox niebieski = new Checkbox("Niebieski", grupaKolorow, false);
        Checkbox czarny = new Checkbox("Czarny", grupaKolorow, true);

        czerwony.addItemListener(e -> powierzchnia.setAktualnyKolor(Color.RED));
        zielony.addItemListener(e -> powierzchnia.setAktualnyKolor(Color.GREEN));
        niebieski.addItemListener(e -> powierzchnia.setAktualnyKolor(Color.BLUE));
        czarny.addItemListener(e -> powierzchnia.setAktualnyKolor(Color.BLACK));

        panelKolorow.add(czerwony);
        panelKolorow.add(zielony);
        panelKolorow.add(niebieski);
        panelKolorow.add(czarny);

        add(panelKolorow, BorderLayout.EAST);

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_BACK_SPACE -> powierzchnia.usunWszystkieKreski();
                    case KeyEvent.VK_F -> powierzchnia.usunPierwszaKreske();
                    case KeyEvent.VK_B, KeyEvent.VK_L -> powierzchnia.usunOstatniaKreske();
                }
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowOpened(WindowEvent e) {
                requestFocus();
            }

            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

        setFocusable(true);
        requestFocusInWindow(); 
    }

    public static void main(String[] args) {
        RysunekApp app = new RysunekApp();
        app.setVisible(true);
    }
}