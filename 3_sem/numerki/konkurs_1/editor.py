"""
Edytor Krzywych NIFS3
---------------------
Opis funkcji:
- Tworzenie i edycja krzywych sklejanych NIFS3.
- Obsługa wczytywania i zapisywania punktów do pliku JSON.
- Możliwość zmiany gęstości punktów (klawisze +/-).
- Podgląd tła (klawisz b).
- Ukrywanie punktów kontrolnych (klawisz h).
- Podglad każdej z krzywych osobno poprzez zmiane ich koloru (klawisz c)

Autor: Kamil Pawlikowski
"""

import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import json
import os
import numpy as np
import math
import copy
from spline import SplineSystem

DATA_FILE = "points.json"
DENSITIES_FILE = "densities.json"
IMAGE_FILE = "napis.jpg"

# Globalne ustawienia grubości linii
LINE_WIDTH_SPLINE = 1.2
LINE_WIDTH_BACKGROUND = 2

# Tablica gęstości punktów dla poszczególnych krzywych (ilość punktów na segment)
# Możesz ręcznie edytować te wartości dla każdej krzywej
# fmt: off
DENSITIES = [
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10
]
DEFAULT_DENSITY = 10
# fmt: on


class CurveEditor:
    def __init__(
        self, ax, points, curve_index, mode="edit", density=DEFAULT_DENSITY, epsilon=8
    ):
        self.ax = ax
        self.points = points  # List of [x, y]
        self.curve_index = curve_index
        self.mode = mode
        self.density = density
        self.epsilon = epsilon  # Pixel distance tolerance
        self.show_points = True  # Flaga widoczności punktów

        self.dragging_point_index = None

        # Elementy graficzne
        (self.line_spline,) = ax.plot(
            [], [], "b-", linewidth=LINE_WIDTH_SPLINE, label="NIFS3"
        )
        (self.points_plot,) = ax.plot(
            [], [], "ro", markersize=6, markerfacecolor="y", label="Węzły"
        )

        self.update_plot()
        self.update_title()

        self.cid_press = ax.figure.canvas.mpl_connect(
            "button_press_event", self.on_press
        )
        self.cid_release = ax.figure.canvas.mpl_connect(
            "button_release_event", self.on_release
        )
        self.cid_motion = ax.figure.canvas.mpl_connect(
            "motion_notify_event", self.on_motion
        )
        self.cid_key = ax.figure.canvas.mpl_connect("key_press_event", self.on_key)
        # Dodaj obsługę zamykania okna, aby wyczyścić eventy
        self.cid_close = ax.figure.canvas.mpl_connect("close_event", self.on_close)

    def on_close(self, event):
        # Rozłącz eventy przy zamykaniu, aby uniknąć błędów Tkinter
        try:
            self.ax.figure.canvas.mpl_disconnect(self.cid_press)
            self.ax.figure.canvas.mpl_disconnect(self.cid_release)
            self.ax.figure.canvas.mpl_disconnect(self.cid_motion)
            self.ax.figure.canvas.mpl_disconnect(self.cid_key)
            self.ax.figure.canvas.mpl_disconnect(self.cid_close)
        except Exception:
            pass

    def on_key(self, event):
        if event.key == "h":
            self.show_points = not self.show_points
            self.update_plot()
        elif event.key == "+" or event.key == "=":
            self.density += 1
            self.update_global_density()
            self.update_plot()
            self.update_title()
        elif event.key == "-":
            if self.density > 1:
                self.density -= 1
                self.update_global_density()
                self.update_plot()
                self.update_title()
        elif event.key == "b":
            for img in self.ax.images:
                img.set_visible(not img.get_visible())
            self.ax.figure.canvas.draw()

    def update_global_density(self):
        while len(DENSITIES) <= self.curve_index:
            DENSITIES.append(DEFAULT_DENSITY)
        DENSITIES[self.curve_index] = self.density

    def update_title(self):
        prefix = (
            f"Tworzenie krzywej nr {self.curve_index + 1}"
            if self.mode == "create"
            else f"Edycja krzywej nr {self.curve_index + 1}"
        )
        self.ax.set_title(
            f"{prefix} (Gęstość: {self.density})\n"
            "LPM: dodaj/przesuń | PPM: usuń | 'h': ukryj | 'b': tło | +/-: zmień gęstość"
        )

    def calculate_spline(self):
        if len(self.points) < 2:
            return [], []

        try:
            pts = np.array(self.points)
            x_nodes = pts[:, 0]
            y_nodes = pts[:, 1]
            n_points = len(x_nodes)

            # Parametryzacja t (równomierna)
            t_nodes = np.linspace(0, 1, n_points)

            # Siatka gęsta u
            n_u = max(2, (n_points - 1) * self.density)
            u_grid = np.linspace(0, 1, n_u)

            # Obliczenia NIFS3
            solver = SplineSystem(t_nodes)
            M_x = solver.solve_moments(x_nodes)
            M_y = solver.solve_moments(y_nodes)

            curve_x = solver.get_interpolated_values(x_nodes, M_x, u_grid)
            curve_y = solver.get_interpolated_values(y_nodes, M_y, u_grid)

            return curve_x, curve_y
        except Exception as e:
            print(f"Błąd obliczania splajnu: {e}")
            return [], []

    def update_plot(self):
        if not self.points:
            self.points_plot.set_data([], [])
            self.line_spline.set_data([], [])
        else:
            xs = [p[0] for p in self.points]
            ys = [p[1] for p in self.points]

            # Rysuj łamaną kontrolną i punkty
            if self.show_points:
                self.points_plot.set_data(xs, ys)
            else:
                self.points_plot.set_data([], [])

            # Rysuj splajn
            sx, sy = self.calculate_spline()
            self.line_spline.set_data(sx, sy)

        self.ax.figure.canvas.draw()

    def get_closest_point_index(self, x, y):
        if not self.points:
            return float("inf"), None

        dists = [(math.hypot(p[0] - x, p[1] - y), i) for i, p in enumerate(self.points)]
        dists.sort()
        return dists[0]  # (distance, index)

    def get_closest_segment_index(self, x, y):
        if len(self.points) < 2:
            return -1, float("inf"), None

        best_dist = float("inf")
        best_idx = -1
        best_proj = None

        for i in range(len(self.points) - 1):
            p1 = np.array(self.points[i])
            p2 = np.array(self.points[i + 1])
            p = np.array([x, y])

            v = p2 - p1
            w = p - p1
            c1 = np.dot(w, v)
            c2 = np.dot(v, v)

            if c2 == 0:  # p1 == p2
                dist = np.linalg.norm(p - p1)
                proj = p1
            else:
                b = c1 / c2
                if b < 0:
                    proj = p1
                elif b > 1:
                    proj = p2
                else:
                    proj = p1 + b * v
                dist = np.linalg.norm(p - proj)

            if dist < best_dist:
                best_dist = dist
                best_idx = i
                best_proj = proj.tolist()

        return best_idx, best_dist, best_proj

    def on_press(self, event):
        # Ignoruj kliknięcia, jeśli aktywne jest narzędzie paska narzędzi (np. zoom, pan)
        if self.ax.figure.canvas.toolbar and self.ax.figure.canvas.toolbar.mode != "":
            return

        if event.inaxes != self.ax:
            return

        if event.button == 1:  # Left Click
            # Check for Shift key to force add point
            force_add = event.key == "shift"

            # 1. Check if clicking on a point to drag
            if not force_add:
                dist, idx = self.get_closest_point_index(event.xdata, event.ydata)
                if dist < self.epsilon:
                    self.dragging_point_index = idx
                    return

            # 2. Check if clicking on a segment to insert
            # If force_add is True (Shift pressed), we skipped step 1 (drag),
            # so we allow checking for segment insertion here to enable adding points
            # very close to existing ones (on the line).
            seg_idx, seg_dist, proj_point = self.get_closest_segment_index(
                event.xdata, event.ydata
            )
            if seg_dist < self.epsilon:
                # Check if we are actually projecting onto the start or end of the curve
                # If so, we should probably append/prepend (Step 3) instead of inserting into the segment
                is_start_node = (
                    seg_idx == 0
                    and np.linalg.norm(np.array(proj_point) - np.array(self.points[0]))
                    < 1e-5
                )
                is_end_node = (
                    seg_idx == len(self.points) - 2
                    and np.linalg.norm(np.array(proj_point) - np.array(self.points[-1]))
                    < 1e-5
                )

                if not (is_start_node or is_end_node):
                    # Insert point
                    self.points.insert(seg_idx + 1, [event.xdata, event.ydata])
                    self.dragging_point_index = (
                        seg_idx + 1
                    )  # Start dragging the new point immediately
                    self.update_plot()
                    return

            # 3. If clicked far away, append to the closest end?
            # Sprawdźmy czy kliknięto blisko początku lub końca krzywej, żeby przedłużyć
            if self.points:
                start_dist = math.hypot(
                    self.points[0][0] - event.xdata, self.points[0][1] - event.ydata
                )
                end_dist = math.hypot(
                    self.points[-1][0] - event.xdata, self.points[-1][1] - event.ydata
                )

                # Jeśli kliknięto w miarę blisko końca (np. 50px), to dodaj na koniec
                # Albo po prostu zawsze dodawaj na koniec jeśli nic innego nie kliknięto?
                # Niech będzie: zawsze dodaj na koniec, chyba że bliżej jest początek (wtedy insert na start)

                if end_dist <= start_dist:
                    self.points.append([event.xdata, event.ydata])
                    self.dragging_point_index = len(self.points) - 1
                else:
                    self.points.insert(0, [event.xdata, event.ydata])
                    self.dragging_point_index = 0
                self.update_plot()
                return

            # If empty
            if not self.points:
                self.points.append([event.xdata, event.ydata])
                self.dragging_point_index = 0
                self.update_plot()

        elif event.button == 3:  # Right Click
            # Delete point
            dist, idx = self.get_closest_point_index(event.xdata, event.ydata)
            if dist < self.epsilon:
                self.points.pop(idx)
                self.dragging_point_index = None
                self.update_plot()

    def on_motion(self, event):
        if self.dragging_point_index is not None and event.inaxes == self.ax:
            self.points[self.dragging_point_index] = [event.xdata, event.ydata]
            self.update_plot()

    def on_release(self, event):
        self.dragging_point_index = None


def load_densities():
    if os.path.exists(DENSITIES_FILE):
        try:
            with open(DENSITIES_FILE, "r") as f:
                return json.load(f)
        except:
            pass
    return DENSITIES


def save_densities():
    with open(DENSITIES_FILE, "w") as f:
        json.dump(DENSITIES, f)
    print(f"Zapisano gęstości do {DENSITIES_FILE}")


def load_data():
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, "r") as f:
            return json.load(f)
    return []


def save_data(data):
    rounded_data = [[[round(p[0], 2), round(p[1], 2)] for p in curve] for curve in data]

    with open(DATA_FILE, "w") as f:
        json.dump(rounded_data, f)
    print(
        f"Zapisano {len(data)} krzywych do {DATA_FILE} (zaokrąglono do 2 miejsc po przecinku)"
    )
    save_densities()


def add_curve(data):
    if not os.path.exists(IMAGE_FILE):
        print(f"Błąd: Nie znaleziono pliku {IMAGE_FILE}")
        return

    img = mpimg.imread(IMAGE_FILE)
    fig, ax = plt.subplots(figsize=(12, 8))
    ax.imshow(img)

    for curve in data:
        xs = [p[0] for p in curve]
        ys = [p[1] for p in curve]
        ax.plot(xs, ys, "r-", linewidth=LINE_WIDTH_BACKGROUND, alpha=0.3)
    new_points = []
    next_idx = len(data)
    while len(DENSITIES) <= next_idx:
        DENSITIES.append(DEFAULT_DENSITY)
    density = DENSITIES[next_idx]

    editor = CurveEditor(ax, new_points, next_idx, mode="create", density=density)

    print("--- TRYB DODAWANIA ---")
    print("LPM na pustym: dodaj punkt.")
    print("LPM na punkcie: przesuń.")
    print("LPM na linii: wstaw punkt.")
    print("PPM na punkcie: usuń.")
    print("Zamknij okno, aby zakończyć i zapisać.")

    plt.show()
    try:
        plt.close("all")
    except:
        pass

    if new_points:
        data.append(new_points)
        print(f"Dodano krzywą złożoną z {len(new_points)} punktów.")
    else:
        print("Nie utworzono krzywej (brak punktów).")


def edit_existing_curve(data):
    if not data:
        print("Brak krzywych do edycji.")
        return

    print("\nWybierz krzywą do edycji:")
    for i, curve in enumerate(data):
        print(f"{i+1}. Krzywa ({len(curve)} punktów)")

    try:
        idx_str = input("Podaj numer krzywej: ")
        if not idx_str:
            return
        idx = int(idx_str) - 1
        if idx < 0 or idx >= len(data):
            print("Nieprawidłowy numer.")
            return
    except ValueError:
        print("To nie jest liczba.")
        return

    curve_points = data[idx]
    curve_points_copy = copy.deepcopy(curve_points)

    if not os.path.exists(IMAGE_FILE):
        print(f"Błąd: Nie znaleziono pliku {IMAGE_FILE}")
        return

    img = mpimg.imread(IMAGE_FILE)
    fig, ax = plt.subplots(figsize=(12, 8))
    ax.imshow(img)

    for i, c in enumerate(data):
        if i == idx:
            continue
        xs = [p[0] for p in c]
        ys = [p[1] for p in c]

    while len(DENSITIES) <= idx:
        DENSITIES.append(DEFAULT_DENSITY)
    density = DENSITIES[idx]

    editor = CurveEditor(ax, curve_points_copy, idx, mode="edit", density=density)
    plt.show()
    try:
        plt.close("all")
    except:
        pass

    print(f"Zakończono edycję w oknie.")
    save_choice = input("Czy zapisać zmiany w tej krzywej? (t/n): ")
    if save_choice.lower() == "t":
        data[idx] = curve_points_copy
        print(
            "Zmiany zostały zachowane (pamiętaj o opcji 'Zapisz i wyjdź' w menu głównym, aby zapisać do pliku)."
        )
    else:
        print("Zmiany zostały odrzucone.")


class CurvesViewer:
    def __init__(self, data):
        self.data = data
        self.show_points = True
        self.use_colors = True
        self.point_artists = []
        self.text_artists = []
        self.spline_artists = []
        self.total_u_size = 0

        if not os.path.exists(IMAGE_FILE):
            print(f"Błąd: Nie znaleziono pliku {IMAGE_FILE}")
            return

        img = mpimg.imread(IMAGE_FILE)
        self.fig, self.ax = plt.subplots(figsize=(12, 8))
        self.ax.imshow(img)

        self.plot_curves()

        num_curves = len(data)
        total_points = sum(len(c) for c in data)
        total_u = self.total_u_size

        self.ax.set_title(
            f"Statystyki: NIFS3={num_curves}, Pkt={total_points}, Rozmiar u={total_u}\n"
            f"'h': ukryj/pokaż punkty | 'c': przełącz kolory | 'b': tło"
        )

        # Automatyczne przybliżenie do wszystkich krzywych
        all_xs = []
        all_ys = []
        for curve in data:
            for p in curve:
                all_xs.append(p[0])
                all_ys.append(p[1])

        if all_xs and all_ys:
            min_x, max_x = min(all_xs), max(all_xs)
            min_y, max_y = min(all_ys), max(all_ys)

            # Margines 5% lub minimum 20px
            width = max_x - min_x
            height = max_y - min_y
            pad_x = max(width * 0.05, 20)
            pad_y = max(height * 0.05, 20)

            self.ax.set_xlim(min_x - pad_x, max_x + pad_x)
            self.ax.set_ylim(max_y + pad_y, min_y - pad_y)

        self.cid_key = self.fig.canvas.mpl_connect("key_press_event", self.on_key)
        plt.show()

    def plot_curves(self):
        # Lista kolorów do cyklicznego użycia
        colors = ["b", "g", "r", "c", "m", "y", "k", "orange", "purple", "brown"]
        self.total_u_size = 0  # Reset licznika

        for i, curve in enumerate(self.data):
            xs = [p[0] for p in curve]
            ys = [p[1] for p in curve]

            color = colors[i % len(colors)]  # Wybierz kolor cyklicznie

            # Rysuj splajn
            line = None
            if len(curve) >= 2:
                try:
                    pts = np.array(curve)
                    t = np.linspace(0, 1, len(curve))
                    solver = SplineSystem(t)
                    Mx = solver.solve_moments(pts[:, 0])
                    My = solver.solve_moments(pts[:, 1])

                    # Dynamiczne obliczanie rozmiaru u (zgodnie z generate_submission.py)
                    # Pobieramy gęstość z tablicy DENSITIES lub używamy domyślnej
                    density = DENSITIES[i] if i < len(DENSITIES) else DEFAULT_DENSITY
                    n_u = max(2, (len(curve) - 1) * density)
                    u = np.linspace(0, 1, n_u)

                    # Zliczamy faktycznie użyte punkty
                    self.total_u_size += len(u)

                    cx = solver.get_interpolated_values(pts[:, 0], Mx, u)
                    cy = solver.get_interpolated_values(pts[:, 1], My, u)
                    (line,) = self.ax.plot(
                        cx, cy, "-", color=color, linewidth=LINE_WIDTH_SPLINE
                    )
                except:
                    (line,) = self.ax.plot(
                        xs, ys, "-", color=color, linewidth=LINE_WIDTH_SPLINE
                    )
            else:
                (line,) = self.ax.plot(
                    xs, ys, "-", color=color, linewidth=LINE_WIDTH_SPLINE
                )

            if line:
                self.spline_artists.append((line, color))

            # Rysuj punkty i tekst (zachowaj referencje)
            (points_line,) = self.ax.plot(
                xs, ys, "o", color=color, markersize=3, markeredgecolor="white"
            )
            self.point_artists.append((points_line, color))

            if xs:
                text = self.ax.text(
                    xs[0],
                    ys[0],
                    str(i + 1),
                    color="black",
                    fontsize=12,
                    fontweight="bold",
                )
                self.text_artists.append(text)

    def on_key(self, event):
        if event.key == "h":
            self.show_points = not self.show_points
            for artist, _ in self.point_artists:
                artist.set_visible(self.show_points)
            for artist in self.text_artists:
                artist.set_visible(self.show_points)
            self.fig.canvas.draw()
        elif event.key == "c":
            self.use_colors = not self.use_colors

            # Aktualizuj kolory splajnów
            for line, original_color in self.spline_artists:
                line.set_color(original_color if self.use_colors else "red")

            # Aktualizuj kolory punktów
            for points, original_color in self.point_artists:
                points.set_color(original_color if self.use_colors else "yellow")
                points.set_markeredgecolor("white" if self.use_colors else "none")

            self.fig.canvas.draw()
        elif event.key == "b":
            for img in self.ax.images:
                img.set_visible(not img.get_visible())
            self.fig.canvas.draw()


def show_curves(data):
    CurvesViewer(data)


def main():
    global DENSITIES
    data = load_data()
    loaded_densities = load_densities()
    if loaded_densities:
        DENSITIES = loaded_densities

    while True:
        print("\n--- EDYTOR PUNKTÓW (ZAAWANSOWANY) ---")
        print(f"Aktualnie masz {len(data)} krzywych.")
        print("1. Dodaj nową krzywą (szybkie dodawanie)")
        print("2. Edytuj istniejącą krzywą (przesuwanie/usuwanie/wstawianie)")
        print("3. Usuń ostatnią krzywą")
        print("4. Pokaż wszystkie krzywe")
        print("5. Zapisz i wyjdź")

        choice = input("Wybierz opcję: ")

        if choice == "1":
            add_curve(data)
            save_data(data)
        elif choice == "2":
            edit_existing_curve(data)
            save_data(data)
        elif choice == "3":
            if data:
                confirm = input("Czy na pewno chcesz usunąć ostatnią krzywą? (t/n): ")
                if confirm.lower() == "t":
                    data.pop()
                    print("Usunięto ostatnią krzywą.")
                    save_data(data)
                else:
                    print("Anulowano usuwanie.")
            else:
                print("Brak krzywych do usunięcia.")
        elif choice == "4":
            show_curves(data)
        elif choice == "5":
            save_data(data)
            break
        else:
            print("Nieznana opcja.")


if __name__ == "__main__":
    main()
