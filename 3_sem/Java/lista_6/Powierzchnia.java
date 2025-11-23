package lista_6;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class Powierzchnia extends Canvas {
    private ArrayList<Kreska> kreski;
    private Point poczatek;
    private Point dynamicznyKoniec; 
    private Color aktualnyKolor;

    public Powierzchnia() {
        kreski = new ArrayList<>();
        aktualnyKolor = Color.BLACK;

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                poczatek = e.getPoint();
                dynamicznyKoniec = null; 
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                Point koniec = e.getPoint();
                if (poczatek != null) {
                    kreski.add(new Kreska(poczatek, koniec, aktualnyKolor));
                    poczatek = null;
                    dynamicznyKoniec = null; 
                    repaint();
                }
            }

            @Override
            public void mouseClicked(MouseEvent e) {
                getParent().requestFocus(); 
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                dynamicznyKoniec = e.getPoint(); 
                repaint();
            }
        });
    }

    public void setAktualnyKolor(Color kolor) {
        this.aktualnyKolor = kolor;
    }

    @Override
    public void paint(Graphics g) {
        for (Kreska kreska : kreski) {
            kreska.rysuj(g);
        }
        if (poczatek != null && dynamicznyKoniec != null) {
            g.setColor(Color.GRAY);
            g.drawLine(poczatek.x, poczatek.y, dynamicznyKoniec.x, dynamicznyKoniec.y);
        }
    }

    public void usunWszystkieKreski() {
        kreski.clear();
        repaint();
    }

    public void usunPierwszaKreske() {
        if (!kreski.isEmpty()) {
            kreski.remove(0);
            repaint();
        }
    }

    public void usunOstatniaKreske() {
        if (!kreski.isEmpty()) {
            kreski.remove(kreski.size() - 1);
            repaint();
        }
    }
}